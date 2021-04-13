//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_UI_QUAD_H
#define SMALLSQUARE_UI_QUAD_H

#include <game.h>
#include <canvas.h>
#include <shader.h>

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
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        static vector<float> vertices;

    public:
        float alpha = 1.0f;
        Canvas * canvas = nullptr;
        HorizontalAnchor HAnchor;
        VerticalAnchor VAnchor;
        Shader * shader;
        Texture * background;

        UIQuad(vec2 position,
               float rotation,
               vec2 oscale,
               Shader * shader,
               Texture * background,
               HorizontalAnchor HAnchor = HA_LEFT,
               VerticalAnchor VAnchor = VA_TOP,
               const string &name = "UIQuad"
                  )
                        : UIElement(vec3(position,0.0f), vec3(0.0f,0.0f,rotation), vec3(oscale, 0.0f),name ){


            this->HAnchor = HAnchor;
            this->VAnchor = VAnchor;
            this->shader = shader;
            this->background = background;

            SetupMesh();
        }

        void CheckIntegrity() override;
        void Tick(float deltaTime) override{


        }

        mat4 GetLocalMatrix() override;

        void Draw(Viewport * viewport) override;


    };

}

#endif //SMALLSQUARE_UI_QUAD_H
