//
// Created by mmonfort on 4/14/21.
//

#ifndef SMALLSQUARE_RAYCAST_H
#define SMALLSQUARE_RAYCAST_H
#include "game.h"

#include "glm/gtx/intersect.hpp"

namespace smallsquare {


    struct RayHitInfo{

    };

    class Ray{
        vec3 _origin;
        vec3 _direction;
        float _distance;
    public:
        Ray(vec3 origin , vec3 direction, float distance );

        vec3 GetOrigin();
        vec3 GetDirection();
        float GetDistance();



    };

    class RaycastCandidate : public GameObject{
    public:
        RaycastCandidate(vec3 position, vec3 euler, vec3 s, const string &name = "RaycastCandidate");
        virtual bool IsIntersecting(Ray * ray){return false;}

    };



    class RaycastPlane : public RaycastCandidate{
    public:
        explicit RaycastPlane(vec3 position, vec3 euler, vec2 s, const string &name = "RaycastPlane");
        bool IsIntersecting(Ray* ray) override;

    };

    class RaycastBox : public RaycastCandidate{
    public:
        explicit RaycastBox(vec3 position, vec3 rotation, vec3 scale, const string &name = "RaycastBox");
        bool IsIntersecting(Ray *ray) override;
    };
    class RaycastEllipsoid : public RaycastCandidate{
        explicit RaycastEllipsoid(vec3 position, vec3 rotation, vec3 scale, const string &name = "RaycastEllipsoid");
        bool IsIntersecting(Ray* ray) override;
    };

    class  RaycastSphere: public RaycastCandidate{
        explicit RaycastSphere(vec3 position, float radius, const string &name = "RaycastSphere");
        bool IsIntersecting(Ray *ray) override;
    };
}

#endif //SMALLSQUARE_RAYCAST_H
