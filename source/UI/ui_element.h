//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_UI_ELEMENT_H
#define SMALLSQUARE_UI_ELEMENT_H

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
    class UIElement : public DrawableObject{
    private :
        void SetupMesh();
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        static vector<float> vertices;

    public:
        Canvas * canvas = nullptr;
        HorizontalAnchor HAnchor;
        VerticalAnchor VAnchor;
        Shader * shader;
        Texture * background;

        UIElement(vec2 position,
                  float rotation,
                  vec2 oscale,
                  Shader * shader,
                  Texture * background,
                  const string &name = "UIElement",
                  HorizontalAnchor HAnchor = HA_LEFT,
                  VerticalAnchor VAnchor = VA_TOP )
                        : DrawableObject(vec3(position,0.0f), vec3(0.0f,0.0f,rotation), vec3(oscale, 1.0f),name ){


            this->HAnchor = HAnchor;
            this->VAnchor = VAnchor;
            this->shader = shader;
            this->background = background;

            SetupMesh();
        }

        void CheckIntegrity() override;
        void Draw(Viewport * viewport) override;


    };

}

#endif //SMALLSQUARE_UI_ELEMENT_H
