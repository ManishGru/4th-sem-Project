 #version 330 core
 in vec3 fragmentColor;
 in vec3 Normal;
 //in vec2 UV;
 out vec3 color;
 uniform vec3 lightPos;
//uniform sampler2D myTextureSampler;
void main()
{

  float ambient = 0.2f;
  vec3 normal = normalize(Normal);
  float diffuse = max(dot(normal, lightPos), 0.0f);
   color = fragmentColor;//*(diffuse+ambient);
  // color = texture(myTextureSampler, UV).rgb;
}