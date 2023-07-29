//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include "model.h"


#pragma region MatIndex
smallsquare::MatIndex::MatIndex(smallsquare::Material *mat, unsigned int index) {
    this->mat = mat;
    this->index = index;
}
#pragma endregion

#pragma region Mesh

smallsquare::Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material * material){
    _vao =0;
    _vbo =0;
    _ebo =0;

    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->material = material;

    SetupMesh();
}

void smallsquare::Mesh::Draw(Shader * shader) const {

    //TODO: Error Management: shader not instantiated;
    shader->Use();
    shader->SetMaterial("material", material);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void smallsquare::Mesh::SetupMesh(){
    glGenVertexArrays(1,&_vao);
    glGenBuffers(1,&_vbo);
    glGenBuffers(1,&_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}

#pragma endregion

#pragma region Model

smallsquare::Model::Model(vec3 position, vec3 euler, vec3 s, string path, smallsquare::Shader *shader,
                          const string &name) : DrawableObject(position, euler, s, name) {
    this->shader = shader;
    LoadModel(path);
}

void smallsquare::Model::Tick(float deltaTime){ }

void smallsquare::Model::Draw(mat4 projection, Camera * cam, float ratio){

    auto lightSources = FindObjectsOfType<Light*>();

    shader->Use();

    shader->SetMat4("model", GetLocalMatrix());
    shader->SetMat4("view", cam->GetView());
    shader->SetMat4("projection", projection);
    shader->SetVec3("viewPos", cam->position);


    //Adding Light Sources Info To used Shader;
    vector<DirectionLight *> dls;
    vector<PointLight *> pls;
    vector<SpotLight *> sls;
    for(auto & i : lightSources ){
        Light * l = i ;
        if(dynamic_cast<DirectionLight *>(l)){
            dls.push_back((DirectionLight *)l);
        }
        if(dynamic_cast<PointLight *>(l)){
            pls.push_back((PointLight *) l);
        }
        if(dynamic_cast<SpotLight *>(l)){
            sls.push_back((SpotLight *) l);
        }
    }
    shader->SetDirLightArray("dirlights", dls);
    shader->SetPointLightArray("pointlights", pls);
    shader->SetSpotLightArray("spotlights", sls);

    for(auto & mesh : meshes){
        mesh->Draw(shader);
    }

}

void smallsquare::Model::LoadModel(string &path){
    Assimp::Importer importer;
    const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate |aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }

    _directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode,scene);
}

void smallsquare::Model::ProcessNode(aiNode *node, const aiScene *scene){
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i], scene);
    }
}

smallsquare::Mesh * smallsquare::Model::ProcessMesh(aiMesh * mesh, const aiScene *scene){
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Material * mat;

    for(int i =0; i< mesh->mNumVertices; i++){
        Vertex vertex{};

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        if(mesh->mTextureCoords[0]){
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else{
            vertex.texCoords = vec2(0.0f);
        }

        vertices.push_back(vertex);
    }


    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    bool isMatLoaded = false;
    for(auto & loadedMaterial : _loadedMaterials){
        if(loadedMaterial.index == mesh->mMaterialIndex) {
            isMatLoaded = true;
            mat = loadedMaterial.mat;

        }
    }

    if(mesh->mMaterialIndex >=0 && !isMatLoaded ){
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        Texture * diffuse = nullptr;
        Texture * specular = nullptr;
        Texture * emissive = nullptr;
        if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString diffPath;
            material->GetTexture(aiTextureType_DIFFUSE, 0 , &diffPath);
            diffuse = new Texture(_directory + "/" + diffPath.C_Str());
        }

        if(material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
            aiString specPath;
            material->GetTexture(aiTextureType_SPECULAR, 0 , &specPath);
            specular = new Texture(_directory + "/" + specPath.C_Str());
        }

        if(material->GetTextureCount(aiTextureType_SPECULAR) > 0 ) {
            aiString emPath;
            material->GetTexture(aiTextureType_EMISSIVE, 0 , &emPath);
            emissive = new Texture(_directory + "/" + emPath.C_Str());
        }
        mat = new Material(diffuse, specular, emissive, 10.0f);

        _loadedMaterials.emplace_back(mat, mesh->mMaterialIndex);
    }

    return new Mesh(vertices, indices, mat);
}


#pragma endregion




