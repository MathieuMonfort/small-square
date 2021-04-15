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
        AddViewPort(cam, 0.5f, 0.0f, 0.2f, 0.5f );



        //Shaders
        auto PhongShader = new Shader((resFold +  "/shaders/basic_phong.vert").c_str(), (resFold + "/shaders/basic_phong.frag").c_str());
        auto SolidShader = new Shader((resFold +  "/shaders/solid.vert").c_str(),(resFold +  "/shaders/solid.frag").c_str());
        auto UIShader = new Shader((resFold +  "/shaders/basic_ui.vert").c_str(),(resFold +  "/shaders/basic_ui.frag").c_str());







        //Lights
        //auto pl = Instantiate(new PointLight(vec3(-3.0f),vec3(0.0f), vec3(0.8f), vec3(2.f),vec3(3.0f),1.0f,0.09f,0.032f));

        //Models
        auto backpack = Instantiate(new Model(vec3(0.0f , 0.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",PhongShader,"Back Pack" ));
        //auto backpack2 = Instantiate(new Model(vec3(0.0f , 3.0f  , 2.0f),vec3(0.0f),vec3(0.3f),resFold + "/models/Backpack/backpack.obj",SolidShader,"Back Pack 2" ));

        Instantiate(new Model(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), vec3(0.2f), resFold + "/models/Axes/all-axes.obj",
                              SolidShader));


        Instantiate(new FlightCamCon(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f), cam));

        input->AddInput( GLFW_KEY_A, "Move_Left");
        input->AddInput( GLFW_KEY_D, "Move_Right");
        input->AddInput( GLFW_KEY_W, "Move_Forward");
        input->AddInput( GLFW_KEY_S, "Move_Back");
        input->AddInput( GLFW_KEY_SPACE, "Move_Up");
        input->AddInput( GLFW_KEY_C, "Move_Down");

        //UI Stuff
        auto ui_texture = new Texture((resFold +  "/textures/UI_Element.png"));
        auto canvas = Instantiate(new FixedCanvas());

        /*
        auto ui_quad =(UIQuad *) Instantiate( new UIQuad(vec2(0.0f, -0.0f), 0.0f, vec2(0.2f), UIShader, ui_texture, HA_LEFT, VA_TOP), canvas);
        ui_quad->alpha = 0.5;

        Instantiate(new UIQuad(vec2(0.0f, 0.0f), 0.0f, vec2(0.2f), UIShader, ui_texture, HA_CENTER, VA_CENTER), canvas);
        Instantiate(new UIQuad(vec2(-0.0f, 0.0f), 0.0f, vec2(0.2f), UIShader, ui_texture, HA_RIGHT, VA_BOTTOM), canvas);
        */


    }

    void Tick() override{
        DEBUG::Clear();
        Game::Tick();

        DEBUG::Log("Mouse Pos" , input->MousePosition());
        auto vps = GetFirstViewportAtPixel(input->MousePosition().x , input->MousePosition().y);

        if(vps) {
            string log = "Current Viewport Ratio" + to_string(vps->GetRatio());
            DEBUG::Log(log);
        }
    }

};



int main(int argc, char * argv[]){

    auto game = new MyGame();
    game->GameLoop();
}



