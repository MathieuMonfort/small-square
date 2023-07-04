//
// Created by mmonfort on 4/14/21.
//

#include "raycast.h"

smallsquare::Ray::Ray(vec3 origin, vec3 direction,float distance) {
    _origin = origin;
    _direction = direction;
    _distance = distance;
}

vec3 smallsquare::Ray::GetOrigin() {
    return _origin;
}

vec3 smallsquare::Ray::GetDirection() {
    return _direction;
}

float smallsquare::Ray::GetDistance() {
    return _distance;
}


smallsquare::RaycastCandidate::RaycastCandidate(vec3 position, vec3 euler, vec3 s, const string &name) : GameObject(
        position, euler, s, name) {
}


bool smallsquare::RaycastPlane::IsIntersecting(smallsquare::Ray * ray ) {
    vec3 rayOrigin = ray->GetOrigin();
    vec3 rayDirection = ray->GetDirection();
    vec3 vert0 = vec4(-1.0f,1.0f,0.0f,0.0f) * GetGlobalMatrix();
    vec3 vert1 = vec4(1.0f,1.0f,0.0f,0.0f) * GetGlobalMatrix();
    vec3 vert2 =  vec4(1.0f,-1.0f,0.0f,0.0f) *GetGlobalMatrix();;
    vec3 vert3 = vec4(-1.0f,-1.0f,0.0f,0.0f)* GetGlobalMatrix();
    vec2 intersectPosition;
    float distance= ray->GetDistance();
    bool intersects;

    intersects = glm::intersectRayTriangle(rayOrigin, rayDirection,vert0,vert1,vert2,intersectPosition ,distance);
    intersects = intersects || glm::intersectRayTriangle(rayOrigin, rayDirection,vert2,vert3,vert0,intersectPosition ,distance);
    return intersects;

}

smallsquare::RaycastPlane::RaycastPlane(vec3 position, vec3 euler, vec2 s, const string &name) : RaycastCandidate(
        position, euler, vec3(s,0.0f), name) {

}


smallsquare::RaycastBox::RaycastBox(vec3 position, vec3 rotation, vec3 scale, const string &name) : RaycastCandidate(
        position, rotation, scale, name) {

}

bool smallsquare::RaycastBox::IsIntersecting(smallsquare::Ray *ray) {
    return RaycastCandidate::IsIntersecting(ray);

    vec3 rayOrigin;
    vec3 rayDirection;
    vec3 sphereCenter;
    float sphereRadius;
    float intersectionDistance;
    bool Intersects = glm::intersectRaySphere(rayOrigin, rayDirection, sphereCenter, sphereRadius, intersectionDistance);



}

smallsquare::RaycastEllipsoid::RaycastEllipsoid(vec3 position, vec3 rotation, vec3 scale, const string &name)
        : RaycastCandidate(position, rotation, scale, name) {

}

bool smallsquare::RaycastEllipsoid::IsIntersecting(smallsquare::Ray *ray) {
    return RaycastCandidate::IsIntersecting(ray);
}

smallsquare::RaycastSphere::RaycastSphere(vec3 position, float radius, const string &name) : RaycastCandidate(position, vec3(0), vec3(radius), name){

}

bool smallsquare::RaycastSphere::IsIntersecting(smallsquare::Ray *ray) {

}
