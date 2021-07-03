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

        /**
         * A constructor for the Light class. It's useless in itself
         * and is there only to be derived into different specific types of light
         * @param position The light's initial position.
         * @param euler The light's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the light's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the light's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the light's specular intensity and color ( in RGB format).
         */
        Light(vec3 position , vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular ) ;
    };

    class DirectionLight : public Light{

        /**
         * A constructor for the DirectionLight class.
         * @param position The DirectionLight's initial position.
         * @param euler The DirectionLight's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the DirectionLight's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the DirectionLight's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the DirectionLight's specular intensity and color ( in RGB format).
         */
        DirectionLight( vec3 position ,
                        vec3 euler,
                        vec3 ambient,
                        vec3 diffuse,
                        vec3 specular);
    };

    class PointLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;

        // TODO look up what constant linear and quadratic stand for (I forgot).

        /**
          A constructor for the DirectionLight class.
         * @param position The DirectionLight's initial position.
         * @param euler The DirectionLight's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the DirectionLight's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the DirectionLight's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the DirectionLight's specular intensity and color ( in RGB format).
         * @param constant A float representing
         * @param linear
         * @param quadratic
         */
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