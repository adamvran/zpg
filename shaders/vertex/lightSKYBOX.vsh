#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;
out vec3 fragmentPosition;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
     gl_Position = (projectionMatrix * viewMatrix) * vec4(vp, 1.0);
     fragmentPosition = vp;
}