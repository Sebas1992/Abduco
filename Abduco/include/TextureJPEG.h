/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureJPEG.h
 * Author: sebas
 *
 * Created on 14 novembre 2017, 21:51
 */

#ifndef TEXTUREJPEG_H
#define TEXTUREJPEG_H

#include"Texture.h"

class TextureJPEG : public Texture {
public:
    TextureJPEG(const char* cheminTexture);
    virtual ~TextureJPEG();
private:

};

#endif /* TEXTUREJPEG_H */

