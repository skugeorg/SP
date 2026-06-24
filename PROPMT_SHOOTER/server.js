const http = require('http');
const { Server } = require('socket.io');

const PORT = 3000;
const MAX_PLAYERS = 8;
const MATCH_DURATION = 180;

const HTML = `<!DOCTYPE html>
<html lang="ru">
<head>
<meta charset="UTF-8">
<title>3D Shooter Multiplayer</title>
<style>
  body { margin:0; overflow:hidden; font-family:Arial; background:#000; color:#fff; }
  #menu { position:fixed; inset:0; background:rgba(0,0,0,0.85); display:flex; flex-direction:column; align-items:center; justify-content:center; z-index:100; }
  #menu h1 { font-size:48px; margin:0 0 20px; color:#0f0; text-shadow:0 0 20px #0f0; }
  #menu button, #menu input, #menu select { padding:14px 28px; font-size:20px; margin:8px; border:2px solid #0f0; background:#111; color:#0f0; cursor:pointer; border-radius:4px; }
  #menu button:hover { background:#0f0; color:#000; }
  #menu input, #menu select { text-align:center; width:280px; cursor:text; }
  #connStatus { margin-top:20px; font-size:18px; color:#ff0; text-align:center; }
  #hud { position:fixed; inset:0; pointer-events:none; z-index:10; }
  #crosshair { position:absolute; top:50%; left:50%; width:20px; height:20px; transform:translate(-50%,-50%); border:2px solid #0f0; border-radius:50%; box-shadow:0 0 10px #0f0; }
  #crosshair::before, #crosshair::after { content:''; position:absolute; background:#0f0; }
  #crosshair::before { top:50%; left:-10px; right:-10px; height:2px; transform:translateY(-50%); }
  #crosshair::after { left:50%; top:-10px; bottom:-10px; width:2px; transform:translateX(-50%); }
  #healthbar { position:absolute; bottom:30px; left:30px; width:250px; height:20px; background:#333; border:2px solid #fff; border-radius:4px; overflow:hidden; }
  #healthfill { height:100%; background:linear-gradient(90deg,#f00,#0f0); transition:width 0.2s; }
  #score { position:absolute; top:20px; right:30px; font-size:20px; text-shadow:2px 2px 4px #000; text-align:right; }
  #teamScore { position:absolute; top:20px; left:50%; transform:translateX(-50%); font-size:28px; text-shadow:2px 2px 4px #000; text-align:center; }
  #timer { position:absolute; top:70px; left:50%; transform:translateX(-50%); font-size:36px; text-shadow:2px 2px 4px #000; color:#fff; }
  #status { position:absolute; top:20px; left:30px; font-size:16px; text-shadow:2px 2px 4px #000; }
  #ammo { position:absolute; bottom:30px; right:30px; font-size:32px; text-shadow:2px 2px 4px #000; text-align:right; }
  #weaponName { position:absolute; bottom:80px; right:30px; font-size:18px; text-shadow:2px 2px 4px #000; color:#ffaa00; }
  #reloadBar { position:absolute; bottom:110px; right:30px; width:200px; height:10px; background:#333; border:2px solid #fff; border-radius:4px; overflow:hidden; display:none; }
  #reloadFill { height:100%; background:#ffaa00; width:0%; transition:width 0.05s linear; }
  #msg { position:absolute; top:50%; left:50%; transform:translate(-50%,-50%); font-size:48px; text-shadow:0 0 20px #000; opacity:0; transition:opacity 0.3s; pointer-events:none; }
  #players { position:absolute; top:60px; left:30px; font-size:14px; text-shadow:2px 2px 4px #000; }
  #endScreen { position:fixed; inset:0; background:rgba(0,0,0,0.9); display:none; flex-direction:column; align-items:center; justify-content:center; z-index:200; }
  #endScreen h1 { font-size:72px; margin:0 0 20px; text-shadow:0 0 30px currentColor; }
  #endScreen p { font-size:28px; margin:10px; }
  .hidden { display:none !important; }
  .tp-dfwv {
    position: fixed !important;
    top: 10px !important;
    right: 10px !important;
    z-index: 50 !important;
    pointer-events: auto !important;
  }
</style>
</head>
<body>
<div id="menu">
  <h1>⚡ 3D SHOOTER ⚡</h1>
  <input id="nickname" placeholder="Введи свой ник" maxlength="16">
  <select id="teamSelect">
    <option value="auto">🎲 Авто-распределение</option>
    <option value="red">🔴 Красные</option>
    <option value="blue">🔵 Синие</option>
  </select>
  <select id="weaponSelect">
    <option value="pistol">🔫 Пистолет (18 патр, урон 10)</option>
    <option value="rifle">🔫 Автомат (30 патр, урон 7)</option>
    <option value="shotgun">🔫 Дробовик (8 патр, урон 20)</option>
    <option value="sniper">🔫 Снайперка (5 патр, урон 50)</option>
  </select>
  <div id="connStatus">⏳ Подключение к серверу...</div>
  <button id="btnStart" class="hidden">🎮 НАЧАТЬ ИГРУ</button>
</div>
<div id="hud" class="hidden">
  <div id="crosshair"></div>
  <div id="healthbar"><div id="healthfill" style="width:100%"></div></div>
  <div id="score">
    Kills: <span id="killsVal">0</span> | Deaths: <span id="deathsVal">0</span><br>
    <span id="myTeamLabel"></span>
  </div>
  <div id="teamScore">
    <span style="color:#ff3333">🔴 <span id="redScore">0</span></span>
    :
    <span style="color:#3399ff">🔵 <span id="blueScore">0</span></span>
  </div>
  <div id="timer">03:00</div>
  <div id="status">HP: 100</div>
  <div id="weaponName">🔫 Пистолет</div>
  <div id="ammo">
    <span id="ammoVal">18</span> / <span id="ammoMax">18</span><br>
    <span style="font-size:14px; color:#aaa">[R] Перезарядка</span>
  </div>
  <div id="reloadBar"><div id="reloadFill"></div></div>
  <div id="players"></div>
  <div id="msg"></div>
</div>
<div id="endScreen">
  <h1 id="winnerText">🏆 ПОБЕДА!</h1>
  <p id="winnerTeam"></p>
  <p id="finalScore"></p>
  <p style="font-size:18px; color:#aaa">Рестарт через <span id="restartTimer">5</span> сек...</p>
</div>
<script src="https://cdn.socket.io/4.7.4/socket.io.min.js"></script>
<script src="https://unpkg.com/three@0.150.0/build/three.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/tweakpane@3.1.1/dist/tweakpane.min.js"></script>
<script>
const MATCH_DURATION = 180;

// Оружия
const WEAPONS = {
  pistol: { name: '🔫 Пистолет', damage: 10, fireRate: 200, magazineSize: 18, reloadTime: 1500, bulletSize: 0.08, color: 0xffff00 },
  rifle: { name: '🔫 Автомат', damage: 7, fireRate: 120, magazineSize: 30, reloadTime: 2000, bulletSize: 0.1, color: 0xffaa00 },
  shotgun: { name: '🔫 Дробовик', damage: 20, fireRate: 600, magazineSize: 8, reloadTime: 2500, bulletSize: 0.15, color: 0xff6600 },
  sniper: { name: '🔫 Снайперка', damage: 50, fireRate: 1200, magazineSize: 5, reloadTime: 3000, bulletSize: 0.12, color: 0x00ffff }
};

let socket, myId = -1, myTeam = null, gameStarted = false, isShooting = false, lastShot = 0;
let matchTimeLeft = MATCH_DURATION;
let currentWeapon = 'pistol';
let currentAmmo = WEAPONS.pistol.magazineSize;
let isReloading = false;
let reloadStartTime = 0;

const params = {
  sensitivity: 0.003,
  fov: 75,
  moveSpeed: 0.08,
  sprintSpeed: 0.15
};

const state = {
  myHP: 100, myKills: 0, myDeaths: 0, myName: 'Игрок',
  myPos: {x:0,y:1.7,z:0}, myRot: {x:0,y:0},
  players: {},
  teamScore: {red: 0, blue: 0},
  keys: {}, velocity: {x:0,y:0,z:0}, onGround: true
};

const menu = document.getElementById('menu');
const hud = document.getElementById('hud');
const msgEl = document.getElementById('msg');
const statusEl = document.getElementById('connStatus');
const endScreen = document.getElementById('endScreen');

const TEAM_COLORS = { red: 0xff3333, blue: 0x3399ff };

function showMsg(text, color='#fff') {
  msgEl.textContent = text; msgEl.style.color = color; msgEl.style.opacity = 1;
  setTimeout(()=> msgEl.style.opacity = 0, 1500);
}

// ===== TWEAKPANE =====
const pane = new Tweakpane.Pane({ title: '⚙️ Настройки', expanded: true });

const f1 = pane.addFolder({ title: 'Мышь и камера' });
f1.addInput(params, 'sensitivity', { min: 0.0005, max: 0.02, step: 0.0005, label: 'Чувствительность' });
f1.addInput(params, 'fov', { min: 50, max: 120, step: 1, label: 'FOV' }).on('change', e => {
  camera.fov = e.value; camera.updateProjectionMatrix();
});

const f2 = pane.addFolder({ title: 'Движение' });
f2.addInput(params, 'moveSpeed', { min: 0.03, max: 0.2, step: 0.01, label: 'Скорость' });
f2.addInput(params, 'sprintSpeed', { min: 0.1, max: 0.3, step: 0.01, label: 'Спринт' });

// ===== SOCKET.IO =====
socket = io();
socket.on('connect', () => {
  statusEl.textContent = '✅ Подключено! Введи ник и жми НАЧАТЬ';
  document.getElementById('btnStart').classList.remove('hidden');
});
socket.on('init', (data) => {
  myId = data.id;
  state.teamScore = data.teamScore;
  updateTeamScore();
  data.players.forEach(p => {
    if (p.id !== myId && p.team) createPlayerModel(p.id, p.color, p.pos, p.name, p.team);
  });
});
socket.on('player_joined', (data) => {
  if (data.id === myId) {
    myTeam = data.team;
    statusEl.innerHTML = '✅ Ты — ' + data.name + '<br>Команда: ' + (myTeam === 'red' ? '🔴 Красные' : '🔵 Синие');
    updateHUD();
  } else {
    showMsg('🎮 ' + data.name + ' подключился!', '#0f0');
    createPlayerModel(data.id, data.color, data.pos, data.name, data.team);
  }
  updatePlayersList(data.players);
});
socket.on('player_left', (data) => {
  showMsg('❌ ' + data.name + ' вышел', '#f00');
  removePlayerModel(data.id);
  updatePlayersList(data.players);
});
socket.on('team_score', (data) => {
  state.teamScore = data;
  updateTeamScore();
});
socket.on('match_time', (data) => {
  matchTimeLeft = data.time;
  updateTimer();
});
socket.on('match_end', (data) => {
  endMatch(data.winner, data.teamScore);
});
socket.on('match_reset', () => {
  resetMatch();
});
socket.on('pos', (data) => {
  if (data.id !== myId && state.players[data.id]) {
    state.players[data.id].pos = data.pos;
    state.players[data.id].rot = data.rot;
  }
});
socket.on('shoot', (data) => {
  if (data.id !== myId) {
    spawnBullet(new THREE.Vector3(data.pos.x, data.pos.y, data.pos.z),
                new THREE.Vector3(data.dir.x, data.dir.y, data.dir.z), false, data.id, data.team, data.weapon);
  }
});
socket.on('hit', (data) => {
  if (data.targetId === myId) {
    state.myHP -= data.damage;
    updateHUD();
    if (state.myHP <= 0) die(data.shooterId);
  }
});
socket.on('kill', (data) => {
  if (data.killerId === myId) {
    state.myKills++;
    showMsg('🏆 Убийство!', '#0f0');
    updateHUD();
  }
});
socket.on('disconnect', () => {
  statusEl.textContent = '❌ Соединение потеряно';
});

function updatePlayersList(players) {
  const el = document.getElementById('players');
  if (!el) return;
  el.innerHTML = 'Игроки: ' + players.filter(p => p.team).map(p => {
    const teamColor = p.team === 'red' ? '#ff3333' : '#3399ff';
    return '<span style="color:' + teamColor + '">●</span> ' + p.name;
  }).join(' ');
}

function updateTeamScore() {
  document.getElementById('redScore').textContent = state.teamScore.red;
  document.getElementById('blueScore').textContent = state.teamScore.blue;
}

function updateTimer() {
  const m = Math.floor(matchTimeLeft / 60);
  const s = Math.floor(matchTimeLeft % 60);
  document.getElementById('timer').textContent = 
    String(m).padStart(2,'0') + ':' + String(s).padStart(2,'0');
}

function updateAmmoDisplay() {
  const weapon = WEAPONS[currentWeapon];
  document.getElementById('ammoVal').textContent = currentAmmo;
  document.getElementById('ammoMax').textContent = weapon.magazineSize;
  const ammoEl = document.getElementById('ammoVal');
  if (currentAmmo <= Math.floor(weapon.magazineSize * 0.2)) ammoEl.style.color = '#ff3333';
  else if (currentAmmo <= Math.floor(weapon.magazineSize * 0.4)) ammoEl.style.color = '#ffaa00';
  else ammoEl.style.color = '#fff';
}

function updateHUD() {
  document.getElementById('healthfill').style.width = Math.max(0, state.myHP) + '%';
  document.getElementById('status').textContent = 'HP: ' + Math.max(0, state.myHP);
  document.getElementById('killsVal').textContent = state.myKills;
  document.getElementById('deathsVal').textContent = state.myDeaths;
  const teamColor = myTeam === 'red' ? '#ff3333' : '#3399ff';
  document.getElementById('myTeamLabel').innerHTML = 'Команда: <span style="color:' + teamColor + '">' + (myTeam === 'red' ? '🔴 Красные' : '🔵 Синие') + '</span>';
  document.getElementById('weaponName').textContent = WEAPONS[currentWeapon].name;
  updateAmmoDisplay();
}

document.getElementById('btnStart').onclick = () => {
  const nick = document.getElementById('nickname').value.trim() || ('Игрок' + (myId + 1));
  const teamChoice = document.getElementById('teamSelect').value;
  const weaponChoice = document.getElementById('weaponSelect').value;
  state.myName = nick;
  currentWeapon = weaponChoice;
  currentAmmo = WEAPONS[currentWeapon].magazineSize;
  socket.emit('set_name', { name: nick, teamChoice, weapon: currentWeapon });
  gameStarted = true;
  menu.classList.add('hidden');
  hud.classList.remove('hidden');
  renderer.domElement.requestPointerLock();
  updateHUD();
};

// ===== THREE.JS =====
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x87ceeb);
scene.fog = new THREE.Fog(0x87ceeb, 30, 100);
const camera = new THREE.PerspectiveCamera(params.fov, innerWidth/innerHeight, 0.1, 500);
camera.position.set(0, 1.7, 0);
const renderer = new THREE.WebGLRenderer({antialias:true});
renderer.setSize(innerWidth, innerHeight);
renderer.shadowMap.enabled = true;
document.body.appendChild(renderer.domElement);

const sun = new THREE.DirectionalLight(0xffffff, 1);
sun.position.set(30, 50, 20);
sun.castShadow = true;
sun.shadow.mapSize.set(2048, 2048);
sun.shadow.camera.left = -50; sun.shadow.camera.right = 50;
sun.shadow.camera.top = 50; sun.shadow.camera.bottom = -50;
scene.add(sun);
scene.add(new THREE.AmbientLight(0xffffff, 0.5));

const ground = new THREE.Mesh(
  new THREE.PlaneGeometry(200, 200),
  new THREE.MeshStandardMaterial({color:0x3a7d3a})
);
ground.rotation.x = -Math.PI/2;
ground.receiveShadow = true;
scene.add(ground);
scene.add(new THREE.GridHelper(200, 40, 0x000000, 0x222222));

const obstacles = [];
function addBox(x, y, z, w, h, d, color) {
  const m = new THREE.Mesh(
    new THREE.BoxGeometry(w, h, d),
    new THREE.MeshStandardMaterial({color})
  );
  m.position.set(x, y, z);
  m.castShadow = true; m.receiveShadow = true;
  scene.add(m);
  obstacles.push({min:{x:x-w/2,z:z-d/2}, max:{x:x+w/2,z:z+d/2}});
}
addBox(0, 2, -30, 60, 4, 1, 0x888888);
addBox(0, 2, 30, 60, 4, 1, 0x888888);
addBox(-30, 2, 0, 1, 4, 60, 0x888888);
addBox(30, 2, 0, 1, 4, 60, 0x888888);
addBox(-10, 1.5, -10, 4, 3, 1, 0x8b4513);
addBox(10, 1.5, 10, 4, 3, 1, 0x8b4513);
addBox(-10, 1.5, 10, 1, 3, 4, 0x8b4513);
addBox(10, 1.5, -10, 1, 3, 4, 0x8b4513);
addBox(0, 1, 0, 3, 2, 3, 0x666666);
addBox(-20, 1.5, 0, 2, 3, 8, 0x8b4513);
addBox(20, 1.5, 0, 2, 3, 8, 0x8b4513);
addBox(0, 1.5, -20, 8, 3, 2, 0x8b4513);
addBox(0, 1.5, 20, 8, 3, 2, 0x8b4513);

function checkCollision(x, z, r=0.4) {
  if (x < -29 || x > 29 || z < -29 || z > 29) return true;
  for (const o of obstacles) {
    if (x+r > o.min.x && x-r < o.max.x && z+r > o.min.z && z-r < o.max.z) return true;
  }
  return false;
}

function getSpawnPosition(team) {
  // Безопасные зоны спавна (подальше от стен)
  const safeZones = team === 'red' 
    ? [{x: -22, z: -15}, {x: -22, z: 0}, {x: -22, z: 15}]
    : [{x: 22, z: -15}, {x: 22, z: 0}, {x: 22, z: 15}];
  
  // Пытаемся найти безопасную позицию
  for (let attempt = 0; attempt < 20; attempt++) {
    const zone = safeZones[Math.floor(Math.random() * safeZones.length)];
    const x = zone.x + (Math.random() - 0.5) * 3;
    const z = zone.z + (Math.random() - 0.5) * 8;
    
    if (!checkCollision(x, z, 0.5)) {
      return { x, y: 1.7, z };
    }
  }
  
  // Fallback — центр карты
  return { x: 0, y: 1.7, z: 0 };
}

function makeTextSprite(text, color) {
  const canvas = document.createElement('canvas');
  const ctx = canvas.getContext('2d');
  canvas.width = 512; canvas.height = 128;
  ctx.clearRect(0,0,512,128);
  ctx.shadowColor = 'rgba(0,0,0,0.8)';
  ctx.shadowBlur = 8;
  ctx.shadowOffsetX = 2; ctx.shadowOffsetY = 2;
  ctx.fillStyle = color;
  ctx.font = 'Bold 48px Arial';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';
  ctx.fillText(text, 256, 64);
  const texture = new THREE.CanvasTexture(canvas);
  const material = new THREE.SpriteMaterial({map: texture, transparent: true, depthTest: false});
  const sprite = new THREE.Sprite(material);
  sprite.scale.set(2.5, 0.625, 1);
  return sprite;
}

function createPlayerModel(id, color, pos, name, team) {
  const player = new THREE.Group();
  const body = new THREE.Mesh(
    new THREE.CapsuleGeometry(0.4, 1, 4, 8),
    new THREE.MeshStandardMaterial({color})
  );
  body.position.y = 1; body.castShadow = true; player.add(body);
  const head = new THREE.Mesh(
    new THREE.SphereGeometry(0.3, 16, 16),
    new THREE.MeshStandardMaterial({color:0xffccaa})
  );
  head.position.y = 1.9; head.castShadow = true; player.add(head);
  const gun = new THREE.Mesh(
    new THREE.BoxGeometry(0.1, 0.1, 0.6),
    new THREE.MeshStandardMaterial({color:0x222222})
  );
  gun.position.set(0.3, 1.2, 0.3); player.add(gun);
  
  const spawnPos = pos || getSpawnPosition(team);
  player.position.set(spawnPos.x, 0, spawnPos.z);
  scene.add(player);
  
  const displayName = name || ('Игрок ' + (id + 1));
  const colorHex = '#' + color.toString(16).padStart(6, '0');
  const label = makeTextSprite(displayName, colorHex);
  label.position.y = 2.5;
  label.userData.isLabel = true;
  player.add(label);
  
  state.players[id] = {
    model: player,
    pos: spawnPos,
    rot: {x:0, y:0},
    hp: 100,
    color: color,
    name: displayName,
    team: team
  };
}

function removePlayerModel(id) {
  if (state.players[id]) {
    scene.remove(state.players[id].model);
    delete state.players[id];
  }
}

const myGun = new THREE.Group();
const gunBody = new THREE.Mesh(
  new THREE.BoxGeometry(0.1, 0.15, 0.5),
  new THREE.MeshStandardMaterial({color:0x111111})
);
const gunBarrel = new THREE.Mesh(
  new THREE.CylinderGeometry(0.03, 0.03, 0.4),
  new THREE.MeshStandardMaterial({color:0x333333})
);
gunBarrel.rotation.x = Math.PI/2; gunBarrel.position.z = -0.4;
myGun.add(gunBody); myGun.add(gunBarrel);
myGun.position.set(0.3, -0.3, -0.5);
camera.add(myGun);
scene.add(camera);

const muzzle = new THREE.PointLight(0xffaa00, 0, 5);
muzzle.position.set(0.3, -0.2, -1);
camera.add(muzzle);

const bullets = [];
function spawnBullet(from, dir, isMine, shooterId, team, weapon) {
  const w = WEAPONS[weapon] || WEAPONS.pistol;
  const color = isMine ? (team === 'red' ? 0xff6666 : 0x66aaff) : w.color;
  const b = new THREE.Mesh(
    new THREE.SphereGeometry(w.bulletSize),
    new THREE.MeshBasicMaterial({color})
  );
  b.position.copy(from);
  scene.add(b);
  bullets.push({mesh:b, dir:dir.clone(), life:60, isMine, shooterId, team, weapon});
}

function startReload() {
  if (isReloading) return;
  const weapon = WEAPONS[currentWeapon];
  if (currentAmmo >= weapon.magazineSize) {
    showMsg('Магазин полный!', '#ffaa00');
    return;
  }
  isReloading = true;
  reloadStartTime = performance.now();
  document.getElementById('reloadBar').style.display = 'block';
  showMsg('🔄 Перезарядка...', '#ffaa00');
}

function updateReload() {
  if (!isReloading) return;
  const weapon = WEAPONS[currentWeapon];
  const elapsed = performance.now() - reloadStartTime;
  const progress = Math.min(1, elapsed / weapon.reloadTime);
  document.getElementById('reloadFill').style.width = (progress * 100) + '%';
  
  if (progress >= 1) {
    isReloading = false;
    currentAmmo = weapon.magazineSize;
    document.getElementById('reloadBar').style.display = 'none';
    document.getElementById('reloadFill').style.width = '0%';
    updateAmmoDisplay();
    showMsg('✅ Готово!', '#0f0');
  }
}

let yaw = 0, pitch = 0;
document.addEventListener('keydown', e => { 
  state.keys[e.code] = true;
  if (e.code === 'KeyR' && gameStarted && !isReloading) {
    startReload();
  }
});
document.addEventListener('keyup', e => { state.keys[e.code] = false; });
renderer.domElement.addEventListener('click', () => {
  if (gameStarted) renderer.domElement.requestPointerLock();
});
document.addEventListener('mousemove', e => {
  if (document.pointerLockElement !== renderer.domElement) return;
  yaw -= e.movementX * params.sensitivity;
  pitch -= e.movementY * params.sensitivity;
  pitch = Math.max(-Math.PI/2+0.1, Math.min(Math.PI/2-0.1, pitch));
  state.myRot.x = pitch; state.myRot.y = yaw;
});

document.addEventListener('mousedown', e => {
  if (document.pointerLockElement !== renderer.domElement) return;
  if (e.button === 0) {
    isShooting = true;
    shoot();
  }
});
document.addEventListener('mouseup', e => {
  if (e.button === 0) isShooting = false;
});
window.addEventListener('blur', () => { isShooting = false; });

function shoot() {
  if (isReloading) return;
  const weapon = WEAPONS[currentWeapon];
  if (currentAmmo <= 0) {
    startReload();
    return;
  }
  const now = performance.now();
  if (now - lastShot < weapon.fireRate) return;
  lastShot = now;
  
  currentAmmo--;
  updateAmmoDisplay();
  
  const dir = new THREE.Vector3(0,0,-1).applyEuler(new THREE.Euler(pitch, yaw, 0, 'YXZ'));
  const from = camera.position.clone();
  spawnBullet(from, dir, true, myId, myTeam, currentWeapon);
  muzzle.intensity = 3;
  setTimeout(()=> muzzle.intensity = 0, 50);
  myGun.position.z = -0.35;
  setTimeout(()=> myGun.position.z = -0.5, 80);
  socket.emit('shoot', {pos:from, dir, team: myTeam, weapon: currentWeapon});
  
  if (currentAmmo <= 0) {
    setTimeout(() => {
      if (currentAmmo <= 0 && !isReloading) startReload();
    }, 300);
  }
}

function update() {
  const speed = state.keys['ShiftLeft'] ? params.sprintSpeed : params.moveSpeed;
  const forward = new THREE.Vector3(-Math.sin(yaw), 0, -Math.cos(yaw));
  const right = new THREE.Vector3(Math.cos(yaw), 0, -Math.sin(yaw));
  let mx = 0, mz = 0;
  if (state.keys['KeyW']) { mx += forward.x; mz += forward.z; }
  if (state.keys['KeyS']) { mx -= forward.x; mz -= forward.z; }
  if (state.keys['KeyD']) { mx += right.x; mz += right.z; }
  if (state.keys['KeyA']) { mx -= right.x; mz -= right.z; }
  const len = Math.hypot(mx, mz);
  if (len > 0) { mx = mx/len * speed; mz = mz/len * speed; }
  
  // Прыжок
  if (state.keys['Space'] && state.onGround) {
    state.velocity.y = 0.15;
    state.onGround = false;
  }
  
  // Гравитация
  state.velocity.y -= 0.008;
  
  const nx = camera.position.x + mx;
  const nz = camera.position.z + mz;
  if (!checkCollision(nx, camera.position.z)) camera.position.x = nx;
  if (!checkCollision(camera.position.x, nz)) camera.position.z = nz;
  
  camera.position.y += state.velocity.y;
  if (camera.position.y <= 1.7) {
    camera.position.y = 1.7;
    state.velocity.y = 0;
    state.onGround = true;
  }
  
  state.myPos.x = camera.position.x;
  state.myPos.y = camera.position.y;
  state.myPos.z = camera.position.z;
  camera.rotation.set(pitch, yaw, 0, 'YXZ');

  updateReload();

  if (isShooting && document.pointerLockElement === renderer.domElement) {
    shoot();
  }

  for (let i = bullets.length-1; i >= 0; i--) {
    const b = bullets[i];
    b.mesh.position.add(b.dir.clone().multiplyScalar(1.5));
    b.life--;
    
    if (b.isMine) {
      for (const pid in state.players) {
        const p = state.players[pid];
        if (p.team === myTeam) continue;
        const d = b.mesh.position.distanceTo(p.model.position.clone().add(new THREE.Vector3(0,1,0)));
        if (d < 0.8) {
          const weapon = WEAPONS[b.weapon] || WEAPONS.pistol;
          socket.emit('hit', {targetId: parseInt(pid), shooterId: myId, damage: weapon.damage});
          scene.remove(b.mesh); bullets.splice(i,1);
          break;
        }
      }
    } else {
      const d = b.mesh.position.distanceTo(camera.position);
      if (d < 0.6) {
        const weapon = WEAPONS[b.weapon] || WEAPONS.pistol;
        state.myHP -= weapon.damage; updateHUD();
        scene.remove(b.mesh); bullets.splice(i,1);
        if (state.myHP <= 0) die(b.shooterId);
        continue;
      }
    }
    
    if (checkCollision(b.mesh.position.x, b.mesh.position.z, 0.1) || b.life <= 0) {
      scene.remove(b.mesh); bullets.splice(i,1);
    }
  }

  for (const pid in state.players) {
    if (parseInt(pid) === myId) continue;
    const p = state.players[pid];
    p.model.position.lerp(new THREE.Vector3(p.pos.x, 0, p.pos.z), 0.2);
    if (p.rot) p.model.rotation.y = p.rot.y;
  }

  if (Math.random() < 0.3) {
    socket.emit('pos', {pos:state.myPos, rot:state.myRot});
  }
}

function die(killerId) {
  state.myHP = 100; state.myDeaths++;
  const weapon = WEAPONS[currentWeapon];
  currentAmmo = weapon.magazineSize;
  isReloading = false;
  document.getElementById('reloadBar').style.display = 'none';
  const spawnPos = getSpawnPosition(myTeam);
  camera.position.set(spawnPos.x, spawnPos.y, spawnPos.z);
  const killerName = state.players[killerId]?.name || ('Игрок ' + (killerId + 1));
  showMsg('💀 Тебя убил ' + killerName, '#f00');
  socket.emit('die', {killerId});
  updateHUD();
}

function endMatch(winner, teamScore) {
  gameStarted = false;
  document.exitPointerLock();
  endScreen.style.display = 'flex';
  const winnerText = document.getElementById('winnerText');
  const winnerTeam = document.getElementById('winnerTeam');
  const finalScore = document.getElementById('finalScore');
  
  if (winner === 'red') {
    winnerText.textContent = '🏆 ПОБЕДА КРАСНЫХ!';
    winnerText.style.color = '#ff3333';
    winnerTeam.textContent = '🔴 Красная команда победила!';
  } else if (winner === 'blue') {
    winnerText.textContent = '🏆 ПОБЕДА СИНИХ!';
    winnerText.style.color = '#3399ff';
    winnerTeam.textContent = '🔵 Синяя команда победила!';
  } else {
    winnerText.textContent = '🤝 НИЧЬЯ!';
    winnerText.style.color = '#ffff00';
    winnerTeam.textContent = 'Команды сыграли вничью!';
  }
  finalScore.textContent = 'Счёт: 🔴 ' + teamScore.red + ' : ' + teamScore.blue + ' 🔵';
  
  let countdown = 5;
  document.getElementById('restartTimer').textContent = countdown;
  const cdInterval = setInterval(() => {
    countdown--;
    document.getElementById('restartTimer').textContent = countdown;
    if (countdown <= 0) {
      clearInterval(cdInterval);
      endScreen.style.display = 'none';
      resetMatch();
    }
  }, 1000);
}

function resetMatch() {
  state.myHP = 100;
  state.myKills = 0;
  state.myDeaths = 0;
  state.teamScore = {red: 0, blue: 0};
  const weapon = WEAPONS[currentWeapon];
  currentAmmo = weapon.magazineSize;
  isReloading = false;
  matchTimeLeft = MATCH_DURATION;
  const spawnPos = getSpawnPosition(myTeam);
  camera.position.set(spawnPos.x, spawnPos.y, spawnPos.z);
  updateHUD();
  updateTeamScore();
  updateTimer();
  gameStarted = true;
  renderer.domElement.requestPointerLock();
  showMsg('🔥 Новый матч!', '#0f0');
}

function animate() {
  requestAnimationFrame(animate);
  if (gameStarted) update();
  renderer.render(scene, camera);
}
animate();

window.addEventListener('resize', () => {
  camera.aspect = innerWidth/innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(innerWidth, innerHeight);
});
</script>
</body>
</html>`;

const httpServer = http.createServer((req, res) => {
  res.setHeader('Content-Type', 'text/html; charset=utf-8');
  res.end(HTML);
});

const io = new Server(httpServer, {
  cors: { origin: '*' },
  pingTimeout: 60000,
  pingInterval: 25000
});

const TEAM_COLORS = { red: 0xff3333, blue: 0x3399ff };
let players = [];
let teamScore = { red: 0, blue: 0 };
let matchStartTime = Date.now();
let matchEnded = false;

function getPlayersPublic() {
  return players.map(p => ({
    id: p.id, color: p.color, pos: p.pos, name: p.name, team: p.team
  }));
}

function assignTeam(choice, currentCounts) {
  if (choice === 'red') return 'red';
  if (choice === 'blue') return 'blue';
  return currentCounts.red <= currentCounts.blue ? 'red' : 'blue';
}

function checkMatchEnd() {
  const elapsed = (Date.now() - matchStartTime) / 1000;
  const timeLeft = Math.max(0, MATCH_DURATION - elapsed);
  
  io.emit('match_time', { time: timeLeft });
  
  if (timeLeft <= 0 && !matchEnded) {
    matchEnded = true;
    let winner = null;
    if (teamScore.red > teamScore.blue) winner = 'red';
    else if (teamScore.blue > teamScore.red) winner = 'blue';
    
    io.emit('match_end', { winner, teamScore });
    
    setTimeout(() => {
      teamScore = { red: 0, blue: 0 };
      matchStartTime = Date.now();
      matchEnded = false;
      io.emit('team_score', teamScore);
      io.emit('match_reset');
    }, 6000);
  }
}

setInterval(checkMatchEnd, 1000);

io.on('connection', (socket) => {
  if (players.length >= MAX_PLAYERS) {
    socket.emit('full');
    socket.disconnect();
    return;
  }
  
  const id = players.length;
  const playerData = {
    socket, id,
    color: 0xffffff,
    pos: { x: 0, y: 1.7, z: 0 },
    name: 'Игрок ' + (id + 1),
    team: null,
    teamChoice: 'auto',
    weapon: 'pistol'
  };
  players.push(playerData);
  console.log(`✅ Игрок ${id + 1} подключился (всего: ${players.length})`);
  
  socket.emit('init', {
    id, pos: playerData.pos,
    players: getPlayersPublic(),
    teamScore
  });
  
  socket.on('set_name', (data) => {
    const cleanName = String(data.name || '').trim().slice(0, 16) || ('Игрок ' + (id + 1));
    playerData.name = cleanName;
    playerData.teamChoice = data.teamChoice || 'auto';
    playerData.weapon = data.weapon || 'pistol';
    
    const counts = { red: 0, blue: 0 };
    players.forEach(p => { if (p.team) counts[p.team]++; });
    playerData.team = assignTeam(playerData.teamChoice, counts);
    playerData.color = TEAM_COLORS[playerData.team];
    
    if (playerData.team === 'red') {
      playerData.pos = { x: -22 + Math.random() * 3, y: 1.7, z: Math.random() * 30 - 15 };
    } else {
      playerData.pos = { x: 22 - Math.random() * 3, y: 1.7, z: Math.random() * 30 - 15 };
    }
    
    console.log(`📝 ${cleanName} → ${playerData.team === 'red' ? '🔴 Красные' : '🔵 Синие'} (${playerData.weapon})`);
    
    players.forEach(p => {
      p.socket.emit('player_joined', {
        id, color: playerData.color, pos: playerData.pos,
        name: cleanName, team: playerData.team,
        players: getPlayersPublic()
      });
    });
  });
  
  socket.on('pos', (data) => {
    playerData.pos = data.pos;
    players.forEach(p => {
      if (p.socket !== socket) p.socket.emit('pos', {id, ...data});
    });
  });
  
  socket.on('shoot', (data) => {
    players.forEach(p => {
      if (p.socket !== socket) p.socket.emit('shoot', {id, team: playerData.team, ...data});
    });
  });
  
  socket.on('hit', (data) => {
    const target = players.find(p => p.id === data.targetId);
    if (target) target.socket.emit('hit', data);
  });
  
  socket.on('die', (data) => {
    const killer = players.find(p => p.id === data.killerId);
    const victim = players.find(p => p.id === id);
    if (killer && victim && killer.team !== victim.team) {
      teamScore[killer.team]++;
      io.emit('team_score', teamScore);
      killer.socket.emit('kill', { killerId: killer.id });
    }
  });
  
  socket.on('disconnect', () => {
    const name = playerData.name;
    console.log(`❌ ${name} отключился`);
    players = players.filter(p => p.socket !== socket);
    players.forEach(p => {
      p.socket.emit('player_left', {
        id, name,
        players: getPlayersPublic()
      });
    });
  });
});

httpServer.listen(PORT, '0.0.0.0', () => {
  console.log(`\n🎮 Сервер запущен! (максимум ${MAX_PLAYERS} игроков)`);
  console.log(`⏱️ Длительность матча: ${MATCH_DURATION} сек`);
  console.log(`📡 Локальный адрес: http://localhost:${PORT}`);
  
  const nets = require('os').networkInterfaces();
  for (const name of Object.keys(nets)) {
    for (const net of nets[name]) {
      if (net.family === 'IPv4' && !net.internal) {
        console.log(`🌐 Для друга в сети: http://${net.address}:${PORT}`);
      }
    }
  }
  console.log(`\n⏳ Ждём игроков...\n`);
});