#include <shader.h>
using namespace smallsquare;


Shader::Shader(const char * vertexPath, const char* fragmentPath){
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
        cout<< "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];


    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::
        endl;
    }
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    };
    
    // shader Program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    // print linking errors if any

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // delete the shaders as they’re linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use(){
    glUseProgram(program);
}

void Shader::setBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec2(const string &name, const vec2 &value) const{ 
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const string &name, const vec3 &value) const{ 
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void Shader::setVec4(const string &name, const vec4 &value) const{ 
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]); 
}

void Shader::setMat2(const string &name, const mat2 &value) const{
    glUniformMatrix2fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void Shader::setMat3(const string &name, const mat3 &value) const{
    glUniformMatrix3fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}

void Shader::setMat4(const string &name, const mat4 &value) const{
    glUniformMatrix4fv(  glGetUniformLocation(program,name.c_str() ) , 1 ,GL_FALSE, &value[0][0] );
}


#pragma region Mat&Light


void Shader::setMaterial(const string &name, Material  *value) const{
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

void Shader::setDirLightArray(const string &name, list<DirectionLight *>value) const{

    int i =0;
    for(list<DirectionLight * >::iterator it = value.begin() ; it != value.end(); it++ ){
        setVec3(name + "[" + to_string(i) + "].direction", (*it)->GetGlobalFront() );
        setVec3(name + "[" + to_string(i) + "].ambient", (*it)->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", (*it)->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", (*it)->specular );
        i++;
    }
    setInt("n_dirLight", value.size());

}


void Shader::setPointLightArray(const string &name,list<PointLight *>value) const{
    
    int i =0;
    for(list<PointLight * >::iterator it = value.begin() ; it != value.end(); it++ ){
        setVec3(name + "[" + to_string(i) + "].position", (*it)->position );
        setVec3(name + "[" + to_string(i) + "].ambient", (*it)->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", (*it)->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", (*it)->specular );
        setFloat(name + "[" + to_string(i) + "].constan", (*it)->constant );
        setFloat(name + "[" + to_string(i) + "].linear", (*it)->linear );
        setFloat(name + "[" + to_string(i) + "].quadratic", (*it)->quadratic );
        i++;
    }

    setInt("n_pointLight",value.size());

}

void Shader::setSpotLightArray(const string &name, list<SpotLight *>value) const{

    int i =0;
    for(list<SpotLight * >::iterator it = value.begin() ; it != value.end(); it++ ){

        string id = name + "[" + to_string(i) + "].position";

        setVec3(name + "[" + to_string(i) + "].position", (*it)->position );
        setVec3(name + "[" + to_string(i) + "].direction", (*it)->GetGlobalFront() );
        setVec3(name + "[" + to_string(i) + "].ambient", (*it)->ambient );
        setVec3(name + "[" + to_string(i) + "].diffuse", (*it)->diffuse );
        setVec3(name + "[" + to_string(i) + "].specular", (*it)->specular );
        setFloat(name + "[" + to_string(i) + "].constant", (*it)->constant );
        setFloat(name + "[" + to_string(i) + "].linear", (*it)->linear );
        setFloat(name + "[" + to_string(i) + "].quadratic", (*it)->quadratic );
        setFloat(name + "[" + to_string(i) + "].cutOff", (*it)->cutOff );
        setFloat(name + "[" + to_string(i) + "].outerCutOff", (*it)->outerCutOff );
        i++;
    }
    setInt("n_spotLight",value.size());

}

#pragma endregion