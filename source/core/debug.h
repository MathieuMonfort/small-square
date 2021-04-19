//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_DEBUG_H
#define SMALLSQUARE_DEBUG_H

#include <iostream>
#include <string>
#include <iomanip>
#include <shader.h>

struct DebugLine{
public:
    vector<float> vertices;
};

using namespace std;
class Debug{
private:
    static smallsquare::Shader * _debugShader;

public:
    static void Init( smallsquare::Shader * shader);
    static void DrawRay(vec3 start, vec3 end , vec3 color);

    static void Log(const string &str);
    static void Log(const string &name, mat4 mat);
    static void Log( const string &name, vec2 vec);
    static void Log( const string &name, vec3 vec);
    static void Log( const string &name, vec4 vec);


    static void Clear();
};


#endif