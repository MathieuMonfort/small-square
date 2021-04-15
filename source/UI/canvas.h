//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_CANVAS_H
#define SMALLSQUARE_CANVAS_H

#include <game.h>
#include <raycast.h>




namespace  smallsquare {
    class UIElement : public DrawableObject{
    public:
        float ratio = 1.0f;
        UIElement(vec3 position, vec3 euler, vec2 oscale, const string& name = "Canvas" ): DrawableObject( position , euler, vec3(oscale,0.0f ), name ){}

    };


class Canvas : public UIElement, public RayCastCandidate{
    public:
        Canvas(vec3 position, vec3 euler, vec2 oscale, const string& name = "Canvas" ): UIElement( position , euler, vec3(oscale,0.0f ), name),
                                                                                        RayCastCandidate()  {}

        virtual mat4 GetProjectionMatrix(Viewport * viewport){
            return viewport->GetProjectionMatrix();
        }
        virtual mat4 GetViewMatrix(Viewport * viewport){
            return viewport->GetViewMatrix();
        }
        void Draw(Viewport * viewport) override{
            ratio = viewport->GetRatio();
        }
    };

    class FixedCanvas : public Canvas{
    public:
        explicit FixedCanvas(const string& name = "FixedCanvas") : Canvas(vec3(0.0f), vec3(0.0f), vec3(1.0f),name){}

        mat4 GetGlobalMatrix() override{
            return mat4(1.0f);
        }
        mat4 GetProjectionMatrix(Viewport * viewport) override{
            return viewport->GetOrthoProjectionMatrix();
            return mat4(1.0f);
        }
        mat4 GetViewMatrix(Viewport * viewport) override{
            //return translate(mat4(1.0), vec3(0.0f, 0.0f, -2.0f )  );
            return mat4(1.0f);
        }
    };
}


#endif //SMALLSQUARE_CANVAS_H
