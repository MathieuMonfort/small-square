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
        vec3 size = vec3(0.0f);
        explicit Box(vec3 size);
    };

    struct Plane : Shape3D{
    public:
        vec2 size = vec2(0.0f);
        explicit Plane(vec2 size);
    };

    struct Sphere : Shape3D{
        float radius;
        explicit Sphere(float radius);
    };

    struct RayHitInfo{

    };

    class Ray : public GameObject{

    };

    class RayCastCandidate{
    public:
        Shape3D* shape =new Box(vec3(1.0f));

        RayCastCandidate()=default;
    };
}

#endif //SMALLSQUARE_RAYCAST_H
