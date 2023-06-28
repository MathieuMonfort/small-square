//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "input.h"


float smallsquare::Input::_mLastX = 0;
float smallsquare::Input::_mLastY = 0;
float smallsquare::Input::_mXOffset = 0;
float smallsquare::Input::_mYOffset = 0;
int smallsquare::Input::_winW = 0;
int smallsquare::Input::_winH = 0;

float smallsquare::Input::_sensitivity = 0.001f;
bool smallsquare::Input::_firstMouse = true;
bool smallsquare::Input::_initialised = false;

GLFWwindow * smallsquare::Input::_win = nullptr;
vector<smallsquare::Action *> smallsquare::Input::_keymap;

smallsquare::Action::Action(const int key, string id) {
    this->key = key;
    this->id = std::move(id);
}


void smallsquare::Input::Init(GLFWwindow *win){
    Input::_win = win;
    glfwGetWindowSize(_win, &_winW, &_winH);
    Input::_initialised = true;
}

bool smallsquare::Input::KeyPressed(const string &name) {
    if(!_initialised) {return false;}
    auto pressed = false;
    for(auto & i : _keymap){
        if(i->id == name){
            pressed = glfwGetKey(_win, i->key) == GLFW_PRESS;
        }
    }
    return pressed;

}

void smallsquare::Input::MouseMoveCallback(GLFWwindow * win, double xpos, double ypos){
    if(_firstMouse)
    {
        _mLastX = (float)xpos;
        _mLastY = (float)ypos;
        _firstMouse = false;
    }


    _mXOffset = (float)xpos - _mLastX;
    _mYOffset = _mLastY - (float)ypos;

    _mLastX = (float)xpos;
    _mLastY = (float)ypos;
    _mXOffset *= _sensitivity;
    _mYOffset *= _sensitivity;
}

vec2 smallsquare::Input::MouseOffset(){
    return vec2(_mXOffset , _mYOffset );
}

vec2 smallsquare::Input::MousePosition() {
    return vec2(_mLastX, _mLastY);
}

void smallsquare::Input::Process() {
    Input::_mXOffset = 0;
    Input::_mYOffset = 0;
}

void smallsquare::Input::AddInput(int key, string id) {
    _keymap.push_back(new Action(key, id));
}

void smallsquare::Input::WindowSizeCallback(GLFWwindow *win, int h, int w) {
    _winW = w;
    _winH = h;
}

