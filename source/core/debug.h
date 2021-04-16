//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef SMALLSQUARE_DEBUG_H
#define SMALLSQUARE_DEBUG_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>

#include <iomanip>



using namespace std;
using namespace glm;

class Debug{
public:
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


    static void Clear(){
        system("clear");
    }

};


#endif