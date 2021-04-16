//
// Created by mmonfort on 4/14/21.
//

#ifndef SMALLSQUARE_RAYCAST_H
#define SMALLSQUARE_RAYCAST_H
#include <game.h>

namespace smallsquare {
    struct Shape3D{

    };

    struct Box : Shape3D{
    public:
        vec3 size;

        explicit Box(vec3 size){
            this->size = size;
        }
    };

    struct Plane : Shape3D{
    public:
        vec2 size;

        explicit Plane(vec2 size){
            this->size = size;
        }
    };


    class Ray {


    };

    class RayCastCandidate{
    public:
        Shape3D shape;


        RayCastCandidate()=default;

        virtual void OnRaycastHit(Ray *ray) {

        }
    };
}

#endif //SMALLSQUARE_RAYCAST_H
