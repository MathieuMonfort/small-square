//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "camera_controller.h"




smallsquare::CameraController::CameraController(vec3 position, vec3 euler, smallsquare::Camera *cam) : GameObject( position, euler, vec3(1.0f) ){
    this->cam = cam;
}

void smallsquare::CameraController::Tick(float deltaTime){
    cam->position = GetGlobalPosition();
    cam->rotation = GetGlobalRotation();
}


smallsquare::FlightCamCon::FlightCamCon(vec3 position, vec3 euler, smallsquare::Camera *cam, float moveSpeed)
                        : CameraController(position, euler, cam){
    this->_moveSpeed = moveSpeed;
}

void smallsquare::FlightCamCon::Tick(float deltaTime){
    CameraController::Tick(deltaTime);

    if(Input::KeyPressed("Move_Left")){
        Translate(_moveSpeed * deltaTime * GetLocalRight());
    }
    if(Input::KeyPressed("Move_Right")){
        Translate(- _moveSpeed * deltaTime * GetLocalRight());
    }
    if(Input::KeyPressed("Move_Forward")){
        Translate(_moveSpeed * deltaTime * GetLocalFront());
    }
    if(Input::KeyPressed("Move_Back")){
        Translate(- _moveSpeed * deltaTime * GetLocalFront());
    }
    if(Input::KeyPressed("Move_Up")){
        Translate(_moveSpeed * deltaTime * GetLocalUp());
    }
    if(Input::KeyPressed("Move_Down")){
        Translate(- _moveSpeed * deltaTime * GetLocalUp());
    }

    Rotate(smallsquare::Input::MouseOffset().x,  GetLocalUp());
    Rotate(smallsquare::Input::MouseOffset().y,  GetLocalRight());
}


