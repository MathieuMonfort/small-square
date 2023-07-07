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
using namespace smallsquare::UI;


class MyGame : public Game{
private:
    UIQuad * _uiElement;
    UIQuad * _uiTarget;

    Model * _backpack;

    float totalOffset = 0;

    Ray* _ray;
    RaycastPlane * _plane;
    Camera *_cam;
    float _yScale = 1.0f;
public:
    MyGame() : Game(1280   ,720){
        string resFold = RESOURCE_FOLDER;

        auto uielement = new Texture(resFold + "/textures/UI_Element.png");
        auto uiTarget = new Texture(resFold + "/textures/center-target.png");

        //Cams & Viewports
        _cam = new Camera(vec3 (0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
        AddViewPort(_cam);


        //Shaders
        auto phongShader = new Shader((resFold + "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
        auto solidShader = new Shader((resFold + "/shaders/solid.vert").c_str(), (resFold + "/shaders/solid.frag").c_str());
        auto uiShader = new Shader((resFold + "/shaders/basic_ui.vert").c_str(), (resFold + "/shaders/basic_ui.frag").c_str());
        //GameObjects

        //_backpack = (Model* )Instantiate(new Model(vec3(0, 0, 0) , vec3(0, 0, 0), vec3(1, 1, 1) , resFold + "/models/Backpack/backpack.obj", phongShader, "BACKPACK" ) );
        Instantiate(new PointLight(vec3(3,3,3), vec3(0,0,0) ,vec3(1,1,1),vec3(1,1,1),vec3(1,1,1),1,1,1 ));
        Instantiate(new Model(vec3(3,3,3),vec3(0,0,0),vec3(1,1,1),resFold + "/models/Axes/all-axes.obj",solidShader ));

        auto canvas = Instantiate(new smallsquare::UI::Canvas(vec3(0,0,0), vec3(0,0,0), vec2(1)));
        _uiElement = (UIQuad *)Instantiate(new UIQuad(vec2(0.0f, 0.0f), 0.0f, vec2(1.0f, 1.0f),  uiShader,uielement,HA_CENTER, VA_CENTER),canvas);

        auto fCanvas = Instantiate(new FixedCanvas());
        _uiTarget = (UIQuad *)Instantiate(new UIQuad(vec2(0),0.0f, vec2(.4f) ,uiShader,uiTarget,HA_CENTER,VA_CENTER),fCanvas);
        Instantiate(new FlightCamCon(vec3(0,0,-10), vec3(0,0,0), _cam) );


        Instantiate(new Model(vec3(0,0,0), vec3(0,0,0), vec3(1,1,1), resFold + "/models/Spheres/ico-sphere.obj", solidShader));


        Input::AddInput(GLFW_KEY_W, "Move_Forward");
        Input::AddInput(GLFW_KEY_A, "Move_Left");
        Input::AddInput(GLFW_KEY_S, "Move_Back");
        Input::AddInput(GLFW_KEY_D, "Move_Right");


        Input::AddInput(GLFW_KEY_KP_8, "UI_Up");
        Input::AddInput(GLFW_KEY_KP_2, "UI_Down");
        Input::AddInput(GLFW_KEY_KP_7, "UI_Left");
        Input::AddInput(GLFW_KEY_KP_6, "UI_Right");

        _plane = (RaycastPlane*) Instantiate(new RaycastPlane(vec3(0.0f), vec3(0.0f), vec2(1.0f) ));


    }

    void Tick() override{
        Game::Tick();
        Debug::Clear();


        //if(Input::KeyPressed("UI_Up")){

        _ray = new Ray(_cam->position, _cam->GetFront(), 800.0f);
        if(_plane->IsIntersecting(_ray)) {
            Debug::Log("Intersect");
        }
        else{
            Debug::Log("Not Intersecting");
        }
    }

};



int main([[maybe_unused]] int argc, [[maybe_unused]] char * argv[]){
    auto game = new MyGame();


    game->GameLoop();
}



