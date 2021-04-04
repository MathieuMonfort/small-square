//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include <game.h>
#include <shader.h>

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

namespace smallsquare{

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
    public:
        vector<Mesh *> meshes;
        Shader * shader;
    
        Model(vec3 position, vec3 euler, vec3 uscale,string path, Shader * shader) : DrawableObject(position,euler,uscale) {
            this->shader = shader;
            LoadModel(path);
        }

        void Tick(float deltaTime) override;
        void Draw(Viewport * viewport) override;
    private: 
        string directory;
        vector<MatIndex> _loadedMaterials;
       
       
        void LoadModel(string &path);
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh  * ProcessMesh(aiMesh *mesh, const aiScene *scene);

    };
    
    struct Vertex {
        vec3 Position;
        vec3 Normal;
        vec2 TexCoords; 
        vec3 Tangent;
        vec3 Bitangent;
    };

    class Mesh{
    public:
        Material * material; 
        vector<Vertex> vertices;
        vector<unsigned int> indices; 

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material * mat); 
        void Draw(Shader * shader) const ;

    private: 
        unsigned int VAO, VBO, EBO;

        void SetupMesh();


    };
}