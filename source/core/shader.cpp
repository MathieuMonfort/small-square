//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include <shader.h>


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

void smallsquare::Shader::use()const{
    glUseProgram(program);
}

void smallsquare::Shader::setBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void smallsquare::Shader::setInt(const string &name, int value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void smallsquare::Shader::setFloat(const string &name, float value) const{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void smallsquare::Shader::setVec2(const string &name, const vec2 &value) const{
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::setVec3(const string &name, const vec3 &value) const{
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::setVec4(const string &name, const vec4 &value) const{
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void smallsquare::Shader::setMat2(const string &name, const mat2 &value) const{
    glUniformMatrix2fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void smallsquare::Shader::setMat3(const string &name, const mat3 &value) const{
    glUniformMatrix3fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void smallsquare::Shader::setMat4(const string &name, const mat4 &value) const{
    glUniformMatrix4fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}


#pragma region Mat&Light


void smallsquare::Shader::setMaterial(const string &name, Material  *value) const{
    setInt(name + ".diffuse",0);
    setInt(name + ".specular",1);
    setInt(name + ".emission",2);

    setFloat(name + ".shininess",value->shininess);
    if(value->diffuse){ value->diffuse->BindToProcessor(GL_TEXTURE0);}
    if(value->specular){ value->specular->BindToProcessor(GL_TEXTURE1);}
    
    if(value->emission){ 
        value->emission->BindToProcessor(GL_TEXTURE2); 
        setBool(name + ".emissive", true);
    }
    else{
        setBool(name + ".emissive", false);
    }
    
}

void smallsquare::Shader::setDirLightArray(const string &name, vector<DirectionLight *>value) const{

    for(int i =0; i< value.size() ; i++){
        setVec3(name + "[" + to_string(i) + "].direction", value[i]->GetGlobalFront() );
        setVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", value[i]->specular );
    }
    setInt("n_dirLight", value.size());

}


void smallsquare::Shader::setPointLightArray(const string &name,vector<PointLight *>value) const{
    

    for(int i =0; i< value.size() ; i++){
        setVec3(name + "[" + to_string(i) + "].position", value[i]->position );
        setVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", value[i]->specular );
        setFloat(name + "[" + to_string(i) + "].constant", value[i]->constant );
        setFloat(name + "[" + to_string(i) + "].linear", value[i]->linear );
        setFloat(name + "[" + to_string(i) + "].quadratic", value[i]->quadratic );

    }

    setInt("n_pointLight",value.size());

}

void smallsquare::Shader::setSpotLightArray(const string &name, vector<SpotLight *>value) const{

    for(int i =0; i< value.size() ; i++){

        string id = name + "[" + to_string(i) + "].position";

        setVec3(name + "[" + to_string(i) + "].position", value[i]->position );
        setVec3(name + "[" + to_string(i) + "].direction", value[i]->GetGlobalFront() );
        setVec3(name + "[" + to_string(i) + "].ambient", value[i]->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", value[i]->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", value[i]->specular );
        setFloat(name + "[" + to_string(i) + "].constant", value[i]->constant );
        setFloat(name + "[" + to_string(i) + "].linear", value[i]->linear );
        setFloat(name + "[" + to_string(i) + "].quadratic", value[i]->quadratic );
        setFloat(name + "[" + to_string(i) + "].cutOff", value[i]->cutOff );
        setFloat(name + "[" + to_string(i) + "].outerCutOff", value[i]->outerCutOff );
    }
    setInt("n_spotLight",value.size());

}

#pragma endregion