//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_DEBUG_H
#define SMALLSQUARE_DEBUG_H

#include <iostream>
#include <string>
#include <iomanip>
#include <game.h>
#include "shader.h"

struct DebugLine{
public:
    vector<float> vertices;
};


using namespace std;
class Debug{
public:
    static smallsquare::Shader debugShader;


    static void Init( smallsquare::Shader shader){
        Debug::debugShader = shader;
    }


    static void DrawRay(vec3 start, vec3 end , vec3 color){
        DebugLine ray{};
        ray.vertices = {
            start.x , start.y, start.z,
            end.x, end.y, end.z
        };

        unsigned int vao, vbo;

        glGenVertexArrays(1,&vao);
        glGenBuffers(1,&vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,vbo );

        glBufferData(GL_ARRAY_BUFFER, ray.vertices.size() * sizeof (float), &ray.vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3,GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*) nullptr);
        glEnableVertexAttribArray(0);

        debugShader.Use();
        debugShader.SetVec3("color", color);
        glDrawArrays(GL_LINE,0,1);

        glBindVertexArray(0);

    }


    static void Log(const string &str){
        cout << str <<endl;
    }

    static void Log(const string &name, mat4 mat){
        cout << name << " Matrix :" <<endl;
        cout << setprecision(1) << mat[0][0]  <<"\t" << mat[1][0]<< "\t" << mat[2][0]<< "\t" << mat[3][0] << endl;
        cout << setprecision(1) << mat[0][1] << "\t" << mat[1][1]<< "\t" << mat[2][1]<< "\t" << mat[3][1] << endl;
        cout << setprecision(1) << mat[0][2] << "\t" << mat[1][2]<< "\t" << mat[2][2]<< "\t" << mat[3][2] << endl;
        cout << setprecision(1) << mat[0][3] << "\t" << mat[1][3]<< "\t" << mat[2][3]<< "\t" << mat[3][3] << endl;
    }
    static void Log( const string &name, vec2 vec){
        cout << name << " Vector :" <<endl;
        cout << setprecision(10000) << vec.x  <<"\n" << vec.y<< endl;
    }

    static void Log( const string &name, vec3 vec){
        cout << name << " Vector :" <<endl;
        cout << setprecision(1) << vec.x  <<"\t" << vec.y<< "\t" << vec.z<< endl;
    }

    static void Log( const string &name, vec4 vec){
        cout << name << " Vector :" <<endl;
        cout << setprecision(1) << vec.x  <<"\t" << vec.y<< "\t" << vec.z<< "\t" << vec.w<< endl;
    }



    static void Clear(){
        system("clear");
    }



};


#endif