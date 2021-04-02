#include <game.h>
using namespace smallsquare;

Game::Game(unsigned int Width, unsigned int Height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _win = glfwCreateWindow(Width,Height, "Oglearn - Main Window",NULL,NULL);
    if(_win == NULL){
        cerr << "Failed to Create GLFW Window"<<endl;
        glfwTerminate();
        
    }

    glfwMakeContextCurrent(_win);
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //glfwSetCursorPosCallback(window, mouse_callback);


    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cerr << "Failed To Initialize GLAD;" << endl;
        glfwTerminate();
    }

    _object_tree.GetRoot()->game = this;
    glEnable(GL_DEPTH_TEST);
}

void Game::GameLoop()
{
    while(!glfwWindowShouldClose(_win)){
        glClearColor(0.7f,0.7f,0.7f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Tick();

        glfwSwapBuffers(_win);
        glfwPollEvents();
    }
}

Viewport * Game::AddViewPort(Camera * cam , float x, float y, float w , float h){
    Viewport  *res = new Viewport(_win,cam,x,y,w,h);
    
    viewports.push_back(res);

    return res;
}

void Game::Register(GameObject * object, GameObject * parent)
{
    object->game = this;
    if(object == NULL ) {return ;}
    if(parent == NULL) {
        _object_tree.insert(object);
        return;
    }
    _object_tree.insert(object, parent);
}

GameObject * Game::GetParent(GameObject * object){
    return _object_tree.ParentOf(object);
}



void Game::Tick(){

    if( glfwGetKey(_win, GLFW_KEY_ESCAPE) == GLFW_PRESS){glfwSetWindowShouldClose(_win, true);}
    if( glfwGetKey(_win, GLFW_KEY_KP_4) == GLFW_PRESS) {bfc->Rotate(YAWLEFT, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_6) == GLFW_PRESS) {bfc->Rotate(YAWRIGHT, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_8) == GLFW_PRESS) {bfc->Rotate(PITCHDOWN, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_KP_2) == GLFW_PRESS) {bfc->Rotate(PITCHUP, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_Q) == GLFW_PRESS) {bfc->Rotate(ROLLANTICWISE, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_E) == GLFW_PRESS) {bfc->Rotate(ROLLCWISE, 0.01f);}
    if( glfwGetKey(_win, GLFW_KEY_W) == GLFW_PRESS) {bfc->Move(FORWARD,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_S) == GLFW_PRESS) {bfc->Move(BACK,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_A) == GLFW_PRESS) {bfc->Move(LEFT,0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_D) == GLFW_PRESS) {bfc->Move(RIGHT, 0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_C) == GLFW_PRESS) {bfc->Move(DOWN, 0.1f);}
    if( glfwGetKey(_win, GLFW_KEY_SPACE) == GLFW_PRESS) {bfc->Move(UP, 0.1f);}



    list<GameObject *> object_list = _object_tree.flatten();
    for(list<GameObject *>::iterator it = object_list.begin(); it != object_list.end() ; it++){
        decltype((*it)) obj = (*it);
        obj->Tick();
    }

    list<DrawableObject *> drawables = FindObjectsOfType<DrawableObject *>();
    for(list<Viewport *>::iterator it = viewports.begin(); it != viewports.end() ; it++){
        (*it)->Draw(drawables);
    }

}


void Viewport::Draw(list<DrawableObject *> drawables){

    glfwGetWindowSize(_win, &_wWidth, &_wHeight );
    glViewport(_x * _wWidth,_y * _wHeight,_w *_wWidth ,_h *_wHeight );
    
    glClear( GL_DEPTH_BUFFER_BIT);

    for(list<DrawableObject *>::iterator it = drawables.begin() ; it != drawables.end(); it++ ){
        decltype((*it)) obj = (*it);
        obj->Draw(this);
    } 
}


GameObject::GameObject(vec3 position, vec3 euler, vec3 uscale){
    rotation = mat4(1.0f);
    rotation = rotate(rotation, euler.x, vec3(1.0f,0.0f,0.0f)); 
    rotation = rotate(rotation, euler.y, vec3(0.0f,1.0f,0.0f)); 
    rotation = rotate(rotation, euler.z, vec3(0.0f,0.0f,1.0f)); 
    
    this->position = position;
    this->uscale = uscale;
}

vec3 GameObject::GetLocalFront(){
    mat4 inv = inverse(rotation);
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}

vec3 GameObject::GetLocalRight(){
    mat4 inv = inverse(rotation);
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}

vec3 GameObject::GetLocalUp(){
    mat4 inv = inverse(rotation);
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}

mat4 GameObject::GetLocalMatrix(){ 
    mat4 trans = translate(mat4(1.0f),position);
    return trans * scale(rotation ,uscale );
}




vec3 GameObject::GetGlobalFront(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}

vec3 GameObject::GetGlobalRight(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}

vec3 GameObject::GetGlobalUp(){
    mat4 inv = inverse(GetGlobalRotation() );
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}




mat4 GameObject::GetGlobalMatrix(){
    return  game->GetParent(this)->GetGlobalMatrix() *  GetLocalMatrix();
}

mat4 GameObject::GetGlobalRotation(){
    return  game->GetParent(this)->GetGlobalRotation() *  rotation;
}
