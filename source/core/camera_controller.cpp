//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "camera_controller.h"


void smallsquare::CameraController::Tick(float deltaTime){
    cam->position = position;
    cam->rotation = rotation;
}


void smallsquare::FlightCamCon::Tick(float deltaTime){
    CameraController::Tick(deltaTime);

    if(game->input->KeyPressed("Move_Left")){
        position+= MoveSpeed * deltaTime * GetLocalRight();
    }
    if(game->input->KeyPressed("Move_Right")){
        position-= MoveSpeed * deltaTime * GetLocalRight();
    }
    if(game->input->KeyPressed("Move_Forward")){
        position+= MoveSpeed * deltaTime * GetLocalFront();
    }
    if(game->input->KeyPressed("Move_Back")){
        position -= MoveSpeed * deltaTime * GetLocalFront();
    }
    if(game->input->KeyPressed("Move_Up")){
        position += MoveSpeed * deltaTime * GetLocalUp();
    }
    if(game->input->KeyPressed("Move_Down")){
        position -= MoveSpeed * deltaTime * GetLocalUp();
    }

    rotation = rotate(rotation,smallsquare::Input::MouseOffset().x,  GetLocalUp());
    rotation = rotate(rotation,smallsquare::Input::MouseOffset().y,  GetLocalRight());


}

