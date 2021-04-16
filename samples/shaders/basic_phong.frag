#version 330 core
//Type Definitions
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    bool emissive;
    float shininess;};
struct DirectionLight{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;};
struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;};
struct SpotLight{
    vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
    };







//Function Prototypes
vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir);
vec3 CalcDirLight(DirectionLight light, vec3 norm, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir);


#define MAX_DIR_LIGHT_NR 4
#define MAX_POINT_LIGHT_NR 8
#define MAX_SPOT_LIGHT_NR 8





out vec4 FragColor;

in vec3 FragPos;
in vec3 normal;
in vec2 Tex;

uniform float time;

uniform DirectionLight dirlights[MAX_DIR_LIGHT_NR];
uniform int n_dirLight;

uniform PointLight pointlights[MAX_POINT_LIGHT_NR];
uniform int n_pointLight;

uniform SpotLight spotlights[MAX_SPOT_LIGHT_NR];
uniform int n_spotLight;

uniform Material material;
uniform vec3 viewPos; 




void main(){
    vec3 lightTotal = vec3(0.0);

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    //Emisive Light Calculations
    if(material.emissive == true){
        vec3 emit = abs((texture(material.emission, Tex).rgb) * cos(time));
        lightTotal += emit;
    }

    for(int i =0; i < n_dirLight && i < MAX_DIR_LIGHT_NR; i++){
        lightTotal += CalcDirLight(dirlights[i],norm,viewDir );
    }

    for(int i =0; i < n_pointLight && i < MAX_POINT_LIGHT_NR; i++){
        lightTotal += CalcPointLight(pointlights[i],norm,viewDir );
    }

    for(int i =0; i < n_spotLight && i < MAX_DIR_LIGHT_NR; i++){
        lightTotal += CalcSpotLight(spotlights[i],norm,viewDir );
    }

    //Final Color
    FragColor = vec4(lightTotal, 1.0);
}
vec3 CalcDirLight(DirectionLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);

    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, Tex));
    
    float diff = max(dot(norm, lightDir),0.0 );   
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, Tex));
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, Tex));
    return (ambient + diffuse + specular);

}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(light.position - FragPos);
    float distance = length(light.position - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * texture(material.diffuse, Tex).rgb;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, Tex).rgb;

    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, Tex).rgb;

    ambient *= attenuation;
    diffuse *= attenuation; 
    specular *= attenuation;

    return ambient + diffuse + specular;

}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir){
    vec3 lightDir = normalize(light.position - FragPos);
    float distance = length(light.position - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);


    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff; 
    float intensity = clamp((theta - light.outerCutOff) /epsilon, 0.0,1.0);


    //Ambient Light Calculations
    vec3 ambient = light.ambient * texture(material.diffuse, Tex).rgb;


    //Diffuse Light Calculations
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, Tex).rgb;


    //Specular Light Calculations
    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, Tex).rgb;

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}


