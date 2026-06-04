import {fractalType, PARAMS} from "./ui.js";

let gl;
let startTime;
let oldMouseCoords = [0.0, 0.0];
let m_deltacoords = [0.0, 0.0];
let isMouseDown = false;
let zoom = 1.0;

function initGL(canvas) {
    gl = canvas.getContext("webgl2");
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;
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

let u_time_location;
let u_fractal_type_location;
let u_offset_location;
let u_zoom;
let u_color1_location;
let u_color2_location;

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

    u_time_location = gl.getUniformLocation(program, "u_time");
    u_fractal_type_location = gl.getUniformLocation(program, "u_frac_type");
    u_offset_location = gl.getUniformLocation(program, "u_offset");
    u_zoom = gl.getUniformLocation(program, "u_zoom");
    u_color1_location = gl.getUniformLocation(program, "u_color1");
    u_color2_location = gl.getUniformLocation(program, "u_color2");
}

let vertexBuffer;
function initBuffer() {
    vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    let vertices = [-1, 3, -1, -1, 3, -1];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
}

function drawScene() {
    gl.clearColor(0, 0, 0, 1);
    gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.enableVertexAttribArray(0);
    gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
    
    let timeFromStart = performance.now() - startTime;

    gl.uniform1f(u_time_location, timeFromStart / 1000.0);
    gl.uniform1i(u_fractal_type_location, fractalType);
    gl.uniform2f(u_offset_location, m_deltacoords[0], m_deltacoords[1]);
    gl.uniform1f(u_zoom, zoom);
    
    gl.uniform3f(u_color1_location, 
        PARAMS.color1.r / 255.0, PARAMS.color1.g / 255.0, PARAMS.color1.b / 255.0);
    gl.uniform3f(u_color2_location, 
        PARAMS.color2.r / 255.0, PARAMS.color2.g / 255.0, PARAMS.color2.b / 255.0);

    gl.drawArrays(gl.TRIANGLES, 0, 3);
    window.requestAnimationFrame(drawScene);
}

function onStart(vsText, fsText) {
    let canvas = document.getElementById("webgl-canvas");
    
    canvas.onmousemove = (ev) => {
        if (isMouseDown) {
            m_deltacoords[0] -= (ev.clientX - oldMouseCoords[0]) * 2 / canvas.width;
            m_deltacoords[1] += (ev.clientY - oldMouseCoords[1]) * 2 / canvas.height;
            oldMouseCoords = [ev.clientX, ev.clientY];
        }                
    };

    canvas.onmousedown = (ev) => {
        oldMouseCoords = [ev.clientX, ev.clientY];
        isMouseDown = true;
    };
    
    canvas.onmouseup = () => {
        isMouseDown = false;
    };

    canvas.addEventListener('wheel', (ev) => {
        ev.preventDefault();
        let rect = canvas.getBoundingClientRect();
        let mouseClipX = ((ev.clientX - rect.left) / canvas.width) * 2.0 - 1.0;
        let mouseClipY = 1.0 - ((ev.clientY - rect.top) / canvas.height) * 2.0;

        let oldZoom = zoom;
        zoom *= Math.exp(-ev.deltaY * 0.005);
        zoom = Math.max(0.1, Math.min(100.0, zoom));

        let ratio = zoom / oldZoom;
        m_deltacoords[0] = (mouseClipX + m_deltacoords[0]) * ratio - mouseClipX;
        m_deltacoords[1] = (mouseClipY + m_deltacoords[1]) * ratio - mouseClipY;
    }, { passive: false });

    initGL(canvas);
    initShaders(vsText, fsText);
    initBuffer();

    startTime = performance.now();
    drawScene();
}

Promise.all([
    fetch('./fractal.vert').then(res => {
        if (!res.ok) throw new Error(res.status);
        return res.text();
    }),
    fetch('./fractal.frag').then(res => {
        if (!res.ok) throw new Error(res.status);
        return res.text();
    })
]).then(values => {
    console.log("Шейдеры успешно загружены!");
    onStart(values[0], values[1]);
}).catch(err => {
    console.error("Ошибка загрузки шейдеров:", err);
});