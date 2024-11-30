#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
 sampler2D diffuse; // removed ambient since they have the same color.
 sampler2D specular;
 float shininess;
 };
 uniform Material material;

 struct DirLight {
 vec3 direction; // no need for position since it is considerd infinitly far."like sun light"
 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 };
uniform DirLight dirLight;
 struct PointLight{
 vec3 position;
 
 float constant; // usualy 1.0 , 
 float linear;
 float quadratic;

 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 };
uniform PointLight pointLight;
 struct SpotLight{
 vec3 position;
 vec3 direction;
 float cutOff;
 
 float constant; // usualy 1.0 , 
 float linear;
 float quadratic;

 vec3 ambient;
 vec3 diffuse;
 vec3 specular;
 };	
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);	
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);	
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// TODO : try optimizing some caculations.
 // properties
 vec3 norm = normalize(Normal);
 vec3 viewDir = normalize(viewPos- FragPos);
 // phase 1: Directional lighting
 vec3 result = CalcDirLight(dirLight, norm, viewDir);
 result += CalcPointLight(pointLight, norm, FragPos, viewDir);
  // phase 3: Spot light
 result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
 FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
 {
 vec3 lightDir = normalize(-light.direction);
 // diffuse shading
 float diff = max(dot(normal, lightDir), 0.0);
 // specular shading
 vec3 reflectDir = reflect(-lightDir, normal);
 float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
 // combine results
 vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord));
 vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCoord));
 vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
 return (ambient + diffuse + specular);
 }


 vec3 CalcPointLight (PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
 {
 vec3 lightDir=normalize(light.position-fragPos);
 //diffuseshading
 float diff=max(dot(normal, lightDir),0.0);
 //specularshading
 vec3 reflectDir=reflect(-lightDir,normal);
 float spec=pow(max(dot(viewDir,reflectDir),0.0),
 material.shininess);
 //attenuation
 float distance =length(light.position-fragPos);
 float attenuation=1.0/(light.constant+light.linear * distance+
 light.quadratic * (distance * distance));
 //combineresults
 vec3 ambient=light.ambient * vec3(texture(material.diffuse,TexCoord));
 vec3 diffuse=light.diffuse * diff * vec3(texture(material.diffuse,TexCoord));
 vec3 specular=light.specular * spec * vec3(texture(material.specular,TexCoord));
 ambient *=attenuation;
 diffuse *=attenuation;
 specular *=attenuation;
 return(ambient+diffuse+specular);
 }