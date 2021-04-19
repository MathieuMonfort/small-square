//
// Created by mmonfort on 4/14/21.
//

#include "raycast.h"

smallsquare::Box::Box(vec3 size) {
    this->size = size;
}

smallsquare::Plane::Plane(vec2 size){
    this->size = size;
}

smallsquare::Sphere::Sphere(float radius) {
    this->radius = radius;
}
