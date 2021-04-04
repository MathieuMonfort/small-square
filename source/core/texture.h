//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

using namespace std;

namespace smallsquare{
    class Texture{
    public:
        unsigned int ID = 0;

        explicit Texture(const string& path);
        void BindToProcessor(GLenum proc) const;
    };
};

#endif