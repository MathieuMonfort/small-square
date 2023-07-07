//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_CAMERA_CONTROLLER_H
#define SMALLSQUARE_CAMERA_CONTROLLER_H

#include "game.h"
#include "camera.h"
#include "debug.h"

namespace smallsquare {

    /**
     * A CameraController is a GameObject with a camera attached.
     * At each tick, it updates the Camera's position and rotation to it's position and rotation.
     * DON'T Forget to call the base class's Tick function when Inheriting.
     */
    class CameraController : public GameObject {
    public:
        Camera * cam;

        /**
         * Constructor for the CamController class.
         * @param position The controller's initial position.
         * @param euler The controller's initial euler rotation (applied in XYZ order).
         * @param cam A pointer to the camera that needs to be updated by the controller.
         */
        CameraController(vec3 position, vec3 euler , Camera * cam);

        /**
         * The tick function updates the Camera's position and rotation.
         * @param deltaTime The elapsed time in second since the last frame.
         */
        void Tick(float deltaTime) override ;
    };


    class FlightCamCon : public CameraController{
    private:
        float _moveSpeed;
        float _rotateSpeed;

    public :

        /**
         * Constructor for the FlightCamCon. It's an example functionnal Cam Controller. It will be moved in a specific
         * module in later builds. But it's useful to debug the core for now.
         * @param position The initial controller's position.
         * @param euler The initial controller's euler rotation (applied in XYZ order).
         * @param cam A pointer to the camera that needs to be updated by the controller.
         * @param moveSpeed The speed at which the controller will Move.
         */
        FlightCamCon(vec3 position, vec3 euler, Camera * cam, float moveSpeed = 1.0f) ;
        void Tick(float deltaTime) override;
    };
}






#endif //SMALLSQUARE_CAMERA_CONTROLLER_H
