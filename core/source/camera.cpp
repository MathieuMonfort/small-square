//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include "camera.h"



smallsquare::Camera::Camera(vec3 position, vec3 euler){
    rotation = mat4(1.0f);
    rotation = rotate(rotation, radians(euler.x), vec3(1.0f,0.0f,0.0f));
    rotation = rotate(rotation, radians(euler.y), vec3(0.0f,1.0f,0.0f));
    rotation = rotate(rotation, radians(euler.z), vec3(0.0f,0.0f,1.0f));

    this->position = position;
}

vec3 smallsquare::Camera::GetFront() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}

vec3 smallsquare::Camera::GetRight() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}

vec3 smallsquare::Camera::GetUp() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}

mat4 smallsquare::Camera::GetView() const {
    return lookAt( position, position + GetFront(),GetUp() );
}

mat4 smallsquare::Camera::GetInvertedView() const {
    return inverse(GetView());
}