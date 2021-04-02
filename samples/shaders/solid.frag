#version 330 core
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    bool emissive;
    float shininess;
};


in vec3 Norm;
in vec2 Tex;

out vec4 FragColor;

uniform Material material;

void main(){
    vec3 lightdir = normalize( vec3(-1.0,-1.0,-1.0));

    float diff = max(dot(Norm, lightdir) , 0.5) ;


    FragColor = vec4(texture(material.diffuse,Tex).rgb *diff ,1.0 );
}