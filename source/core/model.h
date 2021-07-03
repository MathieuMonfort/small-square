//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <gameobject.h>
#include <shader.h>

using namespace std;

namespace smallsquare{

    class Shader;
    class Material;
    struct Vertex {
        vec3 position;
        vec3 normal;
        vec2 texCoords;
        vec3 tangent;
        vec3 bitangent;
    };



    struct MatIndex{
    public: 
        Material * mat;
        unsigned int index;

        MatIndex(Material * mat, unsigned int index );
    };



    class Mesh{
    private:
        unsigned int _vao, _vbo, _ebo;

    public:
        Material * material;
        vector<Vertex> vertices;
        vector<unsigned int> indices;

    private:
        void SetupMesh();

    public:
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material * mat);
        void Draw(Shader * shader) const ;

    };



    class Model : public DrawableObject{
    private:
        string _directory;
        vector<MatIndex> _loadedMaterials;
    public:
        vector<Mesh *> meshes;
        Shader * shader;


    private: 
        void LoadModel(string &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh * ProcessMesh(aiMesh *mesh, const aiScene *scene);

    public:

        /**
         * Constructor for the Model class.
         * @param position
         * @param euler
         * @param s
         * @param path
         * @param shader
         * @param name
         */
        Model(vec3 position, vec3 euler, vec3 s, string path, Shader * shader, const string & name = "Model") ;
        void Tick(float deltaTime) override;
        void Draw(mat4 projection, Camera * cam,float ratio ) override;
    };


}