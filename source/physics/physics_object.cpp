//
// Created by Mathieu Monfort
// Date : 4/5/21.
// In Project : smallsquare
//

#include "physics_object.h"
void smallsquare::PhysicsObject::Tick(float deltaTime){
    Translate(velocity);
}