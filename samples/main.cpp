#include <model.h>
#include <camera_controller.h>
#include "config.h"


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

    auto game = new Game();
    auto cam = new Camera(vec3 (0.0f), vec3(0.0f));
    game->AddViewPort(cam);

    
    string resFold = RESOURCE_FOLDER;
    auto PhongShader = new Shader((resFold +  "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
    auto SolidShader = new Shader((resFold +  "/shaders/solid.vert").c_str(),(resFold +  "/shaders/solid.frag").c_str());
    auto pl = new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.1f), vec3(0.6f),vec3(1.0f),1.0f,0.09f,0.032f);
    
    auto backpack = new Model(vec3(0.0f , 0.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",PhongShader);

    auto all_axes = new Model(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(0.2f), resFold + "/models/Axes/all-axes.obj", SolidShader);
    auto fcc = new FlightCamCon(vec3(0.0f, 0.0f,-5.0f ), vec3(0.0f),cam);

    game->Instanciate(pl);
    game->Instanciate(all_axes);
    game->Instanciate(fcc);


    game->Instanciate(backpack);

    game->input->AddInput( GLFW_KEY_A, "Move_Left");
    game->input->AddInput( GLFW_KEY_D, "Move_Right");
    game->input->AddInput( GLFW_KEY_W, "Move_Forward");
    game->input->AddInput( GLFW_KEY_S, "Move_Back");
    game->input->AddInput( GLFW_KEY_SPACE, "Move_Up");
    game->input->AddInput( GLFW_KEY_C, "Move_Down");


    game->GameLoop();


    /*
    if( glfwGetKey(_win, GLFW_KEY_ESCAPE) == GLFW_PRESS){glfwSetWindowShouldClose(_win, true);}
    if( glfwGetKey(_win, GLFW_KEY_KP_4) == GLFW_PRESS) {bfc->Rotate(YAWLEFT, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_6) == GLFW_PRESS) {bfc->Rotate(YAWRIGHT, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_8) == GLFW_PRESS) {bfc->Rotate(PITCHDOWN, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_2) == GLFW_PRESS) {bfc->Rotate(PITCHUP, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_Q) == GLFW_PRESS) {bfc->Rotate(ROLLANTICWISE, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_E) == GLFW_PRESS) {bfc->Rotate(ROLLCWISE, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_W) == GLFW_PRESS) {bfc->Move(FORWARD,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_S) == GLFW_PRESS) {bfc->Move(BACK,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_A) == GLFW_PRESS) {bfc->Move(LEFT,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_D) == GLFW_PRESS) {bfc->Move(RIGHT, 0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_C) == GLFW_PRESS) {bfc->Move(DOWN, 0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS) {bfc->Move(UP, 0.1f);}
    */

}



