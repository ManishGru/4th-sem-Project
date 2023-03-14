#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =  1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

//layout(location = 1) in vec2 vertexUV;
out vec3 fragmentColor;
//out vec2 UV;
out vec3 Normal;
//out vec3 crntPos;

uniform mat4 MVP;

void main()
{
    //crntPos = vec3(mvp* vec4(aPos, 1.0f));
    gl_Position = MVP*vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    fragmentColor = aColor;
    // UV = vertexUV;
    Normal = aNormal;
}