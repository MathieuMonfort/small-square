//
// Created by Mathieu Monfort
// Date : 4/4/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_COLLISION_OBJECT_H
#define SMALLSQUARE_COLLISION_OBJECT_H

#include <game.h>

namespace smallsquare {
    class CollisionObject :public GameObject {
    public:
        void Tick(float deltaTime) override;
    };
}


#endif //SMALLSQUARE_COLLISION_OBJECT_H
