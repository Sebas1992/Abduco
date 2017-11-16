/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Texture.h
 * Author: sebas
 *
 * Created on 14 novembre 2017, 14:12
 */

#ifndef TEXTURE_H
#define TEXTURE_H


#include<stb_image.h>

#include<glad/glad.h>

class Texture {
public:
    Texture(const char* cheminTexture);
    virtual ~Texture();
    unsigned int get_texture(){return texture;}
protected:
    int largeur, hauteur, nbChannels;
    unsigned int texture;
};

#endif /* TEXTURE_H */

