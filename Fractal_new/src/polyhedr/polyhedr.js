import { PARAMS1, PARAMS2, PARAMS3, pane, pane1, pane2, pane3 } from './ui.js';
import * as mat4 from 'gl-matrix/esm/mat4.js';

let gl;
let startTime;
let VBuf, ColBuf, IBuf;

let u_model_location;
let u_view_location;
let u_proj_location;

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
}

function rebuildGeometry() {
    if (VBuf) gl.deleteBuffer(VBuf);
    if (ColBuf) gl.deleteBuffer(ColBuf);
    if (IBuf) gl.deleteBuffer(IBuf);
    
    let ind = 0;
    let vertices = [];
    let colors = [];
    let indices = [];

    const c1 = PARAMS3.color1;
    const c2 = PARAMS3.color2;

    for (let i = 0; i < PARAMS2.n; i++) {
        let v = i / PARAMS2.n * 2 * Math.PI;

        let x1 = PARAMS2.a * (Math.cos(v) + PARAMS2.h * Math.sin(v));
        let y1 = PARAMS2.b * (Math.cos(v) - PARAMS2.h * Math.sin(v));
        let z1 = -PARAMS2.c * PARAMS2.h;

        let x2 = PARAMS2.a * (Math.cos(v) - PARAMS2.h * Math.sin(v));
        let y2 = PARAMS2.b * (Math.cos(v) + PARAMS2.h * Math.sin(v));
        let z2 = PARAMS2.c * PARAMS2.h;
        
        let idx0 = ind++;
        vertices.push(x1, y1, z1);
        colors.push(c1.r / 255, c1.g / 255, c1.b / 255);
        
        let idx1 = ind++;
        vertices.push(x2, y2, z2);
        colors.push(c2.r / 255, c2.g / 255, c2.b / 255);

        indices.push(idx0, idx1);
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

    IBuf = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, IBuf);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.DYNAMIC_DRAW);
    
    numOfIndices = indices.length;
}

function drawScene() {
    gl.clearColor(0, 0, 0, 1);
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    const matrProj = mat4.create();
    mat4.perspective(matrProj, Math.PI / 4, gl.viewportWidth / gl.viewportHeight, 0.1, 200.0);

    const matrView = mat4.create();
    const camPos = [0, 0, PARAMS1.zoom];
    const camLookAt = [0, 0, 0];
    const camUp = [0, 1, 0];

    mat4.lookAt(
        matrView, 
        camPos,
        camLookAt,
        camUp
    );

    const modelMatr = mat4.create();
    mat4.identity(modelMatr);
    if (PARAMS1.autoRotate) {
        PARAMS1.rotY += 0.01;
        pane1.refresh();
    }
    mat4.rotateX(modelMatr, modelMatr, PARAMS1.rotX);
    mat4.rotateY(modelMatr, modelMatr, PARAMS1.rotY);

    gl.uniformMatrix4fv(u_proj_location, false, matrProj);
    gl.uniformMatrix4fv(u_view_location, false, matrView);
    gl.uniformMatrix4fv(u_model_location, false, modelMatr);

    gl.drawElements(gl.LINES, numOfIndices, gl.UNSIGNED_SHORT, 0);
    
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

pane2.on('change', () => {
    rebuildGeometry();
});

pane3.on('change', () => {
    rebuildGeometry();
});

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