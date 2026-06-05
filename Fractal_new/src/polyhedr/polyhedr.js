import { PARAMS1, PARAMS2, PARAMS3, PARAMS_LIGHT, pane1, pane2, pane3, pane4 } from './ui.js';
import * as mat4 from 'gl-matrix/esm/mat4.js';

let gl;
let startTime;
let VBuf, ColBuf, IBuf, NBuf;
let u_model_location, u_view_location, u_proj_location;
let u_light_pos_location, u_ambient_strength_location;
let numOfIndices = 0;

function initGL(canvas) {
  gl = canvas.getContext("webgl2", { alpha: false });
  if (!gl) {
    console.error("WebGL2 не поддерживается");
    return;
  }
  gl.viewportWidth = canvas.width;
  gl.viewportHeight = canvas.height;
  gl.enable(gl.DEPTH_TEST);
}

function getShader(shaderStr, type) {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, shaderStr);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    console.error("Shader compile error:", gl.getShaderInfoLog(shader));
  }
  return shader;
}

function initShaders(vsText, fsText) {
  const vs = getShader(vsText, gl.VERTEX_SHADER);
  const fs = getShader(fsText, gl.FRAGMENT_SHADER);
  const program = gl.createProgram();
  gl.attachShader(program, vs);
  gl.attachShader(program, fs);
  gl.linkProgram(program);

  if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
    console.error("Program linkage error:", gl.getProgramInfoLog(program));
  }
  gl.useProgram(program);

  u_model_location = gl.getUniformLocation(program, "u_model");
  u_view_location = gl.getUniformLocation(program, "u_view");
  u_proj_location = gl.getUniformLocation(program, "u_projection");
  u_light_pos_location = gl.getUniformLocation(program, "u_light_pos");
  u_ambient_strength_location = gl.getUniformLocation(program, "u_ambient_strength");
}

function rebuildGeometry() {
  if (VBuf) gl.deleteBuffer(VBuf);
  if (ColBuf) gl.deleteBuffer(ColBuf);
  if (IBuf) gl.deleteBuffer(IBuf);
  if (NBuf) gl.deleteBuffer(NBuf);

  let ind = 0;
  let vertices = [];
  let colors = [];
  let indices = [];
  let normals = [];

  const c1 = PARAMS3.color1;
  const c2 = PARAMS3.color2;
  const n = PARAMS2.n;

  for (let i = 0; i <= n; i++) {
    let v = (i / n) * 2 * Math.PI;

    let x1 = PARAMS2.a * (Math.cos(v) + PARAMS2.h * Math.sin(v));
    let y1 = PARAMS2.b * (Math.cos(v) - PARAMS2.h * Math.sin(v));
    let z1 = -PARAMS2.c * PARAMS2.h;

    let x2 = PARAMS2.a * (Math.cos(v) - PARAMS2.h * Math.sin(v));
    let y2 = PARAMS2.b * (Math.cos(v) + PARAMS2.h * Math.sin(v));
    let z2 = PARAMS2.c * PARAMS2.h;
    
    let vx = x2 - x1;
    let vy = y2 - y1;
    let vz = z2 - z1;

    let dx1 = PARAMS2.a * (-Math.sin(v) + PARAMS2.h * Math.cos(v));
    let dy1 = PARAMS2.b * (-Math.sin(v) - PARAMS2.h * Math.cos(v));
    let n1x = dy1 * vz;
    let n1y = -dx1 * vz;
    let n1z = dx1 * vy - dy1 * vx;
    let len1 = Math.sqrt(n1x*n1x + n1y*n1y + n1z*n1z);
    if (len1 > 0.0001) { n1x /= len1; n1y /= len1; n1z /= len1; }
    else { n1x = 0; n1y = 0; n1z = 1; }

    let dx2 = PARAMS2.a * (-Math.sin(v) - PARAMS2.h * Math.cos(v));
    let dy2 = PARAMS2.b * (-Math.sin(v) + PARAMS2.h * Math.cos(v));
    let n2x = dy2 * vz;
    let n2y = -dx2 * vz;
    let n2z = dx2 * vy - dy2 * vx;
    let len2 = Math.sqrt(n2x*n2x + n2y*n2y + n2z*n2z);
    if (len2 > 0.0001) { n2x /= len2; n2y /= len2; n2z /= len2; }
    else { n2x = 0; n2y = 0; n2z = 1; }

    let idx1 = ind++;
    vertices.push(x1, y1, z1);
    colors.push(c1.r / 255, c1.g / 255, c1.b / 255);
    normals.push(n1x, n1y, n1z);
    
    let idx2 = ind++;
    vertices.push(x2, y2, z2);
    colors.push(c2.r / 255, c2.g / 255, c2.b / 255);
    normals.push(n2x, n2y, n2z);

    if (i < n) {
      let next_idx1 = idx1 + 2;
      let next_idx2 = idx2 + 2;
      
      indices.push(idx1, idx2, next_idx1);
      indices.push(idx2, next_idx2, next_idx1);
    }
  }

  VBuf = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, VBuf);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.DYNAMIC_DRAW);
  const aPos = gl.getAttribLocation(gl.getParameter(gl.CURRENT_PROGRAM), "a_pos");
  gl.enableVertexAttribArray(aPos);
  gl.vertexAttribPointer(aPos, 3, gl.FLOAT, false, 0, 0);

  ColBuf = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, ColBuf);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.DYNAMIC_DRAW);
  const aColor = gl.getAttribLocation(gl.getParameter(gl.CURRENT_PROGRAM), "a_color");
  gl.enableVertexAttribArray(aColor);
  gl.vertexAttribPointer(aColor, 3, gl.FLOAT, false, 0, 0);

  NBuf = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, NBuf);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.DYNAMIC_DRAW);
  const aNormal = gl.getAttribLocation(gl.getParameter(gl.CURRENT_PROGRAM), "a_normal");
  if (aNormal !== -1) {
    gl.enableVertexAttribArray(aNormal);
    gl.vertexAttribPointer(aNormal, 3, gl.FLOAT, false, 0, 0);
  }

  IBuf = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, IBuf);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.DYNAMIC_DRAW);

  numOfIndices = indices.length;
}

function drawScene() {
  gl.clearColor(0.05, 0.05, 0.05, 1); // Слегка серый фон, чтобы фигура выделялась
  gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  
  const matrProj = mat4.create();
  mat4.perspective(matrProj, Math.PI / 4, gl.viewportWidth / gl.viewportHeight, 0.1, 200.0);

  const matrView = mat4.create();
  const camPos = [0, 0, PARAMS1.zoom];
  mat4.lookAt(matrView, camPos, [0, 0, 0], [0, 1, 0]);

  const modelMatr = mat4.create();
  if (PARAMS1.autoRotate) {
    PARAMS1.rotY += 0.01;
    pane1.refresh();
  }
  mat4.rotateX(modelMatr, modelMatr, PARAMS1.rotX);
  mat4.rotateY(modelMatr, modelMatr, PARAMS1.rotY);

  gl.uniformMatrix4fv(u_proj_location, false, matrProj);
  gl.uniformMatrix4fv(u_view_location, false, matrView);
  gl.uniformMatrix4fv(u_model_location, false, modelMatr);
  
  gl.uniform3f(u_light_pos_location, PARAMS_LIGHT.lightX, PARAMS_LIGHT.lightY, PARAMS_LIGHT.lightZ);
  gl.uniform1f(u_ambient_strength_location, PARAMS_LIGHT.ambient);

  // <-- ГЛАВНОЕ ИЗМЕНЕНИЕ: Рисуем треугольники вместо линий
  gl.drawElements(gl.TRIANGLES, numOfIndices, gl.UNSIGNED_SHORT, 0);

  window.requestAnimationFrame(drawScene);
}

function onStart(vsText, fsText) {
  let canvas = document.getElementById("webgl-canvas");
  let isMouseDown = false;
  let oldMouseCoords = [0.0, 0.0];

  canvas.onmousedown = (ev) => {
    oldMouseCoords = [ev.clientX, ev.clientY];
    isMouseDown = true;
    PARAMS1.autoRotate = false;
    pane1.refresh();
  };

  canvas.onmouseup = () => { isMouseDown = false; };

  canvas.onmousemove = (ev) => {
    if (isMouseDown) {
      PARAMS1.rotY += (ev.clientX - oldMouseCoords[0]) * 0.01;
      PARAMS1.rotX += (ev.clientY - oldMouseCoords[1]) * 0.01;
      oldMouseCoords = [ev.clientX, ev.clientY];
      pane1.refresh();
    }                
  };

  canvas.addEventListener('wheel', (ev) => {
    ev.preventDefault();
    PARAMS1.zoom += ev.deltaY * 0.05;
    PARAMS1.zoom = Math.max(0.1, Math.min(100.0, PARAMS1.zoom));
    pane1.refresh();
  }, { passive: false });

  initGL(canvas);
  initShaders(vsText, fsText);
  rebuildGeometry();

  startTime = performance.now();
  drawScene();
}

pane2.on('change', () => { rebuildGeometry(); });
pane3.on('change', () => { rebuildGeometry(); });

Promise.all([
  fetch('./polyhedr.vert').then(res => {
    if (!res.ok) throw new Error(res.status);
    return res.text();
  }),
  fetch('./polyhedr.frag').then(res => {
    if (!res.ok) throw new Error(res.status);
    return res.text();
  })
]).then(values => {
  console.log("Шейдеры успешно загружены!");
  onStart(values[0], values[1]);
}).catch(err => {
  console.error("Ошибка загрузки шейдеров: ", err);
});