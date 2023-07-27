//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_DEBUG_H
#define SMALLSQUARE_DEBUG_H

#include <iostream>
#include <string>
#include <iomanip>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;


namespace smallsquare {


    /**
     * A Debug class to facilitate logging.
     * As it writes to standard input, it's not meant to be Instantiated.
     */
    class Debug {
    public:
        /**
         * Log a string in the default debug terminal.
         * @param str The string that will be logged.
         */
        static void Log(const string &str);

        /**
         * Log a 4x4 matrix in the default debug terminal.
         * @param name A title to identify the logged matrix.
         * @param mat The matrix that will be logged.
         */
        static void Log(const string &name, mat4 mat);

        /**
         * Log a 2D vector in the default debug terminal.
         * @param name A title to identify the logged vector.
         * @param vec The vector that will be logged.
         */
        static void Log(const string &name, vec2 vec);

        /**
         * Log a 3D vector in the default debug terminal.
         * @param name A title to identify the logged vector.
         * @param vec The vector that will be logged.
         */
        static void Log(const string &name, vec3 vec);

        /**
         * Log a 4D vector in the default debug terminal.
         * @param name A title to identify the logged vector.
         * @param vec The vector that will be logged.
         */
        static void Log(const string &name, vec4 vec);

        /**
         * Clear the default debug terminal.
         */
        static void Clear();
    };
}
#endif