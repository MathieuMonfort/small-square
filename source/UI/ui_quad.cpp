//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#include "ui_quad.h"

vector<float> smallsquare::UIQuad::vertices = {
    -1.0f,  1.0f,   0.0f,   0.0f,   0.0f,
    -1.0,   -1.0f,  0.0f,   0.0f,   1.0f,
    1.0f,   1.0f,   0.0f,   1.0f,   0.0f,

    1.0f,   1.0f,   0.0f,   1.0f,   0.0f,
    1.0f,   -1.0f,  0.0f,   1.0f,   1.0f,
    -1.0f,  -1.0f,  0.0f,   0.0f,   1.0f
};



void smallsquare::UIQuad::CheckIntegrity() {
    for(auto &i :game->GetPathTo(this)  ){
        if(dynamic_cast<Canvas * >(i) ){
            canvas = (Canvas * ) i;
        }
    }

    if(!canvas) {
        cerr<< "ERROR IN OBJECT: " << name << "UIQuad Not Assigned To Canvas";
    }
}

void smallsquare::UIQuad::SetupMesh() {
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

void smallsquare::UIQuad::Draw(Viewport *viewport) {
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

mat4 smallsquare::UIQuad::GetLocalMatrix() {
    float parentRatio =((UIElement *)game->GetParent(this))->ratio;

    vec3 Anchored;
    vec3 lscale = GetLocalScale();

    switch(HAnchor){
        case HA_CENTER :    Anchored.x = GetLocalPosition().x; break;
        case HA_LEFT :      Anchored.x = 2.0f * (GetLocalPosition().x + lscale.x/2 ) - 1.0f * parentRatio ; break;
        case HA_RIGHT :     Anchored.x = 2.0f * (GetLocalPosition().x - lscale.x/2 ) + 1.0f * parentRatio ; break;
    }

    switch(VAnchor){
        case VA_CENTER :    Anchored.y = GetLocalPosition().y ; break;
        case VA_TOP :       Anchored.y =  2.0f * (GetLocalPosition().y - lscale.y/2 ) + 1.0f ; break;
        case VA_BOTTOM :    Anchored.y =  2.0f * (GetLocalPosition().y + lscale.y/2 ) - 1.0f ; break;

    }

    Anchored.z = 0.0f;

    mat4 transMat = translate(mat4(1.0f), Anchored );
    mat4 scaleMat  = scale(mat4(1.0f), GetLocalScale() );

    return transMat * scaleMat * GetLocalRotation();
}
