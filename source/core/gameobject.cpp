//
// Created by Mathieu Monfort
// Date : 4/19/21.
// In Project : smallsquare
//

#include "gameobject.h"


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
    if(!GetParent(this)) {return GetLocalMatrix();}

    mat4 pMat = GetParent(this)->GetGlobalMatrix();
    return  GetParent(this)->GetGlobalMatrix() *  GetLocalMatrix();
}
mat4 smallsquare::GameObject::GetGlobalRotation(){
    if(!GetParent(this)) {return GetLocalRotation();}
    return GetParent(this)->GetGlobalRotation() * GetLocalRotation();
}
vec3 smallsquare::GameObject::GetGlobalPosition(){
    if(!GetParent(this)) {return GetLocalPosition();}
    return GetParent(this)->GetGlobalPosition() + GetLocalPosition();
}
vec3 smallsquare::GameObject::GetGlobalScale(){
    if(!GetParent(this)) {return GetLocalScale();}
    return GetParent(this)->GetGlobalScale() * GetLocalScale();
}

void smallsquare::GameObject::Tick(float deltaTime){}
void smallsquare::GameObject::CheckIntegrity() {}



void smallsquare::GameObject::Rotate(float amount, vec3 direction) {
    _rotation = rotate(_rotation, amount, direction);
}

void smallsquare::GameObject::LookAt(vec3 end) {
    LookAt(end, vec3(0, 1, 0));
}
void smallsquare::GameObject::LookAt(vec3 position, vec3 up) {
    _rotation = lookAt(GetGlobalPosition(),position, up);
}
void smallsquare::GameObject::Translate(vec3 translation) {
    _position += translation;
}

void smallsquare::GameObject::Place(vec3 position) {
    _position = position;
}

void smallsquare::GameObject::Scale(vec3 newScale) {
    _scale = newScale;
}

bool smallsquare::GameObject::IsActive() {
    if(!GetParent(this)) {return active;}
    if(GetParent(this)->IsActive()) {return active;}
    return false;
}

smallsquare::GameObject *smallsquare::GameObject::GetParent(smallsquare::GameObject *object) {
    return objectTree->ParentOf(object);
}

smallsquare::GameObject *smallsquare::GameObject::GetChild(smallsquare::GameObject *object, int i) {
    return objectTree->ChildOf(object, i);
}

vector<smallsquare::GameObject *> smallsquare::GameObject::GetChildren(smallsquare::GameObject *object) {
    return objectTree->ChildrenOf(object);
}

vector<smallsquare::GameObject *> smallsquare::GameObject::GetPathTo(smallsquare::GameObject *object) {
    return objectTree->PathTo(object);
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

void smallsquare::DrawableObject::Draw(mat4 projection, Camera * cam ,float ratio) { }

#pragma endregion
