//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include <game.h>

#pragma region Game
smallsquare::Game::Game(int Width, int Height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _win = glfwCreateWindow(Width,Height, "SmallSquare - Game",nullptr,nullptr);
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


    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cerr << "Failed To Initialize GLAD;" << endl;
        glfwTerminate();
    }

    _object_tree.GetRoot()->game = this;
    glEnable(GL_DEPTH_TEST);
    input = new Input(_win);
}

smallsquare::Viewport * smallsquare::Game::AddViewPort(Camera * cam , float x, float y, float w , float h){
    auto res = new Viewport(_win,cam,x,y,w,h);

    viewports.push_back(res);

    return res;
}

smallsquare::GameObject * smallsquare::Game::Instanciate(GameObject * object, GameObject * parent)
{
    if(!object) {return nullptr;}

    object->game = this;
    if(!parent) {
        _object_tree.insert(object);
        return object;
    }
    _object_tree.insert(object, parent);
    return object;
}

void smallsquare::Game::GameLoop()
{
    auto object_list = _object_tree.flatten();
    for(auto & i : object_list){
        decltype(i) obj = i;
        obj->CheckIntegrity();
    }

    while(!glfwWindowShouldClose(_win)){
        glClearColor(0.7f,0.7f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Tick();

        smallsquare::Input::Process();
        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
}

void smallsquare::Game::Tick(){
    auto object_list = _object_tree.flatten();
    for(auto & i : object_list){
        decltype(i) obj = i;
        if(obj->IsActive()) {
            obj->CheckIntegrity();
        }
    }

    for(auto & i : object_list){
        decltype(i) obj = i;
        if(obj->IsActive()) {
            obj->Tick(deltaTime);
        }
    }

    auto drawables = FindObjectsOfType<DrawableObject *>();
    for(auto & i :viewports){
        i->Draw(drawables);
    }
}



smallsquare::GameObject * smallsquare::Game::GetParent(GameObject * object){
    return _object_tree.ParentOf(object);
}

smallsquare::GameObject * smallsquare::Game::GetChild(GameObject * object, int i ){
    return _object_tree.ChildOf(object, i);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetChildren(GameObject *object){
    return _object_tree.ChildrenOf(object);
}

vector<smallsquare::GameObject *> smallsquare::Game::GetPathTo(GameObject *object){
    return _object_tree.PathTo(object);
}

#pragma endregion

#pragma region Viewport
void smallsquare::Viewport::Draw(vector<DrawableObject *> drawables){

    glfwGetWindowSize(_win, &_wWidth, &_wHeight );
    glViewport(_x * (float)_wWidth,_y * (float)_wHeight,_w * (float)_wWidth ,_h *(float)_wHeight );
    
    glClear( GL_DEPTH_BUFFER_BIT);

    for(auto & i : drawables){
        decltype(i) obj = i;
        if(obj->visible && obj->IsActive()) {
            obj->Draw(this);
        }
    } 
}

mat4 smallsquare::Viewport::GetProjectionMatrix() const{
    return perspective(radians(45.0f), (float)(_w*(float)_wWidth) /(_h*(float)_wHeight) ,0.1f,100.0f);
}

mat4 smallsquare::Viewport::GetViewMatrix() const{
    return _cam->GetView();
}
#pragma endregion

#pragma region GameObject
smallsquare::GameObject::GameObject(vec3 position, vec3 euler, vec3 oscale, const string& name){
    _rotation = mat4(1.0f);
    _rotation = rotate(_rotation, euler.x, vec3(1.0f, 0.0f, 0.0f));
    _rotation = rotate(_rotation, euler.y, vec3(0.0f, 1.0f, 0.0f));
    _rotation = rotate(_rotation, euler.z, vec3(0.0f, 0.0f, 1.0f));
    this->_position = position;
    this->_scale = oscale;
    this->name = name;
}

vec3 smallsquare::GameObject::GetLocalFront(){
    mat4 inv = inverse(_rotation);
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}
vec3 smallsquare::GameObject::GetLocalRight(){
    mat4 inv = inverse(_rotation);
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}
vec3 smallsquare::GameObject::GetLocalUp(){
    mat4 inv = inverse(_rotation);
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}
mat4 smallsquare::GameObject::GetLocalMatrix(){
    mat4 trans = translate(mat4(1.0f), _position);
    mat4 scalemat = scale(mat4(1.0f), _scale );

    return scalemat * trans * _rotation ;
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
    mat4 lmat = GetLocalMatrix();
    if(!game->GetParent(this)) {return GetLocalMatrix();}

    mat4 pmat = game->GetParent(this)->GetGlobalMatrix();
    return  game->GetParent(this)->GetGlobalMatrix() *  GetLocalMatrix();
}
mat4 smallsquare::GameObject::GetGlobalRotation(){
    if(!game->GetParent(this)) {return _rotation;}
    return game->GetParent(this)->GetGlobalRotation() * _rotation;
}
vec3 smallsquare::GameObject::GetGlobalPosition(){
    if(!game->GetParent(this)) {return _position;}
    return game->GetParent(this)->GetGlobalPosition() + _position;
}
vec3 smallsquare::GameObject::GetGlobalScale(){
    if(!game->GetParent(this)) {return _scale;}
    return game->GetParent(this)->GetGlobalScale() * _scale;
}

void smallsquare::GameObject::Rotate(float amount, vec3 direction) {
    _rotation = rotate(_rotation, amount, direction);
}

void smallsquare::GameObject::Translate(vec3 direction) {
    _position += direction;
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