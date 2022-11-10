#version 330
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec3 fragmentPosition;
uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main () {
     ex_worldPosition = transform * vec4(vp, 1.0);
     ex_worldNormal = normalize(transpose(inverse(mat3(transform))) * vn);
     gl_Position = (projectionMatrix * viewMatrix * transform) * vec4(vp, 1.0);
     fragmentPosition = vp;
}