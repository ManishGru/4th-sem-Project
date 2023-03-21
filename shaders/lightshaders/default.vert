#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 anormal;

out vec3 color;
out vec2 texCoord;


out vec3 Normal;
out vec3 crntpos;

uniform mat4 camMatrix;
void main() {
    crntpos = position;
    gl_Position = camMatrix * vec4(position, 1.0f);

    //color=acolor;

    texCoord = aTex;
    Normal=anormal;
}
