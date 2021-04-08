//
// Created by Mathieu Monfort
// Date : 4/8/21.
// In Project : smallsquare
//

#include "ui_element.h"

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

}