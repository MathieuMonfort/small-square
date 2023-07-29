//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "gameobject.h"
#include "shader.h"

using namespace std;

namespace smallsquare{

    class Shader;
    class Material;

    /** \brief A fancy name for a point
     *
     * A Vertex is base block of a Mesh. It's basically a point in 3D space with bunch of useful information.
     */
    struct Vertex {

        /**
         * The vertex position in 3D space.
         */
        vec3 position;

        /**
         * A normal vector calculated from the Mesh's surface at the vertex.
         */
        vec3 normal;

        /**
         * The coordinates ot the texture bound to the vertex when the mesh has been UV mapped.
         */
        vec2 texCoords;

        /**
         * An arbitrary tangent of the Mesh at the vertex.
         */
        vec3 tangent;

        /**
         * A secondary tangent of the Mesh at the vertex, orthogonal to the first tangent vector.
         */
        vec3 bitangent;
    };


    /**
     * A class binding a material to a material index extrated from an Assimp Model.
     */
    struct MatIndex{
    public:

        /**
         * The MatIndex Material.
         */
        Material * mat;

        /**
         * The index present inside the Assimp Model.
         */
        unsigned int index;

        /**
         * Constructor for the MatIndex class
         * @param mat The MatIndex Material.
         * @param index The index present inside the Assimp Model.
         */
        MatIndex(Material * mat, unsigned int index );
    };


    /** \brief A part of a model.
     *
     * A Mesh is a set of vertex bound into triangles with material information. Multiple Mesh make up a Model.
     */
    class Mesh{
    private:

        /**
         * The Mesh's Vertex Array Object index. a VAO is a C abstraction of a array of points without any spatial information. Just a set of index.
         */
        unsigned int _vao;

        /**
         * The Mesh's Vertex Buffer Object index. a VBO is a C array containing spatial,normal,texcoord,tangent and bitangent information.
         */
        unsigned int _vbo;

        /**
         * The Mesh's Element Buffer Object index. an EBO is C array of links between vertices. The EBO essentially contains very abstract triangles.
         */
        unsigned int _ebo;

    public:
        /**
         * A pointer to the material assigned to the Mesh.
         */
        Material * material;

        /**
         * A vector containing all the Mesh's vertices.
         */
        vector<Vertex> vertices;

        /**
         * A vector containing the sets of indices forming triangles to be given to the EBO.
         */
        vector<unsigned int> indices;

    private:

        /**
         * Generate the VAO VBO and EBO and populate them with vertex information so the mesh can be drawn by OpenGL.
         */
        void SetupMesh();

    public:

        /**
         *  Constructor for the Mesh Class.
         * @param vertices A set of vertices.
         * @param indices Sets of indices forming triangles to be given to the EBO.
         * @param mat A pointer to a material.
         */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material * mat);

        /**
         * Signal OpenGL to render the mesh using a given Shader.
         * @param shader A pointer to an instantiated Shader.
         */
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

        //TODO Make a constructor for the model class so they can share loaded mesh.

        Model(vec3 position, vec3 euler, vec3 s, string path, Shader * shader, const string & name = "Model") ;
        void Tick(float deltaTime) override;
        void Draw(mat4 projection, Camera * cam,float ratio ) override;
    };


}