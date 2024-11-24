#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
// texture samplers
//uniform sampler2D u_Texture;
//uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
void main()
{
 vec3 norm = normalize(Normal);
 vec3 lightDir = normalize(lightPos- FragPos);

 float diff = max(dot(norm, lightDir), 0.0);
 vec3 diffuse = diff * lightColor;

 float ambientStrength = 0.1;
 vec3 ambient = ambientStrength * lightColor;
 vec3 result = (ambient+diffuse) * objectColor;
 FragColor = vec4(result, 1.0);
}