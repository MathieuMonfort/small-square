//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_COLLISION_OBJECT_H
#define SMALLSQUARE_COLLISION_OBJECT_H

#include "../../../core/source/game.h"
#include "collider_object.h"


namespace smallsquare {
    class ColliderObject;
    class CollisionObject :public GameObject {
    public:

        /**
         * Constructor for the CollisionObject class. It's useless on it's own and is made to be overridden into
         * physics objects and static objects.
         * @param position The CollisionObject's initial position.
         * @param euler The CollisionObject's initial euler rotation (applied in XYZ order).
         * @param s The CollisionObject's initial scale.
         * @param name The CollisionObject's name.
         */
        CollisionObject(vec3 position, vec3 euler, vec3 s, const string& name = "Collision Object") : GameObject(position, euler, s, name){

        }

        void CheckIntegrity() override;


        virtual void OnCollision(ColliderObject *collider){}
    };
}


#endif //SMALLSQUARE_COLLISION_OBJECT_H
