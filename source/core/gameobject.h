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
         * of the working object tree.
         */
        virtual void CheckIntegrity();

        GameObject * GetParent(GameObject * object);
        GameObject * GetChild(GameObject * object, int i);
        vector<GameObject *> GetChildren(GameObject * object);
        vector<GameObject *> GetPathTo(GameObject* object);

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


        void Rotate(float amount, vec3 direction);
        void LookAt(vec3 position);
        void LookAt(vec3 position, vec3 up);
        void Translate(vec3 direction);
        void Place(vec3 position);
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
