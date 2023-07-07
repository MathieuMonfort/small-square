//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "game.h"

#pragma region Game
smallsquare::Game::Game(int width, int height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _win = glfwCreateWindow(width, height, "SmallSquare - Game", nullptr, nullptr);
    if(!_win){
        cerr << "Failed to Create GLFW Window"<<endl;
        glfwTerminate();

    }

    glfwMakeContextCurrent(_win);

#ifndef CURSOR_DEBUG
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
#ifdef CURSOR_DEBUG
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif

    glfwSetWindowSizeCallback(_win, Input::WindowSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cerr << "Failed To Initialize GLAD;" << endl;
        glfwTerminate();
    }
    _objectTree = new Tree<GameObject *>(new Origin());
    _objectTree->GetRoot()->objectTree = _objectTree;
    glEnable(GL_DEPTH_TEST);
    Input::Init(_win);
}

smallsquare::Viewport * smallsquare::Game::AddViewPort(Camera * cam , float x, float y, float w , float h){
    auto res = new Viewport(_win,cam,x,y,w,h);
    _viewports.push_back(res);
    return res;
}

smallsquare::Viewport * smallsquare::Game::GetFirstViewportAtPixel(int x, int y) {
    int w, h;
    glfwGetWindowSize(_win, &w, &h );
    if(x > w || x < 0 || y > h || y < 0) {
        return nullptr;
    }
    for (auto i = _viewports.rbegin(); i != _viewports.rend(); ++i) {
        Viewport * current = (*i);
        if(current->ContainsPixelPos(x, y)  ){return *i;}

    }
    return nullptr;
}

smallsquare::GameObject * smallsquare::Game::Instantiate(GameObject * object, GameObject * parent)
{
    if(!object) {return nullptr;}

    object->objectTree = _objectTree;
    if(!parent) {
        _objectTree->Insert(object);
        return object;
    }
    _objectTree->Insert(object, parent);
    return object;
}

void smallsquare::Game::GameLoop()
{
    /*
    auto objectList = _objectTree->Flatten();
    for(auto & i : objectList){
        decltype(i) obj = i;
        obj->CheckIntegrity();
    }
    */

    while(!glfwWindowShouldClose(_win)){
        glClearColor(0.7f,0.7f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto currentFrame = (float) glfwGetTime();
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        smallsquare::Input::Process();
        Tick();

        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
}

void smallsquare::Game::Tick(){
    auto objectList = _objectTree->Flatten();
    for(auto & i : objectList){
        decltype(i) obj = i;
        if(obj->IsActive()) {
            obj->CheckIntegrity();
        }
    }

    for(auto & i : objectList){
        decltype(i) obj = i;
        if(obj->IsActive()) {
            obj->Tick(_deltaTime);
        }
    }

    auto drawables = FindObjectsOfType<DrawableObject *>();
    for(auto & i :_viewports){
        i->Draw(drawables);
    }
}

smallsquare::GameObject * smallsquare::Game::GetParent(GameObject * object){
    return _objectTree->ParentOf(object);
}

smallsquare::GameObject * smallsquare::Game::GetChild(GameObject * object, int i ){
    return _objectTree->ChildOf(object, i);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetChildren(GameObject *object){
    return _objectTree->ChildrenOf(object);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetPathTo(GameObject *object){
    return _objectTree->PathTo(object);
}


#pragma endregion

#pragma region Viewport
smallsquare::Viewport::Viewport(GLFWwindow *win, smallsquare::Camera *cam, float x, float y, float width,
                                float height) {
    this->cam = cam;
    _x= x;
    _y=y;
    _w = width;
    _h = height;
    _win = win;

}

mat4 smallsquare::Viewport::GetProjectionMatrix() const{
    return perspective(radians(45.0f), (float)(_w*(float)_wWidth) /(_h*(float)_wHeight) ,0.1f,100.0f);
}


mat4 smallsquare::Viewport::GetViewMatrix() const{
    return cam->GetView();
}

vec3 smallsquare::Viewport::ScreenToWorldSpace(int x, int y) {
    glfwGetWindowSize(_win, &_wWidth, &_wHeight );
    vec3 normalizedDeviceCoords = vec3((2.0f * (float)x) / (float) _wWidth - 1.0f,
                                       1.0f - (2.0f *(float)y) /(float)_wHeight,
                                       1.0f);


    vec4 homogeneousClipCoords = vec4 (normalizedDeviceCoords.x ,  normalizedDeviceCoords.y, -1.0f, 1.0f);

    vec4 eyeCoordinates = inverse(GetProjectionMatrix()) * homogeneousClipCoords;
    eyeCoordinates = vec4(eyeCoordinates.x, eyeCoordinates.y,-1.0f,0.0f );


    vec4 worldCoords = inverse(GetViewMatrix()) * eyeCoordinates ;
    vec3 translatedWorldCoords = vec3(normalize(worldCoords)) + cam->position;

    return worldCoords;
}

float smallsquare::Viewport::GetRatio(){
    glfwGetWindowSize(_win, &_wWidth, &_wHeight );
    return ((float) (_w*(float) _wWidth)/ (_h*(float) _wHeight ));
}

bool smallsquare::Viewport::ContainsPixelPos(int x, int y){
    glfwGetWindowSize(_win, &_wWidth, &_wHeight );
    int xOffset = (int) ((float) _wWidth * _x);
    int yOffset = (int) ((float) _wHeight * _y);

    int wSize = (int) ((float) _wWidth * _w);
    int hSize = (int) ((float) _wHeight * _h);


    return x < xOffset + wSize && x > xOffset && y < yOffset + hSize && y > yOffset ;
}

void smallsquare::Viewport::Draw(vector<DrawableObject *> drawables){

    glfwGetWindowSize(_win, &_wWidth, &_wHeight );

    int x = (int) (_x * (float)_wWidth );
    int y = (int) (_y * (float)_wHeight);
    int w = (int) (_w * (float)_wWidth );
    int h = (int) (_h * (float)_wHeight);

    glViewport(x,y,w,h);


    glClear(GL_DEPTH_BUFFER_BIT);

    for(auto & i : drawables){
        decltype(i) obj = i;
        if(obj->visible && obj->IsActive()) {
            obj->Draw(GetProjectionMatrix(), cam , GetRatio());
        }
    }
}


#pragma endregion
