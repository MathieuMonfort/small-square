//
// Created by Mathieu Monfort
// Date : 4/19/21.
// In Project : smallsquare
//

#ifndef SMALLSQUARE_GAMEOBJECT_H
#define SMALLSQUARE_GAMEOBJECT_H


#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <data_tree.h>
#include <camera.h>

using namespace glm;
using namespace std;

namespace smallsquare {
    class Viewport;

    class GameObject {
    private:
        vec3 _position = vec3(0.0f);
        mat4 _rotation = mat4(0.0f);
        vec3 _scale = vec3(0.0f);

    public:
        string name;
        bool active = true;
        Tree<GameObject*> * objectTree;

        /**
         * Constructor for the GameObject class.
         * @param position The initial GameObject's local position.
         * @param euler The initial GameObject's local rotation applied in XYZ order.
         * @param s The initial GameObject's local scale.
         * @param name The GameObject's name.
         */
        GameObject(vec3 position, vec3 euler, vec3 s, const string &name = "GameObject");

        /**
         * Get the local front vector calculated from the local rotation matrix.
         * @return A vec3 representing the GameObject's local front vector.
         */
        virtual vec3 GetLocalFront();

        /**
         * Get the local right vector calculated from the local rotation matrix.
         * @return A vec3 representing the GameObject's local right vector.
         */
        virtual vec3 GetLocalRight();

        /**
         * Get the local up vector calculated from the local rotation matrix.
         * @return A vec3 representing the GameObject's local up vector.
         */
        virtual vec3 GetLocalUp();

        /**
         * Get the current local position.
         * @return A vec3 representing the GameObject's local position.
         */
        virtual vec3 GetLocalPosition();

        /**
         * Get the current local scale.
         * @return A vec3 representing the GameObject's local scale.
         */
        virtual vec3 GetLocalScale();

        /**
         * Get the current local rotation matrix.
         * @return A mat4 representing the GameObject's local rotation.
         */
        virtual mat4 GetLocalRotation();

        /**
         * Get the current local transformation matrix calculated with the local position, scale and rotation matrix.
         * @return A mat4 representing the GameObject's local transformation.
         */
        virtual mat4 GetLocalMatrix();

        /**
         * Get the global front vector calculated from the global rotation matrix.
         * @return A vec3 representing the GameObject's global front vector.
         */
        virtual vec3 GetGlobalFront();

        /**
         * Get the global right vector calculated from the global rotation matrix.
         * @return A vec3 representing the GameObject's global right vector.
         */
        virtual vec3 GetGlobalRight();

        /**
         * Get the global up vector calculated from the global rotation matrix.
         * @return A vec3 representing the GameObject's global up vector.
         */
        virtual vec3 GetGlobalUp();

        /**
         * Get the current global position.
         * @return A vec3 representing the GameObject's global position.
         */
        virtual vec3 GetGlobalPosition();

        /**
         * Get the current global scale.
         * @return A vec3 representing the GameObject's global scale.
         */
        virtual vec3 GetGlobalScale();

        /**
         * Get the current global rotation matrix.
         * @return A mat4 representing the GameObject's global rotation.
         */
        virtual mat4 GetGlobalRotation();

        /**
         * Get the current global transformation matrix.
         * @return A mat4 representing the GameObject's global transformation.
         */
        virtual mat4 GetGlobalMatrix();

        /**
         * Tick is called by the game's tick function at every iteration of the game loop.
         * @param deltaTime The elapsed time in second since the last frame.
         */
        virtual void Tick(float deltaTime);

        /**
         * CheckIntegrity is initially called right before the main game loop starts. It is used to verify the integrity
         * of the working object tree. It should be overriden to had conditions to the tree integrity. It can be called
         * at any time.
         */
        virtual void CheckIntegrity();

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
            vector<GameObject *> objectList = objectTree->Flatten();
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
        template <class T> vector<T> FindObjects(const string & objectName){
            vector<T> objectList = FindObjectsOfType<T>();
            vector<T> result;

            for(auto & i : objectList ){
                if(((GameObject *) i)->name == objectName ){
                    result.push_back(i);
                }
            }

            return result;
        }

        /**
         * Rotate the game object an amount in degrees around a vector.
         * @param amount The amount in degrees the GameObject should be rotated
         * @param direction The vector the GameObject will be rotated around.
         */
        void Rotate(float amount, vec3 direction);

        /**
         * Generate a new rotation matrix with an up vector corresponding to the world's up vector and a front vector
         * starting at the GameObject's global position and ending at end (normalized).
         * @param end The point the GameObject will be oriented towards.
         */
        void LookAt(vec3 end);

        /**
         * Generate a new rotation matrix with a specified u vector and a front vector
         * starting at the GameObject's global position and ending at end (normalized).
         * @param end The point the GameObject will be oriented towards.
         */
        void LookAt(vec3 position, vec3 up);

        /**
         * Translate the GameObject by adding the current position and the specified vector
         * @param translation the vector the GameObject will be translated by.
         */
        void Translate(vec3 translation);

        /**
         * Set the GameObject at a position relative to it's parent.
         * @param position The position the GameObject will be set to in local space.
         */
        void Place(vec3 position);

        /**
         * Set the GameObject at a position in world space.
         * @param position The position the GameObject will be set to in wold space.
         */
        void PlaceInWorld(vec3 position);
        void Scale(vec3 newScale);

        bool IsActive();
    };

    class Origin : public GameObject {
    public:
        Origin();

        vec3 GetLocalFront() override;

        vec3 GetLocalRight() override;

        vec3 GetLocalUp() override;

        mat4 GetLocalMatrix() override;

        mat4 GetGlobalMatrix() override;

        mat4 GetGlobalRotation() override;
    };

    class DrawableObject : public GameObject {
    public:
        bool visible = true;

        DrawableObject(vec3 position, vec3 euler, vec3 s, const string &name = "DrawableObject");

        virtual void Draw(mat4 projection, Camera * cam, float ratio);
    };
}








#endif //SMALLSQUARE_GAMEOBJECT_H
