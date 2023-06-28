//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_SHADER_H
#define SMALLSQUARE_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "light.h"

using namespace std;
using namespace glm;

namespace smallsquare{
    struct Material{
    public:
        Texture * diffuse;
        Texture * specular;
        Texture * emission;
        float shininess;
        /**
         * Constructor for the Material struct.
         * @param diffuse A vec3 representing a models diffusion coefficient (In RGB Format).
         * @param specular A vec3 representing a models specular coefficient (In RGB Format).
         * @param emission A vec3 representing a models emission intensity (In RGB Format).
         * @param shininess A float representing the intensity a which the model reflects specular light.
         */
        Material(Texture * diffuse, Texture * specular, Texture * emission, float shininess );
    };

    class Shader{
    public:
        int program;

        /**
         * Constructor for the Shader class.
         * @param vertexPath The path to the glsl vertex shader file.
         * @param fragmentPath The path to the glsl fragment shader file.
         */
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        /**
         * Use is called by the Model Class every time it is being drawn.
         */
        void Use() const;

        /**
         * Send a boolean value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetBool(const string &name, bool value) const;

        /**
         * Send an integer value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetInt(const string &name, int value) const;

        /**
         * Send a float value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetFloat(const string &name, float value) const;

        /**
         * Send a vec2 value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetVec2(const std::string &name, const glm::vec2 &value) const;

        /**
         * Send a vec3 value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetVec3(const std::string &name, const glm::vec3 &value) const;

        /**
         * Send a vec4 value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetVec4(const std::string &name, const glm::vec4 &value) const;

        /**
         * Send a mat2 value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetMat2(const string &name, const mat2 &value) const;

        /**
         * Send a mat3 value to the running shader.
         * @param value The value that will be sent.
         * @param name The name serving as identifier for the shader program.
         */
        void SetMat3(const string &name, const mat3 &value) const;

        /**
         * Send a mat4 value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetMat4(const string &name, const mat4 &value) const;

        /**
         * Send a material struct value to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value The value that will be sent.
         */
        void SetMaterial(const string &name, Material *value) const;

        /**
         * Send an array of directional lights to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value A vector containing a number of DirectionLight objects.
         */
        void SetDirLightArray(const string &name, vector<DirectionLight *>value) const;

        /**
         * Send an array of point lights to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value A vector containing a number of PointLight objects.
         */
        void SetPointLightArray(const string &name, vector<PointLight *>value) const;

        /**
         * Send an array of spot lights to the running shader.
         * @param name The name serving as identifier for the shader program.
         * @param value A vector containing a number of SpotLight objects.
         */
        void SetSpotLightArray(const string &name, vector<SpotLight *> value) const;
    };


}


#endif