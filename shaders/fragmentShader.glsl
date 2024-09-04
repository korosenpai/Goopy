#version 400

precision highp float;

uniform vec2 resolution;

float raymarch(vec3 ro, vec3 rd) {
    return 1.0;
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;
    uv -= 0.5;
    uv *= 2.;



    gl_FragColor = vec4(uv.x, uv.y, 0, 1.0);
}
