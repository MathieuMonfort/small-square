//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_CANVAS_H
#define SMALLSQUARE_CANVAS_H

#include <game.h>
#include <raycast.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace  smallsquare {
    class UIElement : public DrawableObject{

    public:
        float ratio = 1.0f;
        UIElement(vec3 position, vec3 euler, vec2 scale, const string& name = "Canvas" ): DrawableObject(position , euler, vec3(scale, 0.0f ), name ){}

    };


class Canvas : public UIElement, public RayCastCandidate{
    private:
        mat4 _projection;
        mat4 _view;
    public:
        Canvas(vec3 position, vec3 euler, vec2 scale, const string& name = "Canvas" ): UIElement(position , euler, vec3(scale, 0.0f ), name),
                                                                                       RayCastCandidate()  {}

        virtual mat4 GetProjectionMatrix(){
            return _projection;
        }
        virtual mat4 GetViewMatrix(){
            return _view;
        }
        void Draw(mat4 projection, Camera * cam , float ratio ) override{
           this->ratio = ratio;
           _view = cam->GetView();
           _projection = projection;
        }
    };

    class FixedCanvas : public Canvas{
    public:
        explicit FixedCanvas(const string& name = "FixedCanvas") : Canvas(vec3(0.0f), vec3(0.0f), vec3(1.0f),name){}

        mat4 GetGlobalMatrix() override{
            return mat4(1.0f);
        }
        mat4 GetProjectionMatrix() override{
            return ortho(-ratio ,ratio,-1.0f,1.0f);
        }
        mat4 GetViewMatrix() override{
            return translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.1f ) );
        }
    };
}


#endif //SMALLSQUARE_CANVAS_H
