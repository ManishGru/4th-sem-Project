#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;
out vec3 ourColor;

out vec2 texCoord;

uniform mat4 camMatrix;
void main() {
    gl_Position = camMatrix * vec4(position, 1.0f);
    ourColor = aColor;
    texCoord = aTex;
}