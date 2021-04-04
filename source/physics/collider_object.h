//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_COLLIDER_OBJECT_H
#define SMALLSQUARE_COLLIDER_OBJECT_H

#include <game.h>
#include <collision_object.h>

namespace smallsquare {
    class ColliderObject : public GameObject {
    public:
        CollisionObject * cMaster = nullptr;

        ColliderObject(vec3 position, vec3 euler,vec3 oscale);



    };
}

#endif //SMALLSQUARE_COLLIDER_OBJECT_H
