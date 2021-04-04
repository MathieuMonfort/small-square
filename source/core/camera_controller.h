//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_CAMERA_CONTROLLER_H
#define SMALLSQUARE_CAMERA_CONTROLLER_H

#include <game.h>

namespace smallsquare {
    class CameraController : public GameObject {
    public:
        Camera * cam;
        CameraController(vec3 position, vec3 euler , Camera * cam): GameObject( position, euler, vec3(1.0f) ){
            this->cam = cam;
        }
        void Tick(float deltaTime) override ;



    };


    class FlightCamCon : public CameraController{
        float MoveSpeed;
        float RotateSpeed;

    public :
        FlightCamCon(vec3 position, vec3 euler, Camera * cam, float MoveSpeed = 1.0f, float RotateSpeed = 0.01f ) : CameraController(position, euler, cam){
        this->MoveSpeed = MoveSpeed;
        this->RotateSpeed = RotateSpeed;

        }

        void Tick(float deltaTime) override;
    };
}






#endif //SMALLSQUARE_CAMERA_CONTROLLER_H
