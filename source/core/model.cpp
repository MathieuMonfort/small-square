//
// Created by Mathieu Monfort
// Date : 4/2/21.
//

#include <model.h>


void smallsquare::Model::LoadModel(string &path){
    Assimp::Importer importer; 
    const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate |aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    
    directory = path.substr(0,path.find_last_of('/'));

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

        vertex.Position.x = mesh->mVertices[i].x;
        vertex.Position.y = mesh->mVertices[i].y;
        vertex.Position.z = mesh->mVertices[i].z;

        vertex.Normal.x = mesh->mNormals[i].x;
        vertex.Normal.y = mesh->mNormals[i].y;
        vertex.Normal.z = mesh->mNormals[i].z;
        
        if(mesh->mTextureCoords[0]){
            vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
        }
        else{
            vertex.TexCoords = vec2(0.0f);
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
    for(auto & _loadedMaterial : _loadedMaterials){
        if(_loadedMaterial.index  == mesh->mMaterialIndex) {
            isMatLoaded = true; 
            mat = _loadedMaterial.mat;

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
            diffuse = new Texture(directory + "/" +diffPath.C_Str());
        }

        if(material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
            aiString specPath;
            material->GetTexture(aiTextureType_SPECULAR, 0 , &specPath);
            specular = new Texture(directory + "/" +specPath.C_Str());
        }

        if(material->GetTextureCount(aiTextureType_SPECULAR) > 0 ) {
            aiString emPath;
            material->GetTexture(aiTextureType_EMISSIVE, 0 , &emPath);
            emissive = new Texture(directory + "/" + emPath.C_Str());
        }
        mat = new Material(diffuse, specular, emissive, 10.0f);

        _loadedMaterials.emplace_back(mat, mesh->mMaterialIndex);
    }
    
    return new Mesh(vertices, indices, mat);
}

void smallsquare::Model::Tick(float deltaTime){
}




void smallsquare::Model::Draw(Viewport * viewport){

    auto lightsources = game->FindObjectsOfType<Light*>();

    shader->use();
    DEBUG::Log( GetGlobalMatrix(),"ModelMatrix");
    shader->setMat4("model",GetGlobalMatrix());
    shader->setMat4("view", viewport->GetViewMatrix());
    shader->setMat4("projection", viewport->GetProjectionMatrix());
    shader->setVec3("viewPos", viewport->_cam->position );
    

    //Adding Light Sources Info To used Shader;
    vector<DirectionLight *> dls;
    vector<PointLight *> pls;
    vector<SpotLight *> sls;
    for(auto & i : lightsources ){
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
    shader->setDirLightArray("dirlights", dls);
    shader->setPointLightArray("pointlights", pls);
    shader->setSpotLightArray("spotlights",sls);

    for(auto & mesh : meshes){
        mesh->Draw(shader);
    }

}

smallsquare::Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material * material){
    VAO =0;
    VBO =0;
    EBO =0;

    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->material = material;

    SetupMesh();
}


void smallsquare::Mesh::SetupMesh(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}

void smallsquare::Mesh::Draw(Shader * shader) const {
    shader->use();
    shader->setMaterial("material", material);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}