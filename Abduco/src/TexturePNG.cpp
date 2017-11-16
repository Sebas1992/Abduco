/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TexturePNG.cpp
 * Author: sebas
 * 
 * Created on 14 novembre 2017, 22:00
 */

#include "TexturePNG.h"

TexturePNG::TexturePNG(const char* cheminTexture) : Texture(cheminTexture)
{   
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    stbi_set_flip_vertically_on_load(true);
    
    unsigned char* data = stbi_load(cheminTexture, &largeur, &hauteur, &nbChannels, 0);
    if(data != NULL)
    {        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largeur, hauteur, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Impossible de charger la texture en memoire" << std::endl;
    }
        
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TexturePNG::~TexturePNG() 
{
    
}

