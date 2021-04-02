#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include <list>
#include <iostream>
#include <data_tree.h>

#include <camera.h>
#include <debug.h>

using namespace std;
using namespace glm;


#define W_HEIGHT 1080
#define W_WIDTH 1920



namespace smallsquare{

    class Game;
    class Viewport;
    class GameObject{
    public:
        Game * game;
        vec3 position;
        mat4 rotation;
        vec3 uscale;


        GameObject(vec3 position, vec3 euler, vec3 uscale);
        

        virtual vec3 GetLocalFront();
        virtual vec3 GetLocalRight();
        virtual vec3 GetLocalUp();
        virtual mat4 GetLocalMatrix();


        virtual vec3 GetGlobalFront();
        virtual vec3 GetGlobalRight();
        virtual vec3 GetGlobalUp();
        virtual mat4 GetGlobalMatrix();
        virtual mat4 GetGlobalRotation();



        virtual void Tick(){
        }
    };

    class DrawableObject : public GameObject {
    public:
        DrawableObject(vec3 position, vec3 euler, vec3 uscale) : GameObject(position, euler, uscale) {}
        virtual void Draw(Viewport * viewport) {}
    };


    class Origin : public GameObject{
    public:
        Origin() : GameObject(vec3(0.0f),vec3(0.0f),vec3(1.0f)){}
         vec3 GetLocalFront() override { return vec3(0.0f,0.0f,1.0f); }
         vec3 GetLocalRight() override { return vec3(0.0f,0.0f,1.0f); }
         vec3 GetLocalUp() override { return vec3(0.0f,0.0f,1.0f); }
         mat4 GetLocalMatrix() override{ return mat4(1.0f); }
         mat4 GetGlobalMatrix() override{return mat4(1.0f);}
         mat4 GetGlobalRotation() override{return mat4(1.0f);}

    };
    class Game{
    public:
        list<Viewport* > viewports;
        Basic_Flight_Controller * bfc;

        explicit Game(unsigned int Width = 1920, unsigned Height = 1080);
        explicit Game(Camera * maincam);
        Viewport * AddViewPort(Camera * cam, float x = 0, float y = 0, float w =1, float h =1);

        void Register(GameObject * object, GameObject * parent = NULL);
        GameObject * GetParent(GameObject * object);
        GameObject * GetChild(GameObject * object, int i);
        list<GameObject *> GetChildren(GameObject * object);
        list<GameObject *> GetPathTo(GameObject* object);

        template <class T> list<T> FindObjectsOfType(){
            list<GameObject*> object_list = _object_tree.flatten(); 
            list<T> result;
            for(list<GameObject *>::iterator it = object_list.begin(); it != object_list.end(); it++ ){
                GameObject * go = (*it);
                

                if( dynamic_cast<T > (go)){
                    T tObject = (T) go ;
                    result.push_back(tObject);
                }
            }
            return result;
        }
        
 
        void GameLoop();

    private:
        tree<GameObject*> _object_tree = tree<GameObject *>(new Origin()); 
        GLFWwindow * _win;
        void Tick();
    };

    class Viewport{
    private:
        float _x,_y,_w,_h;
        int _wWidth, _wHeight;
        GLFWwindow * _win;
    public:
        Camera * _cam;
        Viewport( GLFWwindow * win, Camera * cam,float x = 0, float y = 0, float width = 1, float height = 1){
            _cam = cam;
            _x= x;
            _y=y;
            _w = width;
            _h = height;
            _win = win;
        }

        mat4 GetProjectionMatrix(){
            return perspective(radians(45.0f), (float)(_w*_wWidth) /(_h*_wHeight) ,0.1f,100.0f);
        }

        mat4 GetViewMatrix(){
            return _cam->GetView();
        }


        void Draw(list<DrawableObject *> drawables);
    };






};


#endif