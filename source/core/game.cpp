//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include <game.h>

#pragma region GameObject
smallsquare::GameObject::GameObject(vec3 position, vec3 euler, vec3 s, const string& name){
    _rotation = mat4(1.0f);
    _rotation = rotate(_rotation, euler.x, vec3(1.0f, 0.0f, 0.0f));
    _rotation = rotate(_rotation, euler.y, vec3(0.0f, 1.0f, 0.0f));
    _rotation = rotate(_rotation, euler.z, vec3(0.0f, 0.0f, 1.0f));
    this->_position = position;
    this->_scale = s;
    this->name = name;
}

vec3 smallsquare::GameObject::GetLocalFront(){
    mat4 inv = inverse(GetLocalRotation());
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}
vec3 smallsquare::GameObject::GetLocalRight(){
    mat4 inv = inverse(GetLocalRotation());
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}
vec3 smallsquare::GameObject::GetLocalUp(){
    mat4 inv = inverse(GetLocalRotation());
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}
mat4 smallsquare::GameObject::GetLocalMatrix(){
    mat4 transMat = translate(mat4(1.0f), GetLocalPosition());
    mat4 scaleMat = scale(mat4(1.0f), GetLocalScale() );

    return transMat * scaleMat * GetLocalRotation() ;
}

vec3 smallsquare::GameObject::GetLocalPosition() {
    return _position;
}

vec3 smallsquare::GameObject::GetLocalScale() {
    return _scale;
}

mat4 smallsquare::GameObject::GetLocalRotation() {
    return _rotation;
}



vec3 smallsquare::GameObject::GetGlobalFront(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}
vec3 smallsquare::GameObject::GetGlobalRight(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}
vec3 smallsquare::GameObject::GetGlobalUp(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}
mat4 smallsquare::GameObject::GetGlobalMatrix(){
    mat4 lMat = GetLocalMatrix();
    if(!game->GetParent(this)) {return GetLocalMatrix();}

    mat4 pMat = game->GetParent(this)->GetGlobalMatrix();
    return  game->GetParent(this)->GetGlobalMatrix() *  GetLocalMatrix();
}
mat4 smallsquare::GameObject::GetGlobalRotation(){
    if(!game->GetParent(this)) {return GetLocalRotation();}
    return game->GetParent(this)->GetGlobalRotation() * GetLocalRotation();
}
vec3 smallsquare::GameObject::GetGlobalPosition(){
    if(!game->GetParent(this)) {return GetLocalPosition();}
    return game->GetParent(this)->GetGlobalPosition() + GetLocalPosition();
}
vec3 smallsquare::GameObject::GetGlobalScale(){
    if(!game->GetParent(this)) {return GetLocalScale();}
    return game->GetParent(this)->GetGlobalScale() * GetLocalScale();
}

void smallsquare::GameObject::Tick(float deltaTime){}
void smallsquare::GameObject::CheckIntegrity() {}



void smallsquare::GameObject::Rotate(float amount, vec3 direction) {
    _rotation = rotate(_rotation, amount, direction);
}

void smallsquare::GameObject::LookAt(vec3 position) {
    LookAt(position, vec3(0,1,0));
}
void smallsquare::GameObject::LookAt(vec3 position, vec3 up) {
    _rotation = lookAt(GetLocalPosition(),position, up);
}
void smallsquare::GameObject::Translate(vec3 direction) {
    _position += direction;
}

void smallsquare::GameObject::Place(vec3 position) {
    _position = position;
}

void smallsquare::GameObject::Scale(vec3 newScale) {
    _scale = newScale;
}

bool smallsquare::GameObject::IsActive() {
    if(!game->GetParent(this)) {return active;}
    if(game->GetParent(this)->IsActive()) {return active;}
    return false;
}


#pragma endregion

#pragma region Origin
smallsquare::Origin::Origin() : GameObject(vec3(0.0f),vec3(0.0f),vec3(1.0f)){}

vec3 smallsquare::Origin::GetLocalFront() {
    return vec3(0.0f,0.0f,1.0f);
}

vec3 smallsquare::Origin::GetLocalRight() {
    return vec3(0.0f,0.0f,1.0f);
}

vec3 smallsquare::Origin::GetLocalUp() {
    return vec3(0.0f,0.0f,1.0f);
}

mat4 smallsquare::Origin::GetLocalMatrix() {
    return mat4(1.0f);
}

mat4 smallsquare::Origin::GetGlobalMatrix() {
    return mat4(1.0f);
}

mat4 smallsquare::Origin::GetGlobalRotation() {
    return mat4(1.0f);
}

#pragma endregion

#pragma region DrawableObject
smallsquare::DrawableObject::DrawableObject(vec3 position, vec3 euler, vec3 s, const string& name)
        : GameObject(position, euler, s, name) { }

void smallsquare::DrawableObject::Draw(smallsquare::Viewport *viewport) { }

#pragma endregion

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
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif

    glfwSetCursorPosCallback(_win, Input::MouseMoveCallback);
    glfwSetWindowSizeCallback(_win, Input::WindowSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cerr << "Failed To Initialize GLAD;" << endl;
        glfwTerminate();
    }

    _objectTree.GetRoot()->game = this;
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

    object->game = this;
    if(!parent) {
        _objectTree.Insert(object);
        return object;
    }
    _objectTree.Insert(object, parent);
    return object;
}

void smallsquare::Game::GameLoop()
{
    auto objectList = _objectTree.Flatten();
    for(auto & i : objectList){
        decltype(i) obj = i;
        obj->CheckIntegrity();
    }

    while(!glfwWindowShouldClose(_win)){
        glClearColor(0.7f,0.7f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto currentFrame = (float) glfwGetTime();
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        Tick();

        smallsquare::Input::Process();
        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
}

void smallsquare::Game::Tick(){
    auto objectList = _objectTree.Flatten();
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
    return _objectTree.ParentOf(object);
}

smallsquare::GameObject * smallsquare::Game::GetChild(GameObject * object, int i ){
    return _objectTree.ChildOf(object, i);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetChildren(GameObject *object){
    return _objectTree.ChildrenOf(object);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetPathTo(GameObject *object){
    return _objectTree.PathTo(object);
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

mat4 smallsquare::Viewport::GetOrthoProjectionMatrix(){
    const float ratio = GetRatio();
    return ortho(-ratio ,ratio,-1.0f,1.0f);
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
            obj->Draw(this);
        }
    }
}


#pragma endregion
