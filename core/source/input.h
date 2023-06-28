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
         * Called every time the mouse moves. It updates _mXOffset and _mYOffset so any object class can retrieve mouse
         * input information.
         * @param win The active window
         * @param xpos The current mouse x position in pixel
         * @param ypos The current mouse y position in pixel
         */
        static void MouseMoveCallback(GLFWwindow * win, double xpos, double ypos);

        /**
         * Called every time the window is resized. It updates the _winH and _winW so the viewports can
         * update their projection matrices.
         * @param win The active window.
         * @param h The current window height.
         * @param w The current window width.
         */
        static void WindowSizeCallback(GLFWwindow * win , int h, int w);

        /**
         * Check if a key is currently in a pressed state.
         * @param name The key's name, set with AddInput function.
         * @return true if the key is currently down false if not.
         */
        static bool KeyPressed(const string &name);

        /**
         * Get the mouse movement since last frame in pixel.
         * @return A vec2 representing a translation in pixel.
         */
        static vec2 MouseOffset();

        /**
         * Get The current mouse position in pixel from th top left.
         * @return A vec2 representing the mouse position in pixel.
         */
        static vec2 MousePosition();

        /**
         * Process Should be called by the Game class at every iteration of the game loop
         * before any object Tick and Draw Function (done by default).
         */
        static void Process();

        /**
         * Bind a GLFW_KEY to an id string so it can be accessed through the KeyPressed function.
         * @param key A GLFW_KEY code.
         * @param id A unique string to identify the key.
         */
        static void AddInput( int key, string id);

    };
}

#endif //SMALLSQUARE_INPUT_H