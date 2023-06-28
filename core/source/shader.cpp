//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include "shader.h"

smallsquare::Material::Material(smallsquare::Texture *diffuse, smallsquare::Texture *specular,
                                smallsquare::Texture *emission, float shininess) {
    this->diffuse = diffuse;
    this->specular = specular;
    this->emission = emission;
    this->shininess = shininess;
}

smallsquare::Shader::Shader(const char * vertexPath, const char* fragmentPath){
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch(ifstream::failure& e){
        cout<< "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];


    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::
        endl;
    }
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    // shader Program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    // print linking errors if any

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // delete the shaders as they’re linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void smallsquare::Shader::Use()const{
    glUseProgram(program);
}

void smallsquare::Shader::SetBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void smallsquare::Shader::SetInt(const string &name, int value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void smallsquare::Shader::SetFloat(const string &name, float value) const{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void smallsquare::Shader::SetVec2(const string &name, const vec2 &value) const{
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::SetVec3(const string &name, const vec3 &value) const{
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::SetVec4(const string &name, const vec4 &value) const{
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::SetMat2(const string &name, const mat2 &value) const{
    glUniformMatrix2fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void smallsquare::Shader::SetMat3(const string &name, const mat3 &value) const{
    glUniformMatrix3fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void smallsquare::Shader::SetMat4(const string &name, const mat4 &value) const{
    glUniformMatrix4fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}


#pragma region Mat&Light

void smallsquare::Shader::SetMaterial(const string &name, Material  *value) const{
    SetInt(name + ".diffuse", 0);
    SetInt(name + ".specular", 1);
    SetInt(name + ".emission", 2);

    SetFloat(name + ".shininess", value->shininess);
    if(value->diffuse){ value->diffuse->BindToProcessor(GL_TEXTURE0);}
    if(value->specular){ value->specular->BindToProcessor(GL_TEXTURE1);}
    
    if(value->emission){
        value->emission->BindToProcessor(GL_TEXTURE2);
        SetBool(name + ".emissive", true);
    }
    else{
        SetBool(name + ".emissive", false);
    }
    
}

void smallsquare::Shader::SetDirLightArray(const string &name, vector<DirectionLight *>value) const{

    for(int i =0; i< value.size() ; i++){
        SetVec3(name + "[" + to_string(i) + "].direction", value[i]->GetGlobalFront());
        SetVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient);
        SetVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse);
        SetVec3(name + "[" + to_string(i) + "].specular", value[i]->specular);
    }
    SetInt("n_dirLight", value.size());

}


void smallsquare::Shader::SetPointLightArray(const string &name, vector<PointLight *>value) const{
    

    for(int i =0; i< value.size() ; i++){
        SetVec3(name + "[" + to_string(i) + "]._position", value[i]->GetGlobalPosition());
        SetVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient);
        SetVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse);
        SetVec3(name + "[" + to_string(i) + "].specular", value[i]->specular);
        SetFloat(name + "[" + to_string(i) + "].constant", value[i]->constant);
        SetFloat(name + "[" + to_string(i) + "].linear", value[i]->linear);
        SetFloat(name + "[" + to_string(i) + "].quadratic", value[i]->quadratic);

    }

    SetInt("n_pointLight", value.size());

}

void smallsquare::Shader::SetSpotLightArray(const string &name, vector<SpotLight *>value) const{

    for(int i =0; i< value.size() ; i++){

        string id = name + "[" + to_string(i) + "]._position";

        SetVec3(name + "[" + to_string(i) + "]._position", value[i]->GetGlobalPosition());
        SetVec3(name + "[" + to_string(i) + "].direction", value[i]->GetGlobalFront());
        SetVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient);
        SetVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse);
        SetVec3(name + "[" + to_string(i) + "].specular", value[i]->specular);
        SetFloat(name + "[" + to_string(i) + "].constant", value[i]->constant);
        SetFloat(name + "[" + to_string(i) + "].linear", value[i]->linear);
        SetFloat(name + "[" + to_string(i) + "].quadratic", value[i]->quadratic);
        SetFloat(name + "[" + to_string(i) + "].cutOff", value[i]->cutOff);
        SetFloat(name + "[" + to_string(i) + "].outerCutOff", value[i]->outerCutOff);
    }
    SetInt("n_spotLight", value.size());

}

#pragma endregion


