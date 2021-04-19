//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_LIGHT_H
#define SMALLSQUARE_LIGHT_H

#include <gameobject.h>

namespace smallsquare{
    class Light : public GameObject{
    public:
        vec3 ambient = vec3(0.0f);
        vec3 diffuse = vec3(0.0f);
        vec3 specular = vec3(0.0f);

        Light(vec3 position , vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular ) ;
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
                    float quadratic );
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
                    float outerCutOff);
    };


}


#endif