//
// Created by Mathieu Monfort
// Date : 8/8/23
// In Project : small-square
// Copyright (c) Mathieu Monfort
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <game.h>

using namespace smallsquare;
BOOST_AUTO_TEST_CASE(active_state){
    Game * g = new Game();
    GameObject * go1 = g->Instantiate(new GameObject(vec3(0), vec3(0),vec3(1)));
    GameObject * go2 = g->Instantiate(new GameObject(vec3(0), vec3(0),vec3(1)), go1);
    GameObject * go3 = g->Instantiate(new GameObject(vec3(0), vec3(0),vec3(1)), go2);

    go3->active = true;
    go2->active = false;
    go1->active = true;


    BOOST_TEST(go1->IsActive());
    BOOST_TEST(!go2->IsActive());
    BOOST_TEST(!go3->IsActive());
}

BOOST_AUTO_TEST_CASE(translation){
    GameObject * go1 = new GameObject(vec3(0.0f), vec3(0.0f), vec3(1.0f));
    BOOST_TEST(glm::all(glm::equal(go1->GetLocalPosition(), vec3(0.0f))));

    go1->Translate(vec3(1.0f));
    BOOST_TEST(glm::all(glm::equal(go1->GetLocalPosition(), vec3(1.0f))));

    go1->Translate(vec3(-1.0f));
    BOOST_TEST(glm::all(glm::equal(go1->GetLocalPosition(), vec3(0.0f))));


}
