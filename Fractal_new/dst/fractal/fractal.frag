#version 300 es
precision highp float;
layout (location = 0) out vec4 o_color;

uniform float u_time;
uniform int u_frac_type;
uniform vec2 u_offset;
uniform float u_zoom;
uniform vec3 u_color1;
uniform vec3 u_color2;

in vec2 DrawPos;

vec2 mul(vec2 A, vec2 B) {
    return vec2(A.x * B.x - A.y * B.y, A.x * B.y + A.y * B.x);
}

bool isInsideFractal(vec2 z, vec2 c) {
    int n = 0;
    while (length(z) < 2.0 && n < 128) {
        z = mul(z, z) + c;
        n++;
    }
    return n == 128;
}

void main() {
    vec2 z = (DrawPos + u_offset) / u_zoom;
    bool inside = false;

    if (u_frac_type == 0) {
        vec2 c = vec2(0.5 + 0.2 * sin(u_time / 10.0), 0.5 + sin(u_time) * 0.2);
        inside = isInsideFractal(z, c);
    } else {
        inside = isInsideFractal(z, z);
    }

    if (inside) {
        float t = fract(length(z) * 2.5 + u_time * 0.4);
        o_color = vec4(mix(u_color2, u_color1, t), 1.0);
    } else {
        o_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}