//
// Created by Mathieu Monfort
// Date : 7/29/23
// In Project : smallsquare
// Copyright (c) Mathieu Monfort
//a
#define BOOST_TEST_MODULE Small Square Core Tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <game.h>

using namespace smallsquare;

BOOST_AUTO_TEST_CASE(game_creation){
    Game * g = new Game(1920,1080);
    int width;
    int height;

    BOOST_TEST(g != nullptr);
    glfwGetWindowSize( g->GetWindow(),&width,&height);
    BOOST_TEST(width == 1920);
    BOOST_TEST(height == 1080);


    g = new Game(300,300);
    BOOST_TEST(g != nullptr);
    glfwGetWindowSize( g->GetWindow(),&width,&height);
    BOOST_TEST(width == 300);
    BOOST_TEST(height == 300);
}

BOOST_AUTO_TEST_CASE(viewport_creation){
    Game * g = new Game(1920,1080);
    Viewport * v = g->AddViewPort(new Camera(vec3(0), vec3(0)), 0,0,1,1);
    BOOST_TEST(v != nullptr);
    BOOST_TEST(v == g->GetFirstViewportAtPixel(0,0));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1,1));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920,1080));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920-1,1080-1));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920/2,1080/2));

    Viewport * v2 = g->AddViewPort(new Camera(vec3(0), vec3(0)), 0,0,0.5,0.5);
    BOOST_TEST(v2 != nullptr);
    BOOST_TEST(v2 == g->GetFirstViewportAtPixel(0,0));
    BOOST_TEST(v2 == g->GetFirstViewportAtPixel(1,1));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920,1080));
    BOOST_TEST(v2 == g->GetFirstViewportAtPixel(1920/2,1080/2));
    BOOST_TEST(v2 == g->GetFirstViewportAtPixel(1920/2 -1,1080/2 -1));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920/2,1080/2 +1));
    BOOST_TEST(v == g->GetFirstViewportAtPixel(1920/2+1,1080/2));
}

class TestObject : public GameObject{
public:
    explicit TestObject(const string &name) : GameObject(vec3(0), vec3(0) , vec3(1),name  ){}
};
BOOST_AUTO_TEST_CASE(tree_integrity){
    Game * g = new Game(1920,1080);

    GameObject * go = g->Instantiate(new GameObject(vec3(0),vec3(0),vec3(1),"First Object"));
    auto parent = g->GetParent(go);
    auto root = g->GetRoot();

    BOOST_TEST(parent == root);


    GameObject * go2 = g->Instantiate(new GameObject(vec3(0),vec3(0),vec3(1),"Second Object") , go);
    GameObject * go3 = g->Instantiate(new GameObject(vec3(0),vec3(0),vec3(1),"Third Object"), go);

    BOOST_TEST(g->GetChild(go,0) == go2);
    BOOST_TEST(g->GetChild(go,1) == go3);

    auto p = g->GetPathTo(go2);

    BOOST_TEST(p.at(0) == root);
    BOOST_TEST(p.at(1) == go);
    BOOST_TEST(p.at(2) == go2);

    TestObject * to = (TestObject*)g->Instantiate(new TestObject("First Test Object"));
    TestObject * to2 = (TestObject*)g->Instantiate(new TestObject("Second Test Object"));
    TestObject * to3 = (TestObject*)g->Instantiate(new TestObject("Third Test Object"), to);



    auto oot = g->FindObjectsOfType<TestObject *>();
    BOOST_TEST(oot.size() == 3);
    BOOST_TEST(oot[0] == to);
    BOOST_TEST(oot[1] == to3);
    BOOST_TEST(oot[2] == to2);

    TestObject * tosm1 = (TestObject*)g->Instantiate(new TestObject("Same Name Object"));
    TestObject * tosm2 = (TestObject*)g->Instantiate(new TestObject("Same Name Object"));
    TestObject * tosm3 = (TestObject*)g->Instantiate(new TestObject("Same Name Object"),tosm1);

    auto oSameName = g->FindObjects<TestObject *>("Same Name Object");
    BOOST_TEST(oSameName.size() == 3);
    BOOST_TEST(oSameName[0] == tosm1);
    BOOST_TEST(oSameName[1] == tosm3);
    BOOST_TEST(oSameName[2] == tosm2);

}

//TODO: Test the ScreenToWorldSpace Function
