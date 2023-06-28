//
// Created by Mathieu Monfort
// Date : 4/2/21.
//
#include "texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif



smallsquare::Texture::Texture(const string& path){

    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format;
    int width,height,nrChannels;
    unsigned char *data = stbi_load(path.c_str(),&width,&height,&nrChannels,0);
    if(data){
        if(nrChannels ==1){
            format = GL_RED;
        } 
        else if(nrChannels ==3) {
            format = GL_RGB;
        } 
        else if(nrChannels ==4){
            format = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        cout<<"Failed to load texture with path :" << path << endl;
    }
    stbi_image_free(data);
}

void smallsquare::Texture::BindToProcessor(GLenum proc) const{
    glActiveTexture(proc);
    glBindTexture(GL_TEXTURE_2D, id);
}