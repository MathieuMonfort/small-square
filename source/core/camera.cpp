#include <camera.h>
using namespace smallsquare;



Camera::Camera(vec3 position, vec3 euler){
    rotation = mat4(1.0f);
    rotation = rotate(rotation, radians(euler.x), vec3(1.0f,0.0f,0.0f));
    rotation = rotate(rotation, radians(euler.y), vec3(0.0f,1.0f,0.0f));
    rotation = rotate(rotation, radians(euler.z), vec3(0.0f,0.0f,1.0f));

    this->position = position;
}

vec3 Camera::GetFront() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[2][0], inv[2][1], inv[2][2]);
}

vec3 Camera::GetRight() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[0][0], inv[0][1], inv[0][2]);
}

vec3 Camera::GetUp() const {
    mat4 inv = inverse(rotation);
    return vec3(inv[1][0], inv[1][1], inv[1][2]);
}

mat4 Camera::GetView() const {
    return lookAt( position, position + GetFront(),GetUp() );
}

mat4 Camera::GetInvertedView() const {
    return inverse(GetView());
}


Basic_Flight_Controller::Basic_Flight_Controller(Camera * cam, float MoveSpeed, float RotateSpeed){
    this->cam = cam;
    this->MoveSpeed = MoveSpeed;
    this->RotateSpeed = RotateSpeed;
}

void Basic_Flight_Controller::Move(Direction dir, float deltaTime){
    switch(dir){
        case Direction::FORWARD: cam->position +=  MoveSpeed * deltaTime * cam->GetFront() ; break;
        case Direction::BACK: cam->position -=  MoveSpeed * deltaTime * cam->GetFront() ;  break;
        case Direction::LEFT: cam->position +=  MoveSpeed * deltaTime * cam->GetRight() ;  break;
        case Direction::RIGHT: cam->position -=  MoveSpeed * deltaTime * cam->GetRight() ; break;
        case Direction::UP: cam->position +=  MoveSpeed * deltaTime * cam->GetUp() ; break;
        case Direction::DOWN: cam->position -=  MoveSpeed * deltaTime * cam->GetUp() ; break;
    }
}

void Basic_Flight_Controller::Rotate(Rotation rot, float deltaTime){
    switch(rot){
        case Rotation::PITCHUP: cam->rotation = rotate(cam->rotation, RotateSpeed * deltaTime, cam->GetRight()); break;
        case Rotation::PITCHDOWN: cam->rotation = rotate(cam->rotation, - RotateSpeed * deltaTime, cam->GetRight()); break;
        case Rotation::YAWLEFT: cam->rotation = rotate(cam->rotation, - RotateSpeed * deltaTime, cam->GetUp()); break;
        case Rotation::YAWRIGHT: cam->rotation = rotate(cam->rotation,  RotateSpeed * deltaTime, cam->GetUp()); break;
        case Rotation::ROLLANTICWISE: cam->rotation = rotate(cam->rotation, RotateSpeed * deltaTime, cam->GetFront()); break;
        case Rotation::ROLLCWISE: cam->rotation = rotate(cam->rotation, - RotateSpeed * deltaTime, cam->GetFront()); break;
    }
}

void Basic_Flight_Controller::Rotate(Direction dir, float offset)
{
    switch(dir){
        case Direction::FORWARD: cam->rotation = rotate(cam->rotation, offset, cam->GetFront()); break;
        case Direction::RIGHT: cam->rotation = rotate(cam->rotation, offset, cam->GetRight()); break;
        case Direction::UP: cam->rotation = rotate(cam->rotation, offset, cam->GetUp()); break; 
    }
}
