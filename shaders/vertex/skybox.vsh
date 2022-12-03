#version 330
layout(location = 0) in vec3 vp;
out vec3 fragmentPosition;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
     gl_Position = (projectionMatrix * viewMatrix) * vec4(vp, 1.0);
     fragmentPosition = vp;
}