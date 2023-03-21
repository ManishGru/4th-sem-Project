#version 330 core
layout(location = 0) out vec4 color;

in vec2 texCoord;
in vec3 Normal;
in vec3 crntpos;

uniform sampler2D tex0;
uniform vec4 lightcolor;
uniform vec3 lightpos; 
uniform vec3 camPos;

void main(){
    float ambient=0.50f;
    vec3 normal=normalize(Normal);
    vec3 lightdirection=normalize(lightpos-crntpos);

    float diffuse=max(dot(normal,lightdirection),0.0f);
    float specularlight=0.50f;
    vec3 viewDirection=normalize(camPos-crntpos);
    vec3 reflectionDirection=reflect(-lightdirection,normal);

    float specAmount=pow(max(dot(viewDirection,reflectionDirection),0.0f),8);
    float specular=specAmount*specularlight;
    color = texture(tex0, texCoord)*lightcolor*(ambient+diffuse+specular);
}