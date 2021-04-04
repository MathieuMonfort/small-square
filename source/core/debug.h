//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>

#include <iomanip>



using namespace std;
using namespace glm;

class DEBUG{
public:
    static void Log(const string &str){
        cout << str <<endl;
    }

    static void Log(mat4 mat, const string &name){
        cout << name << " Matrix :" <<endl;
        cout << setprecision(1) << mat[0][0]  <<"\t" << mat[1][0]<< "\t" << mat[2][0]<< "\t" << mat[3][0] << endl;
        cout << setprecision(1) << mat[0][1] << "\t" << mat[1][1]<< "\t" << mat[2][1]<< "\t" << mat[3][1] << endl;
        cout << setprecision(1) << mat[0][2] << "\t" << mat[1][2]<< "\t" << mat[2][2]<< "\t" << mat[3][2] << endl;
        cout << setprecision(1) << mat[0][3] << "\t" << mat[1][3]<< "\t" << mat[2][3]<< "\t" << mat[3][3] << endl;
    }

    static void Log(vec3 vec, const string &name){
        cout << name << " Vector :" <<endl;
        cout << setprecision(1) << vec[0]  <<"\t" << vec[1]<< "\t" << vec[2]<< "\t" << vec[3] << endl;
    }


    static void Clear(){
        system("clear");
    }

};


#endif