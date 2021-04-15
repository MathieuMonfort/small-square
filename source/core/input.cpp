//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "input.h"


float smallsquare::Input::mlastx = 0;
float smallsquare::Input::mlasty = 0;
float smallsquare::Input::mxoffset = 0;
float smallsquare::Input::myoffset = 0;
int smallsquare::Input::winw = 0;
int smallsquare::Input::winh = 0;

float smallsquare::Input::sensitivity = 0.001f;
bool smallsquare::Input::firstmouse = true;
bool smallsquare::Input::initialised = false;

GLFWwindow * smallsquare::Input::_win = nullptr;
vector<smallsquare::Action *> smallsquare::Input::keymap;




void smallsquare::Input::Init(GLFWwindow *win){
    Input::_win = win;
    glfwGetWindowSize(_win, &winw,&winh);
    Input::initialised = true;
}


bool smallsquare::Input::KeyPressed(const string &name) {
    if(!initialised) {return false;}
    auto pressed = false;
    for(auto & i : keymap){
        if(i->id == name){
            pressed = glfwGetKey(_win, i->key) == GLFW_PRESS;
        }
    }
    return pressed;

}

void smallsquare::Input::MouseMoveCallback(GLFWwindow * win, double xpos, double ypos){
    if(firstmouse)
    {
        mlastx = (float)xpos;
        mlasty = (float)ypos;
        firstmouse = false;
    }


    mxoffset = (float)xpos - mlastx;
    myoffset = mlasty - (float)ypos;

    mlastx = (float)xpos;
    mlasty = (float)ypos;
    mxoffset *= sensitivity;
    myoffset *= sensitivity;
}


vec2 smallsquare::Input::MouseOffset(){
    return vec2(mxoffset ,myoffset );
}

vec2 smallsquare::Input::MousePosition() {
    return vec2(mlastx,(float)winh - mlasty);
}

void smallsquare::Input::Process() {
    Input::mxoffset = 0;
    Input::myoffset = 0;
}

void smallsquare::Input::AddInput(int key, string id) {
    keymap.push_back(new Action(key, id));
}

void smallsquare::Input::WindowSizeCallback(GLFWwindow *win, int h, int w) {
    winw = w;
    winh = h;
}