//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SHADER_H
#define SHADER_H

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
        void use() const;

        void setBool(const string &name, bool value) const;
        void setInt(const string &name, int value) const;
        void setFloat(const string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;

        void setMat2(const string &name, const mat2 &value) const;
        void setMat3(const string &name, const mat3 &value) const;
        void setMat4(const string &name, const mat4 &value) const;
        void setMaterial(const string &name, Material *value) const;

        void setDirLightArray(const string &name, vector<DirectionLight *>value) const;
        void setPointLightArray(const string &name, vector<PointLight *>value) const;
        void setSpotLightArray(const string &name, vector<SpotLight *> value) const;
    };


}


#endif