#version 410 core

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec4 position;

void main() {
    vec4 pos4 = vec4(position.xyz, 1.0);
    gl_Position = proj_matrix * mv_matrix * position;
}