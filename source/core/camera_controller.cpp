//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "camera_controller.h"


void smallsquare::CameraController::Tick(float deltaTime){
    cam->position = GetGlobalPosition();
    cam->rotation = GetGlobalRotation();
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

