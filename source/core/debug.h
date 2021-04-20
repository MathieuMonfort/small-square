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

class Debug{
private:

public:
    static void Log(const string &str);
    static void Log(const string &name, mat4 mat);
    static void Log( const string &name, vec2 vec);
    static void Log( const string &name, vec3 vec);
    static void Log( const string &name, vec4 vec);

    static void Clear();
};


#endif