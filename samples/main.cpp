#include <model.h>
#include <camera_controller.h>

#include <ui_element.h>
#include <canvas.h>
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
        auto PhongShader = new Shader((resFold +  "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
        auto SolidShader = new Shader((resFold +  "/shaders/solid.vert").c_str(),(resFold +  "/shaders/solid.frag").c_str());
        auto UIShader = new Shader((resFold +  "/shaders/basic_ui.vert").c_str(),(resFold +  "/shaders/basic_ui.frag").c_str());


        //UI Stuff
        auto ui_texture = new Texture((resFold +  "/textures/UI_Element.png"));
        auto canvas = Instanciate(new FixedCanvas());
        auto ui_element =Instanciate(new UIElement(vec2(0.0f,0.0f), 0.0f,vec2(0.2f) ,UIShader , ui_texture),canvas);

        //Lights
        auto pl = Instanciate(new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.1f), vec3(0.6f),vec3(1.0f),1.0f,0.09f,0.032f));

        //Models
        auto backpack = Instanciate(new Model(vec3(0.0f , 0.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",PhongShader,"Back Pack" ));
        auto all_axes = Instanciate(new Model(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(0.2f), resFold + "/models/Axes/all-axes.obj", SolidShader));



        auto fcc = Instanciate(new FlightCamCon(vec3(0.0f, 0.0f,-5.0f ), vec3(0.0f),cam));

        input->AddInput( GLFW_KEY_A, "Move_Left");
        input->AddInput( GLFW_KEY_D, "Move_Right");
        input->AddInput( GLFW_KEY_W, "Move_Forward");
        input->AddInput( GLFW_KEY_S, "Move_Back");
        input->AddInput( GLFW_KEY_SPACE, "Move_Up");
        input->AddInput( GLFW_KEY_C, "Move_Down");


    }

    void Tick() override{
        Game::Tick();

        auto backpack = FindObjects<Model *>("Back Pack")[0];
        backpack->position += vec3(1.0f,0.0f,0.0f);


    }

};








int main(int argc, char * argv[]){

    auto game = new MyGame();
    game->GameLoop();


}



