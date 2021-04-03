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
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
    while(!glfwWindowShouldClose(_win)){
        glClearColor(0.7f,0.7f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Tick();

        input->Process();
        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
}

void smallsquare::Game::Tick(){
    auto object_list = _object_tree.flatten();
    for(auto & i : object_list){
        decltype(i) obj = i;
        obj->Tick(deltaTime);
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
        obj->Draw(this);
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
smallsquare::GameObject::GameObject(vec3 position, vec3 euler, vec3 oscale){
    rotation = mat4(1.0f);
    rotation = rotate(rotation, euler.x, vec3(1.0f,0.0f,0.0f)); 
    rotation = rotate(rotation, euler.y, vec3(0.0f,1.0f,0.0f)); 
    rotation = rotate(rotation, euler.z, vec3(0.0f,0.0f,1.0f));
    this->position = position;
    this->oscale = oscale;
}

vec3 smallsquare::GameObject::GetLocalFront(){
    mat4 inv = inverse(rotation);
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}
vec3 smallsquare::GameObject::GetLocalRight(){
    mat4 inv = inverse(rotation);
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}
vec3 smallsquare::GameObject::GetLocalUp(){
    mat4 inv = inverse(rotation);
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}
mat4 smallsquare::GameObject::GetLocalMatrix(){
    mat4 trans = translate(mat4(1.0f),position);
    return trans * scale(rotation , oscale );
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
    if(!game->GetParent(this)) {return GetLocalMatrix();}
    return  game->GetParent(this)->GetGlobalMatrix() *  GetLocalMatrix();
}
mat4 smallsquare::GameObject::GetGlobalRotation(){
    if(!game->GetParent(this)) {return rotation;}
    return  game->GetParent(this)->GetGlobalRotation() *  rotation;
}
vec3 smallsquare::GameObject::GetGlobalPosition(){
    if(!game->GetParent(this)) {return position;}
    return  game->GetParent(this)->GetGlobalPosition() + position;
}
vec3 smallsquare::GameObject::GetGlobalScale(){
    if(!game->GetParent(this)) {return oscale;}
    return game->GetParent(this)->GetGlobalScale() * oscale;
}


#pragma endregion