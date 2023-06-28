#include "model.h"
#include "camera_controller.h"

#include <ui_quad.h>
#include <canvas.h>

#include "config.h"
#include "debug.h"
#include <string>

using namespace std;
using namespace glm;
using namespace smallsquare;

class MyGame : public Game{
private:
    UIQuad * _uiElement;
    Model * _backpack;

    float _yScale = 1.0f;
public:
    MyGame() : Game(1280   ,720){
        string resFold = RESOURCE_FOLDER;
        auto o = new Origin();
        o->GetGlobalPosition();

        auto uielement = new Texture(resFold + "/textures/UI_Element.png");

        //Cams & Viewports
        auto cam = new Camera(vec3 (0.0f,0.0f,10.0f), vec3(0.0f,180.0f,0.0f));
        AddViewPort(cam);


        //Shaders
        auto phongShader = new Shader((resFold + "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
        auto solidShader = new Shader((resFold + "/shaders/solid.vert").c_str(), (resFold + "/shaders/solid.frag").c_str());
        auto uiShader = new Shader((resFold + "/shaders/basic_ui.vert").c_str(), (resFold + "/shaders/basic_ui.frag").c_str());
        //GameObjects

        _backpack = (Model* )Instantiate(new Model(vec3(0, 0, 0) , vec3(0, 0, 0), vec3(1, 1, 1) , resFold + "/models/Backpack/backpack.obj", phongShader, "BACKPACK" ) );
        Instantiate(new PointLight(vec3(3,3,3), vec3(0,0,0) ,vec3(1,1,1),vec3(1,1,1),vec3(1,1,1),1,1,1 ));
        Instantiate(new Model(vec3(3,3,3),vec3(0,0,0),vec3(1,1,1),resFold + "/models/Axes/all-axes.obj",solidShader ));
        auto canvas = Instantiate(new FixedCanvas());
        //_uiElement = (UIQuad *)Instantiate(new UIQuad(vec2(0.0f, 0.0f), 0.0f, vec2(1.0f, 0.5f),  uiShader,uielement,HA_CENTER, VA_CENTER),canvas);

        Input::AddInput(GLFW_KEY_KP_8, "UI_Up");
        Input::AddInput(GLFW_KEY_KP_2, "UI_Down");
        Input::AddInput(GLFW_KEY_KP_7, "UI_Left");
        Input::AddInput(GLFW_KEY_KP_6, "UI_Right");

    }

    void Tick() override{
        Game::Tick();
        /*if(Input::KeyPressed("UI_Up")){
            _uiElement->Rotate(pi<float>()/4,vec3(0,0,1));
        }
        if(Input::KeyPressed("UI_Down")){
            _uiElement->Rotate(-pi<float>()/4,vec3(0,0,1));
        }
        if(Input::KeyPressed("UI_Right")){
            _uiElement->Translate(vec3(0.1f, 0.0f,0.0f));
        }
        if(Input::KeyPressed("UI_Left")){
            _uiElement->Translate(vec3(-0.1f, 0.0f,0.0f));
        }
         */

        if(Input::KeyPressed("UI_Up")){
            _backpack->Rotate(radians((float)1), vec3(0, 1, 0));
        }
        if(Input::KeyPressed("UI_Down")){
            _backpack->Rotate(-radians((float)1), vec3(0, 1, 0));
        }
        if(Input::KeyPressed("UI_Right")){
            _yScale -= .1f;
            _backpack->Scale(vec3(1.0f, _yScale, 1.0f));
        }
        if(Input::KeyPressed("UI_Left")){
            _yScale += .1f;
            _backpack->Scale(vec3(1.0f, _yScale,1.0f));
        }



    }

};



int main([[maybe_unused]] int argc, [[maybe_unused]] char * argv[]){
    auto game = new MyGame();


    game->GameLoop();
}



