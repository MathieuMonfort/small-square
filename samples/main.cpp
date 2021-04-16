#include <model.h>
#include <camera_controller.h>

#include <ui_quad.h>
#include <canvas.h>
#include <debug.h>

#include "config.h"



using namespace std;
using namespace glm;
using namespace smallsquare;

class MyGame : public Game{
private:


public:
    MyGame() : Game(){
        string resFold = RESOURCE_FOLDER;

        //Cams & Viewports
        auto cam = new Camera(vec3 (0.0f), vec3(0.0f));

        AddViewPort(cam);

        //Shaders
        auto phongShader = new Shader((resFold + "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
        auto solidShader = new Shader((resFold + "/shaders/solid.vert").c_str(), (resFold + "/shaders/solid.frag").c_str());
        auto uiShader = new Shader((resFold + "/shaders/basic_ui.vert").c_str(), (resFold + "/shaders/basic_ui.frag").c_str());






        Instantiate(new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.8f), vec3(2.f),vec3(3.0f),1.0f,0.09f,0.032f));
        Instantiate(new Model(vec3(0.0f , 0.0f  , 2.0f), vec3(0.0f), vec3(0.3f),resFold + "/models/Backpack/backpack.obj", phongShader, "Back Pack" ));
        Instantiate(new Model(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(0.2f), resFold + "/models/Axes/all-axes.obj", solidShader));

        Instantiate(new FlightCamCon(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f), cam));

        Input::AddInput( GLFW_KEY_A, "Move_Left");
        Input::AddInput( GLFW_KEY_D, "Move_Right");
        Input::AddInput( GLFW_KEY_W, "Move_Forward");
        Input::AddInput( GLFW_KEY_S, "Move_Back");
        Input::AddInput( GLFW_KEY_SPACE, "Move_Up");
        Input::AddInput( GLFW_KEY_C, "Move_Down");


    }

    void Tick() override{
        Debug::Clear();
        Game::Tick();
    }

};



int main([[maybe_unused]] int argc, [[maybe_unused]] char * argv[]){

    auto game = new MyGame();
    game->GameLoop();


    Debug::Log("Mouse position", vec2(Input::MousePosition().x, Input::MousePosition().y ) );
}



