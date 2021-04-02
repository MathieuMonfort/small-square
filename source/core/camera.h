#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

namespace smallsquare{
    class Camera {
    private:
        vec3 _front; 
        vec3 _right;
        vec3 _up;

    public:
        mat4 rotation;
        vec3 position;

        Camera(vec3 position, vec3 rotation);
        
        mat4 GetView() const;
        mat4 GetInvertedView() const;


        vec3 GetFront() const;
        vec3 GetRight() const;
        vec3 GetUp() const;

    };

    enum Direction{
        LEFT,
        RIGHT,
        FORWARD,
        BACK,
        UP,
        DOWN,
    };
    enum Rotation{
        ROLLCWISE,
        ROLLANTICWISE,

        PITCHUP,
        PITCHDOWN,

        YAWLEFT,
        YAWRIGHT,
    };


    class Basic_Flight_Controller{
    public:
        Basic_Flight_Controller(Camera * cam ,float MoveSpeed, float RotateSpeed);
        void Move(Direction dir, float deltaTime);
        void Rotate(Rotation rot, float deltaTime);
        void Rotate(Direction dir, float offset);

    private:
        Camera * cam;
        float MoveSpeed; 
        float RotateSpeed;

    };
};

#endif













