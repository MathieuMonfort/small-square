//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <list>
#include <iostream>
#include <data_tree.h>

#include <camera.h>
#include <debug.h>
#include <input.h>

using namespace std;
using namespace glm;


namespace smallsquare{
    class Game;
    class Viewport;




    class GameObject{
    private:
        vec3 _position = vec3(0.0f) ;
        mat4 _rotation= mat4(0.0f);
        vec3 _scale = vec3(0.0f) ;

    public:

        Game * game = nullptr;

        string name;
        bool active = true;


        GameObject(vec3 position, vec3 euler, vec3 oscale , const string& name = "GameObject");


        virtual vec3 GetLocalFront();
        virtual vec3 GetLocalRight();
        virtual vec3 GetLocalUp();
        virtual vec3 GetLocalPosition();
        virtual vec3 GetLocalScale();
        virtual mat4 GetLocalRotation();
        virtual mat4 GetLocalMatrix();



        virtual vec3 GetGlobalFront();
        virtual vec3 GetGlobalRight();
        virtual vec3 GetGlobalUp();
        virtual mat4 GetGlobalMatrix();
        virtual mat4 GetGlobalRotation();
        virtual vec3 GetGlobalPosition();
        virtual vec3 GetGlobalScale();

        virtual void Tick(float deltaTime){}
        virtual void CheckIntegrity(){}



        void Rotate(float amount , vec3 direction );
        void Translate(vec3 direction);
        void Scale(vec3 newScale);

        bool IsActive();
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

    class DrawableObject : public GameObject {
    public:
        bool visible = true;
        DrawableObject(vec3 position, vec3 euler, vec3 oscale, const string& name = "DrawableObject" ) : GameObject(position, euler, oscale, name) {}
        virtual void Draw(Viewport * viewport) {}
    };



    class Game{
    private:
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        tree<GameObject*> _object_tree = tree<GameObject *>(new Origin());
        GLFWwindow * _win;


    public:
        list<Viewport* > viewports;
        Input *input;


        explicit Game(int Width = 1920, int Height = 1080);
        Viewport * AddViewPort(Camera * cam, float x = 0, float y = 0, float w =1, float h =1);
        GameObject * Instanciate(GameObject * object, GameObject * parent = nullptr);
        virtual void Tick();
        void GameLoop();


        GameObject * GetParent(GameObject * object);
        GameObject * GetChild(GameObject * object, int i);
        vector<GameObject *> GetChildren(GameObject * object);
        vector<GameObject *> GetPathTo(GameObject* object);

        template <class T> vector<T> FindObjectsOfType() {
            vector<GameObject *> object_list = _object_tree.flatten();
            vector<T> result;

            for (auto &i :object_list ) {
                GameObject *go = i;

                if (dynamic_cast<T > (go)) {
                    T tObject = (T) go;
                    result.push_back(tObject);
                }
            }
            return result;
        }

        template <class T> vector<T> FindObjects(const string & name){
            vector<T> object_list = FindObjectsOfType<T>();
            vector<T> res;

            for(auto & i : object_list ){
                if(((GameObject *) i)->name == name ){
                    res.push_back(i);
                }
            }

            return res;
        }


    };



    class Viewport{
    private:
        float _x,_y,_w,_h;
        int _wWidth = 0;
        int _wHeight = 0;
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


        [[nodiscard]]
        mat4 GetProjectionMatrix() const;
        [[nodiscard]]
        mat4 GetViewMatrix() const;

        void Draw(vector<DrawableObject *> drawables);
    };


}


#endif