/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.h
 * Author: sebas
 *
 * Created on 13 novembre 2017, 17:57
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include<glad/glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>
#include"Shader.h"
#include"Texture.h"
#include"TextureJPEG.h"
#include"TexturePNG.h"

#include<iostream>
#include"Shader.h"

class Application {
public:
    Application();
    virtual ~Application();
    static void framebuffer_size_callback(GLFWwindow*, int hauteur, int largeur);
    static void GLClearError();
    static void GLCheckError();
    void run();
    void processInput(GLFWwindow* fenetre);
    void render();


private:
    const int HAUTEUR = 600;
    const int LARGEUR = 800;
    GLFWwindow* _fenetre;
    GLuint VBO, VAO, EBO;
    Shader* shaderProgram;
    TextureJPEG* texture1;
    TexturePNG* texture2;
};

#endif /* Application_H */

