//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_INPUT_H
#define SMALLSQUARE_INPUT_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility>
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
            this->id = std::move(id);
        }
    };

    class Input {
        static vector<Action *> keymap;
        static GLFWwindow * _win;
        static float mlastx;
        static float mlasty;
        static float mxoffset;
        static float myoffset;
        static float sensitivity;

        static int winw;
        static int winh;


        static bool firstmouse;
        static bool initialised;

    public:


        static void Init(GLFWwindow * win );
        static void MouseMoveCallback(GLFWwindow * win, double xpos, double ypos);
        static void WindowSizeCallback(GLFWwindow * win , int h, int w);
        static bool KeyPressed(const string &name);
        static vec2 MouseOffset();
        static vec2 MousePosition();
        static void Process();
        static void AddInput( int key, string id);


    };
}

#endif //SMALLSQUARE_INPUT_H
