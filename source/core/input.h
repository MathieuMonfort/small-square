//
// Created by mmonfort on 4/2/21.
//

#ifndef SMALLSQUARE_INPUT_H
#define SMALLSQUARE_INPUT_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <iostream>

using namespace  std;
using namespace glm;


namespace  smallsquare {
    struct Action {
    public:
        int key;
        string id;

    public:
        Action(const int key,string  id) {
            this->key = key;
            this->id = id;
        }
    };

    class Input {
        vector<Action *> keymap;
        GLFWwindow * _win;
        static float mlastx;
        static float mlasty;
        static float mxoffset;
        static float myoffset;
        static bool firstmouse;

    public:
        Input(GLFWwindow * win );
        static void MouseMoveCallback(GLFWwindow * win, double xpos, double ypos);
        bool KeyPressed(const string &name);
        vec2 MouseOffset();
        void Process();
        void AddInput( int key, string id);


    };
}

#endif //SMALLSQUARE_INPUT_H
