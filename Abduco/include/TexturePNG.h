/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TexturePNG.h
 * Author: sebas
 *
 * Created on 14 novembre 2017, 22:00
 */

#ifndef TEXTUREPNG_H
#define TEXTUREPNG_H

#include<iostream>
#include"Texture.h"


class TexturePNG : public Texture{
public:
    TexturePNG(const char* cheminTexture);
    virtual ~TexturePNG();
private:

};

#endif /* TEXTUREPNG_H */

