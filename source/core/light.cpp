//
// Created by Mathieu Monfort
// Date : 4/18/21.
// In Project : smallsquare
//


#include <light.h>


smallsquare::Light::Light(vec3 position, vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular)
                                    : GameObject(position, euler, vec3(0.0f)){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

smallsquare::DirectionLight::DirectionLight(vec3 position, vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular)
        : Light(position, euler, ambient, diffuse, specular) {}


smallsquare::PointLight::PointLight(vec3 position, vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular,
                                    float constant, float linear, float quadratic)
                                    : Light(position, euler, ambient, diffuse, specular){
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

smallsquare::SpotLight::SpotLight(vec3 position, vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular, float constant,
                                  float linear, float quadratic, float cutOff, float outerCutOff)
                                  : Light(position, euler, ambient, diffuse, specular){
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;
}

