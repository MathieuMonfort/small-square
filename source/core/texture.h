//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_TEXTURE_H
#define SMALLSQUARE_TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

using namespace std;

namespace smallsquare{
    class Texture{
    public:
        unsigned int id = 0;
        /**
         * Constructor for the Texture class. Texture loading is done automatically through mesh loading
         * (if you've done you're 3D model exporting correctly ).
         * @param path A path to an image serving as texture.
         */
        explicit Texture(const string& path);

        /**
         * Bind the texture to an OpenGL texture processor. Called every time a mesh is drawn.
         * @param proc A GL_TEXTURE processor index.
         */
        void BindToProcessor(GLenum proc) const;
    };
}

#endif