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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <texture.h>
#include <light.h>

using namespace std;
using namespace glm;

namespace smallsquare{
    struct Material{
    public:
        Texture * diffuse;
        Texture * specular;
        Texture * emission;
        float shininess;

        Material(Texture * diffuse, Texture * specular, Texture * emission, float shininess ){
            this->diffuse = diffuse;
            this->specular = specular;
            this->emission = emission;
            this->shininess = shininess;
        }
    };

    class Shader{
    public:
        int program;


        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void Use() const;

        void SetBool(const string &name, bool value) const;
        void SetInt(const string &name, int value) const;
        void SetFloat(const string &name, float value) const;
        void SetVec2(const std::string &name, const glm::vec2 &value) const;
        void SetVec3(const std::string &name, const glm::vec3 &value) const;
        void SetVec4(const std::string &name, const glm::vec4 &value) const;

        void SetMat2(const string &name, const mat2 &value) const;
        void SetMat3(const string &name, const mat3 &value) const;
        void SetMat4(const string &name, const mat4 &value) const;
        void SetMaterial(const string &name, Material *value) const;

        void SetDirLightArray(const string &name, vector<DirectionLight *>value) const;
        void SetPointLightArray(const string &name, vector<PointLight *>value) const;
        void SetSpotLightArray(const string &name, vector<SpotLight *> value) const;
    };


}


#endif