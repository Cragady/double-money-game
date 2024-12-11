#version 330 core
layout (location = 0) in vec3 aPos;

uniform float aPosZ = 1.0;
uniform mat4 transform;

void main() {
   gl_Position = transform * vec4(aPos, aPosZ);
};
