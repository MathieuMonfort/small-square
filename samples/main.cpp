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

#include <camera_controller.h>
#include <physics_object.h>

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
    Camera * cam = new Camera(vec3 (0.0f), vec3(0.0f));
    game->AddViewPort(cam);

    
    string resFold = "/home/mmonfort/dev-space/small-square";
    resFold += "/samples";
    auto PhongShader = new Shader((resFold +  "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());


    //auto SolidShader = new Shader((resFold +  "/shaders/solid.vert").c_str(),(resFold +  "/shaders/solid.frag").c_str());


    auto pl = new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.1f), vec3(0.6f),vec3(1.0f),1.0f,0.09f,0.032f);
    auto backpack = new Model(vec3(0.0f , 0.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",PhongShader);
    auto mover = new PhysicsObject(vec3(0.0f), vec3(0.0f), vec3(1.0f) );
    auto fcc = new FlightCamCon(vec3(0.0f, 0.0f,-5.0f ), vec3(0.0f),cam);


    game->Instanciate(pl);
    game->Instanciate(fcc);
    game->Instanciate(mover);
    game->Instanciate(backpack, mover);


    game->input->AddInput( GLFW_KEY_A, "Move_Left");
    game->input->AddInput( GLFW_KEY_D, "Move_Right");
    game->input->AddInput( GLFW_KEY_W, "Move_Forward");
    game->input->AddInput( GLFW_KEY_S, "Move_Back");
    game->input->AddInput( GLFW_KEY_SPACE, "Move_Up");
    game->input->AddInput( GLFW_KEY_C, "Move_Down");


    game->GameLoop();
}



