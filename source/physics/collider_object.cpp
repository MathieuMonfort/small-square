//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#include "collider_object.h"


smallsquare::ColliderObject::ColliderObject(vec3 position, vec3 euler,vec3 oscale) :GameObject(position, euler,oscale) {
    for (auto &i : game->GetPathTo(this)) {
        if (dynamic_cast<CollisionObject *>(i)) {
            cMaster = (CollisionObject *) i;
        }
        if (!cMaster) {
            cerr << "ERROR IN OBJECT: " << name << " Collider Object is not assigned to Collision Object";
        }
    }

}