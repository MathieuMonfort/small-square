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
    private:
        float _moveSpeed;
        float _rotateSpeed;

    public :
        FlightCamCon(vec3 position, vec3 euler, Camera * cam, float moveSpeed = 1.0f, float rotateSpeed = 0.01f ) : CameraController(position, euler, cam){
        this->_moveSpeed = moveSpeed;
        this->_rotateSpeed = rotateSpeed;
        }

        void Tick(float deltaTime) override;
    };
}






#endif //SMALLSQUARE_CAMERA_CONTROLLER_H
