//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_UI_QUAD_H
#define SMALLSQUARE_UI_QUAD_H

#include "../../../core/source/game.h"
#include "canvas.h"
#include "../../../core/source/shader.h"


class Canvas;
enum VerticalAnchor{
    VA_TOP,
    VA_CENTER,
    VA_BOTTOM
};

enum HorizontalAnchor{
    HA_LEFT,
    HA_CENTER,
    HA_RIGHT
};


namespace smallsquare {
    class UIQuad : public UIElement{
    private :
        void SetupMesh();
        unsigned int _vao = 0;
        unsigned int _vbo = 0;
        static vector<float> _vertices;

    public:
        float alpha = 1.0f;
        Canvas * canvas = nullptr;
        HorizontalAnchor hAnchor;
        VerticalAnchor vAnchor;
        Shader * shader;
        Texture * background;

        UIQuad(vec2 position,
               float rotation,
               vec2 scale,
               Shader * shader,
               Texture * background,
               HorizontalAnchor hAnchor = HA_LEFT,
               VerticalAnchor vAnchor = VA_TOP,
               const string &name = "UIQuad"
                  )
                        : UIElement(vec3(position,0.0f), vec3(0.0f,0.0f,rotation), vec3(scale, 0.0f), name ){


            this->hAnchor = hAnchor;
            this->vAnchor = vAnchor;
            this->shader = shader;
            this->background = background;

            SetupMesh();
        }

        void CheckIntegrity() override;
        void Tick(float deltaTime) override{


        }

        mat4 GetLocalMatrix() override;

        void Draw(mat4 projection, Camera * cam, float ratio) override;


    };

}

#endif //SMALLSQUARE_UI_QUAD_H
