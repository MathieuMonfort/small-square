//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "input.h"


float smallsquare::Input::mlastx = 0;
float smallsquare::Input::mlasty = 0;
float smallsquare::Input::mxoffset = 0;
float smallsquare::Input::myoffset = 0;
float smallsquare::Input::sensitivity = 0.001f;
bool smallsquare::Input::firstmouse = true;



smallsquare::Input::Input(GLFWwindow *win){
    _win = win;
}


bool smallsquare::Input::KeyPressed(const string &name) {

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

void smallsquare::Input::Process() {
    Input::mxoffset = 0;
    Input::myoffset = 0;
}

void smallsquare::Input::AddInput(int key, string id) {
    keymap.push_back(new Action(key, id));
}