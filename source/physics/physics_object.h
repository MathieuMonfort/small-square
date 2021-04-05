//
// Created by Mathieu Monfort
// Date : 4/5/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_PHYSICS_OBJECT_H
#define SMALLSQUARE_PHYSICS_OBJECT_H

#include <collision_object.h>

namespace smallsquare {
    class PhysicsObject : public CollisionObject{
    public:
        vec3 velocity  =vec3(0.0f);

        PhysicsObject(vec3 position, vec3 euler, vec3 oscale, const string& name = "PhysicsObject") : CollisionObject(position, euler, oscale, name){

        }

        void Tick(float deltaTime) override;
    };
}


#endif //SMALLSQUARE_PHYSICS_OBJECT_H
