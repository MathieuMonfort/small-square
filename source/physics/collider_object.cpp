//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#include "collider_object.h"




void smallsquare::ColliderObject::CheckIntegrity() {
    for (auto &i : GetPathTo(this)) {
        if (dynamic_cast<CollisionObject *>(i)) {
            cMaster = (CollisionObject *) i;
        }
        if (!cMaster) {
            cerr << "ERROR IN OBJECT: " << name << " Collider Object is not assigned to Collision Object";
        }
    }
}