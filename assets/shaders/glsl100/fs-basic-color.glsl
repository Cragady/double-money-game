#version 100 core

out vec4 FragColor;
uniform vec3 u_fragmentColor;
uniform float u_alphaValue = 1.0;

void main() {
   FragColor = vec4(u_fragmentColor, u_alphaValue);
};
