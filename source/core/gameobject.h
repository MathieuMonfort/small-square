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


        GameObject(vec3 position, vec3 euler, vec3 s, const string &name = "GameObject");

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

        virtual void Tick(float deltaTime);
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
