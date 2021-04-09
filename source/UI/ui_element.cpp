//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#include "ui_element.h"

vector<float> smallsquare::UIElement::vertices = {
    -1.0f,  1.0f,   0.0f,   0.0f,   0.0f,
    -1.0,   -1.0f,  0.0f,   0.0f,   1.0f,
    1.0f,   1.0f,   0.0f,   1.0f,   0.0f,

    1.0f,   1.0f,   0.0f,   1.0f,   0.0f,
    1.0f,   -1.0f,  0.0f,   1.0f,   1.0f,
    -1.0f,  -1.0f,  0.0f,   0.0f,   1.0f
};



void smallsquare::UIElement::CheckIntegrity() {
    for(auto &i :game->GetPathTo(this)  ){
        if(dynamic_cast<Canvas * >(i) ){
            canvas = (Canvas * ) i;
        }
    }

    if(!canvas) {
        cerr<< "ERROR IN OBJECT: " << name << "UIElement Not Assigned To Canvas";
    }
}

void smallsquare::UIElement::SetupMesh() {
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float), &vertices[0] , GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(float) *5, (void*)nullptr );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, sizeof(float) *5, (void* )(3* sizeof(float)  ));

    glBindVertexArray(0);
}

void smallsquare::UIElement::Draw(Viewport *viewport) {
    shader->use();
    shader->setFloat("alpha", alpha);

    shader->setInt("texture_ui", 0);
    shader->setMat4("model", GetGlobalMatrix());
    shader->setMat4("view", canvas->GetViewMatrix(viewport));
    shader->setMat4("projection", canvas->GetProjectionMatrix(viewport));

    background->BindToProcessor(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}