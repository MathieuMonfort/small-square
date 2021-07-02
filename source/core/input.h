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

        /**
         * Init should be called once in Game class constructor. it is used to assign a Window to get input information
         * from.
         * @param win The active window the Input class gets input information from.
         */
        static void Init(GLFWwindow * win);

        /**
         * DO NOT USE Called every time the mouse moves. It updates _mXOffset and _mYOffset so any object class can retrieve mouse
         * input information.
         * @param win The active window
         * @param xpos The current mouse x position in pixel
         * @param ypos The current mouse y position in pixel
         */
        static void MouseMoveCallback(GLFWwindow * win, double xpos, double ypos);

        /**
         * DO NOT USE Called every time the window is resized. It updates the _winH and _winW so the viewports can
         * update their projection matrices.
         * @param win The active window.
         * @param h The current window height.
         * @param w The current window width.
         */
        static void WindowSizeCallback(GLFWwindow * win , int h, int w);

        /**
         * Check if a key
         * @param name
         * @return
         */
        static bool KeyPressed(const string &name);
        static vec2 MouseOffset();
        static vec2 MousePosition();
        static void Process();
        static void AddInput( int key, string id);


    };
}

#endif //SMALLSQUARE_INPUT_H
