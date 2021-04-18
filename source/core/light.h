//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_LIGHT_H
#define SMALLSQUARE_LIGHT_H

#include <game.h>

class GameObject;
namespace smallsquare{
    class Light : public GameObject{
    public:
        vec3 ambient = vec3(0.0f);
        vec3 diffuse = vec3(0.0f);
        vec3 specular = vec3(0.0f);


        Light(vec3 position , vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular ) : GameObject(position, euler, vec3(0.0f)){
            this->ambient = ambient;
            this->diffuse = diffuse; 
            this->specular = specular;
        }
    };

    class DirectionLight : public Light{};

    class PointLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;

        PointLight( vec3 position , 
                    vec3 euler, 
                    vec3 ambient, 
                    vec3 diffuse, 
                    vec3 specular, 
                    float constant ,
                    float linear, 
                    float quadratic ): Light(position, euler, ambient, diffuse, specular){
            this->constant = constant;
            this->linear = linear;
            this->quadratic = quadratic;
        }
    };

    class SpotLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;
        float cutOff;
        float outerCutOff;
        
        SpotLight( vec3 position , 
                    vec3 euler, 
                    vec3 ambient, 
                    vec3 diffuse, 
                    vec3 specular, 
                    float constant ,
                    float linear, 
                    float quadratic,
                    float cutOff,
                    float outerCutOff): Light(position, euler, ambient, diffuse, specular){
            this->constant = constant;
            this->linear = linear;
            this->quadratic = quadratic;
            this->cutOff = cutOff;
            this->outerCutOff = outerCutOff;
        }
    };


}


#endif