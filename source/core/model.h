//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include <game.h>
#include <shader.h>
#include <debug.h>

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

namespace smallsquare{

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

        MatIndex(Material * mat, unsigned int index ){
            this->mat = mat;
            this->index = index;
        }
    };

    class Mesh;
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
        Mesh  * ProcessMesh(aiMesh *mesh, const aiScene *scene);

    public:
        Model(vec3 position, vec3 euler, vec3 s, string path, Shader * shader, const string & name = "Model") : DrawableObject(position, euler, s, name) {
            this->shader = shader;
            LoadModel(path);
        }
        void Tick(float deltaTime) override;
        void Draw(Viewport * viewport) override;
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
}