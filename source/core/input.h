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
        Action(int key,string  id);
    };

    class Input {

    private:
        static vector<Action *> _keymap;
        static GLFWwindow * _win;
        static float _mLastX;
        static float _mLastY;
        static float _mXOffset;
        static float _mYOffset;
        static float _sensitivity;

        static int _winW;
        static int _winH;


        static bool _firstMouse;
        static bool _initialised;

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
