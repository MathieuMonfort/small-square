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

#include <camera.h>
#include <data_tree.h>
#include <gameobject.h>

#include <input.h>
#include <debug.h>
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

        /**
         * DO NOT USE Constructor for the Viewport class. Should only be called by the AddViewPort Function
         * from the Game class.
         * @param win Active GLFWwindow.
         * @param cam A pointer to a camera the viewport can get a View Matrix From.
         * @param x viewport position from the left on a 0 to 1 scale.
         * @param y viewport position from the top on a 0 to 1 scale.
         * @param width viewport width on a 0 to 1 scale.
         * @param height viewport height on a 0 to 1 scale.
         */
        Viewport(GLFWwindow *win, Camera *cam, float x = 0, float y = 0, float width = 1, float height = 1);

        /**
         * Get the viewport projection matrix.
         * @return A glm::mat4 matrix representing a projection matrix.
         */
        [[nodiscard]]
        mat4 GetProjectionMatrix() const;

        /**
         * Get the viewport's currently assigned camera's view matrix.
         * @return A glm::mat4 matrix representing a view matrix.
         */
        [[nodiscard]]
        mat4 GetViewMatrix() const;

        /**
         * Get the position of a point projected on the screen plane in world space.
         * @param x position of the projected point from the left.
         * @param y position of the projected point from the top.
         * @return a vec3 representing the position of a point in world space.
         */
        [[nodiscard]]
        vec3 ScreenToWorldSpace(int x, int y );

        /**
         * Get the viewport's current ratio.
         * @return The viewport's current ratio.
         */
        [[nodiscard]]
        float GetRatio();

        /**
         * Checks if a point of the current window is inside the viewport.
         * @param x position of the point in pixel from the left.
         * @param y position of the point in pixel from the top.
         * @return true if the point is inside the viewport, false if not.
         */
        [[nodiscard]]
        bool ContainsPixelPos(int x, int y);

        /**
         * Draws a list of objects on screen. Should be called by the game's Tick Function.
         * @param drawables The list of DrawableObjects to be drawn on screen.
         */
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

        /**
         * Constructor for the game class
         * @param width width of the game's window
         * @param height height of the game's window
         */
        explicit Game(int width = 1920, int height = 1080);

        /**
         * Adds a viewport to the game's list of viewport. (By default, every DrawableObject has to be rendered x times.
         * x being the number of instantiated viewports)
         * @param cam A pointer to a camera the viewport can get a View Matrix From.
         * @param x viewport position from the left on a 0 to 1 scale.
         * @param y viewport position from the top on a 0 to 1 scale.
         * @param w viewport width on a 0 to 1 scale.
         * @param h viewport height on a 0 to 1 scale.
         * @return A pointer to the instantiated viewport;
         */
        Viewport * AddViewPort(Camera * cam, float x = 0, float y = 0, float w = 1, float h =1);

        /**
         * Get The top most viewport under specified pixel coordinates.
         * @param x pixel coordinate from the left.
         * @param y pixel coordinate from the top.
         * @return pointer to top most viewport at coordinates.
         */
        Viewport * GetFirstViewportAtPixel(int x, int y);

        /**
         * Instantiate a GameObject in its parent's tree
         * @param object The GameObject to be instantiated
         * @param parent The GameObject's Parent
         * @return  Pointer to the newly created GameObject
         */
        GameObject * Instantiate(GameObject * object, GameObject * parent = nullptr);

        /**
         * Tick is called at every iteration of the game loop. It can be overridden to change object update priority.
         */
        virtual void Tick();

        /**
         * Main game loop function, should be called once at the end of your main function.
         */
        void GameLoop();

        /**
         * Get the parent of a GameObject in the current object tree
         * @param object A pointer to the child object
         * @return A pointer to the parent object
         */
        GameObject * GetParent(GameObject * object);

        /**
         * Get the child of a GameObject at index i in the current object tree
         * @param object a pointer to the parent object
         * @param i The index of the child object
         * @return A pointer to the child object
         */
        GameObject * GetChild(GameObject * object, int i);

        /**
         * Get a vector containing pointers to every children of a GameObject
         * @param object A pointer to the parent object
         * @return A vector of GameObject pointers or null if the parent object has no children
         */
        vector<GameObject *> GetChildren(GameObject * object);

        /**
         * Get a vector containing pointers to every GameObject between one object and the current tree root object.
         * It is organized so the lowest index represents the path's end and the highest index represents the tree root.
         * @param object A pointer to the path's end
         * @return A vector og GameObject pointers.
         */
        vector<GameObject *> GetPathTo(GameObject* object);


        /**
         * Get a vector containing pointers to every GameObject of a certain child type in the current object tree.
         * @tparam T The type of object to be searched for. It must be a pointer to a class derived from GameObject.
         * @return A vector containing objects of type T or an empty vector if there is no object of type T in the
         * current object tree.
         */
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

        /**
         * Get a vector containing pointers to every GameObject of a certain child type and with a given name
         * in the current object tree.
         * @tparam T The type of object to be searched for. It must be a pointer to a class derived from GameObject.
         * @param name The name of the searched for objects.
         * @return A vector containing objects of type T or an empty vector if there no object respects the type and
         * name condition in the current object tree.
         */
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