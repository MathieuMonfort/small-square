//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_COLLISION_OBJECT_H
#define SMALLSQUARE_COLLISION_OBJECT_H

#include <game.h>
#include <collider_object.h>


namespace smallsquare {
    class ColliderObject;
    class CollisionObject :public GameObject {
    public:
        CollisionObject(vec3 position, vec3 euler, vec3 oscale, const string& name = "Collision Object") : GameObject(position, euler,oscale,name){

        }

        void Tick(float deltaTime) override;
        void CheckIntegrity() override;


        virtual void OnCollision(ColliderObject collider){}
    };
}


#endif //SMALLSQUARE_COLLISION_OBJECT_H
