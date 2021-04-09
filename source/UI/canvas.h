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

        virtual mat4 GetProjectionMatrix(Viewport * viewport){
            return viewport->GetProjectionMatrix();
        }
        virtual mat4 GetViewMatrix(Viewport * viewport){
            return viewport->GetViewMatrix();
        }
    };

    class FixedCanvas : public Canvas{
    public:
        explicit FixedCanvas(const string& name = "FixedCanvas") : Canvas(vec3(0.0f), vec3(0.0f), vec3(1.0f),name){}

        mat4 GetGlobalMatrix() override{
            return mat4(1.0f);
        }
        mat4 GetProjectionMatrix(Viewport * viewport) override {
            return mat4(1.0f);
        }
        mat4 GetViewMatrix(Viewport * viewport) override {
            return mat4(1.0f);
        }

    };
}


#endif //SMALLSQUARE_CANVAS_H
