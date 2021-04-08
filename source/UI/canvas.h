//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_CANVAS_H
#define SMALLSQUARE_CANVAS_H

#include <game.h>

namespace  smallsquare {
    class Canvas : public GameObject{

    public:

        Canvas(vec3 position, vec3 euler, vec2 oscale, const string& name = "Canvas" ): GameObject( position , euler, vec3(oscale,0.0f ), name ){}
    };
}


#endif //SMALLSQUARE_CANVAS_H
