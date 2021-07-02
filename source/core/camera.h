//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_CAMERA_H
#define SMALLSQUARE_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;
using namespace glm;

namespace smallsquare{
    class Camera {

    public:
        mat4 rotation = mat4(1.0f);
        vec3 position = vec3(1.0f);

        /**
         * The Constructor for the Camera class. A camera has a position and a pointing direction. It's used to provide
         * a view matrix along side a viewport's projection matrix.
         * @param position The camera's initial position (Unused if attached to a Camera Controller).
         * @param rotation The camera's initial euler rotation (applied in XYZ order)
         * (Unused if attached to a Camera Controller).
         */
        Camera(vec3 position, vec3 rotation);

        /**
         * Get the camera view matrix calculated with the current position and rotation matrix.
         * @return A mat4 representing the Camera's view.
         */
        [[nodiscard]]
        mat4 GetView() const;

        /**
         * Get the camera inverted view matrix.
         * @return A mat4 representing the Camera's view inverted to simplify shader calculations.
         */
        [[nodiscard]]
        mat4 GetInvertedView() const;

        /**
         * Get the camera's front vector calculated from the inverse rotation matrix.
         * @return a vec3 representing the camera's front direction.
         */
        [[nodiscard]]
        vec3 GetFront() const;

        /**
         * Get the camera's right vector calculated from the inverse rotation matrix.
         * @return a vec3 representing the camera's right direction.
         */
        [[nodiscard]]
        vec3 GetRight() const;


        /**
         * Get the camera's up vector calculated from the inverse rotation matrix.
         * @return a vec3 representing the camera's up direction.
         */
        [[nodiscard]]
        vec3 GetUp() const;

    };
}

#endif













