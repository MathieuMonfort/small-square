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
        Translate( MoveSpeed * deltaTime * GetLocalRight());
    }
    if(Input::KeyPressed("Move_Right")){
        Translate( - MoveSpeed * deltaTime * GetLocalRight());
    }
    if(Input::KeyPressed("Move_Forward")){
        Translate( MoveSpeed * deltaTime * GetLocalFront());
    }
    if(Input::KeyPressed("Move_Back")){
        Translate( - MoveSpeed * deltaTime * GetLocalFront());
    }
    if(Input::KeyPressed("Move_Up")){
        Translate( MoveSpeed * deltaTime * GetLocalUp());
    }
    if(Input::KeyPressed("Move_Down")){
        Translate( - MoveSpeed * deltaTime * GetLocalUp());
    }

    Rotate(smallsquare::Input::MouseOffset().x,  GetLocalUp());
    Rotate(smallsquare::Input::MouseOffset().y,  GetLocalRight());


}

