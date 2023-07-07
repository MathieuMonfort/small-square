//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_LIGHT_H
#define SMALLSQUARE_LIGHT_H

#include "gameobject.h"

namespace smallsquare{

    /** \brief Let there be light.
     *
     * A GameObject representing a light source for shading.
     * The game finds every active lights in the game tree and sends it to the shader active for every drawable objects.
     * It's useless in itself and is there only to be derived into different specific types of light
     */
    class Light : public GameObject{
    public:
        vec3 ambient = vec3(0.0f);
        vec3 diffuse = vec3(0.0f);
        vec3 specular = vec3(0.0f);

        /**
         * A constructor for the Light class.
         * @param position The light's initial position.
         * @param euler The light's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the light's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the light's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the light's specular intensity and color ( in RGB format).
         */
        Light(vec3 position , vec3 euler, vec3 ambient, vec3 diffuse, vec3 specular ) ;
    };

    /** \brief Basically a sun
     *
     * A DirectionLight is a light source with a constant direction aimed to simulate the sun.
     */
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
    /** \brief Your average light bulb
    *
    * A PointLight is the simplest light source. it has no direction and simulates a common light source. Like a candle or a light bulb.
    */
    class PointLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;

        // TODO look up what constant linear and quadratic stand for (I forgot).

        /**
         * A constructor for the DirectionLight class.
         * @param position The DirectionLight's initial position.
         * @param euler The DirectionLight's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the DirectionLight's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the DirectionLight's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the DirectionLight's specular intensity and color ( in RGB format).
         * @param constant
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
    /** \brief Wouldn't you rather be under those instead of coding?
    *
    * A SpotLight is a directional light with a cutoff. That means light exists in a cone whose tip is at the object's position.
    * It simulates an actual stage spotlight.
    */
    class SpotLight : public Light{
    public:
        float constant;
        float linear;
        float quadratic;
        float cutOff;
        float outerCutOff;


        //TODO define cutOff and outerCutOff in documentation.
        /**
         * A constructor for the SpotLight class.
         * @param position The SpotLight's initial position.
         * @param euler The SpotLight's initial rotation (applied in XYZ order).
         * @param ambient A vec3 representing the SpotLight's ambient intensity and color ( in RGB format).
         * @param diffuse A vec3 representing the SpotLight's diffusion intensity and color ( in RGB format).
         * @param specular A vec3 representing the SpotLight's specular intensity and color ( in RGB format).
         * @param constant
         * @param linear
         * @param quadratic
         * @param cutOff
         * @param outerCutOff
         */
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