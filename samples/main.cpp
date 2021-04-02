#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem> 

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include <model.h>
#include <debug.h>

#define M_SPEED 2.5f
#define R_SPEED 2.0f

using namespace std;
using namespace glm;
using namespace smallsquare;


class A{
public :
    int x,y; 
    A(int x, int y ){
        this->x = x;
        this->y = y;

    }

    void print(){
        cout<< "(" <<  x << " ;" << y << " );" <<endl; 
    }
};





int main(int argc, char * argv[]){

    Game * game = new Game();
    Camera * cam = new Camera(vec3 (0.0f,0.0f, -5.0f ), vec3(0.0f));
    game->AddViewPort(cam);

    
    string resFold = get_current_dir_name();
    resFold += "/samples";
    Shader * PhongShader = new Shader((resFold +  "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
    Shader * SolidShader = new Shader((resFold +  "/shaders/solid.vert").c_str(),(resFold +  "/shaders/solid.frag").c_str());
    PointLight * pl = new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.1f), vec3(0.6f),vec3(1.0f),1.0f,0.09f,0.032f);
    
    Model * backpack = new Model(vec3(0.0f , 0.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",PhongShader);



    Model * all_axes = new Model(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(0.2f), resFold + "/models/Axes/all-axes.obj", SolidShader);



    game->bfc = new Basic_Flight_Controller(cam, 1.0f,1.0f);
    game->Register(pl);
    game->Register(all_axes);



    game->Register(backpack);


    game->GameLoop();

}



