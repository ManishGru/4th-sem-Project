#version 330 core
layout(location = 0) out vec4 color;

in vec2 texCoord;
uniform sampler2D tex0;
// uniform vec4 ourColor;
void main(){
    // color = vec4(1.0f,0.0f,0.0f,1.0f);
    // color = ourColor; 
    color = texture(tex0, texCoord);
}