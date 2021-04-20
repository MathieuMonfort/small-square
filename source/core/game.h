//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#ifndef SMALLSQUARE_GAME_H
#define SMALLSQUARE_GAME_H


#include <list>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <data_tree.h>
#include <gameobject.h>

#include <camera.h>
#include <input.h>

using namespace glm;
using namespace std;

namespace smallsquare{
    class GameObject;
    class DrawableObject;
    class Origin;

    class Viewport{
    private:
        float _x,_y,_w,_h;
        int _wWidth = 0;
        int _wHeight = 0;
        GLFWwindow * _win;

    public:
        Camera * cam;

        Viewport(GLFWwindow *win, Camera *cam, float x = 0, float y = 0, float width = 1, float height = 1);

        [[nodiscard]]
        mat4 GetProjectionMatrix() const;
        [[nodiscard]]
        mat4 GetViewMatrix() const;
        [[nodiscard]]
        vec3 ScreenToWorldSpace(int x, int y );
        [[nodiscard]]
        float GetRatio();
        [[nodiscard]]
        bool ContainsPixelPos(int x, int y);

        void Draw(vector<DrawableObject *> drawables);
    };
    class Game{
    private:

        float _lastFrame = 0.0f;
        Tree<GameObject*> * _objectTree;
        GLFWwindow * _win;

    protected:
        float _deltaTime = 0.0f;
        list<Viewport* > _viewports;


    public:

        explicit Game(int width = 1920, int height = 1080);
        Viewport * AddViewPort(Camera * cam, float x = 0, float y = 0, float w =1, float h =1);
        Viewport * GetFirstViewportAtPixel(int x, int y);
        GameObject * Instantiate(GameObject * object, GameObject * parent = nullptr);
        virtual void Tick();
        void GameLoop();

        GameObject * GetParent(GameObject * object);
        GameObject * GetChild(GameObject * object, int i);
        vector<GameObject *> GetChildren(GameObject * object);
        vector<GameObject *> GetPathTo(GameObject* object);



        template <class T> vector<T> FindObjectsOfType(){
            vector<GameObject *> objectList = _objectTree->Flatten();
            vector<T> result;

            for (auto &i :objectList) {
                GameObject *go = i;

                if (dynamic_cast<T > (go)) {
                    T tObject = (T) go;
                    result.push_back(tObject);
                }
            }
            return result;

        }

        template <class T> vector<T> FindObjects(const string & name){
            vector<T> objectList = FindObjectsOfType<T>();
            vector<T> result;

            for(auto & i : objectList ){
                if(((GameObject *) i)->name == name ){
                    result.push_back(i);
                }
            }

            return result;
        }

    };

}


#endif