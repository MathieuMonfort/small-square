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
        unsigned int ID;

        Texture(string path);
        void BindToProcessor(GLenum proc);
    };
};

#endif