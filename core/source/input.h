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


    /** \brief An interface between user input and the game
     *
     *  A static class binding User Input to action string identifiers.
     *  Not meant to be instantiated.
     *  Every input mapping is saved and accessed statically.
     */
    class Input {

        /** \brief Let's Roll
         *
         *  An action an object binding a GLFW input key to an input ID.
         */
        struct Action {
        public:

            /**
             * A GLFW input key
             */
            int key;

            /**
             * The input id
             */
            string id;

        public:

            /**
             * THe constructor for the Action class
             * @param key A GLFW input key
             * @param id The input id
             */
            Action(int key,string  id);
        };

    private:

        /**
         * A vector of all the registered action in the Game.
         */
        static vector<Action *> _keymap;

        /**
         * A pointer to the Game's OpenGL Window
         */
        static GLFWwindow * _win;

        /**
         * The mouse's recorded horizontal position at last frame.
         */
        static float _mLastX;

        /**
         * The mouse's recorded vertical position at last frame.
         */
        static float _mLastY;

        /**
         * The mouse's horizontal offset since last frame.
         */
        static float _mXOffset;

        /**
         * The mouse's horizontal offset since last frame.
         */
        static float _mYOffset;

        /**
         * A factor by which the mouse's input axis is multiplied to get a final input axis
         */
        static float _sensitivity;

        /**
         * The OpenGL window's width
         */
        static int _winW;

        /**
         * The OpenGL window's height
         */
        static int _winH;

        /**
         * True if mouse first enters the OpenGL Window
         */
        static bool _firstMouse;

        /**
         * True if Input is correctly initialised
         */
        static bool _initialised;

        /**
         * Gets mouse position from the OpenGL Window and processes it into mouse offset.
         */
        static void ProcessMousePosition();

    public:

        /**
         * Init should be called once in Game class constructor.
         * it is used to assign a Window to get input information from.
         * @param win The active window the Input class gets input information from.
         */
        static void Init(GLFWwindow * win);


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
         * Get the mouse movement since last frame in pixel multiplied by the sensitivity.
         * @return A vec2 representing an input axis.
         */
        static vec2 MouseOffsetSensitive();

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