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
#include<glm//gtx/string_cast.hpp>
#include<iostream>
#include"Shader.h"
#include"Texture.h"
#include"TextureJPEG.h"
#include"TexturePNG.h"
#include"Camera.h"

#include<iostream>
#include"Shader.h"

static const float sensibiliteSouris = 0.05f;
static Camera* camera = new Camera();

class Application {
public:
    Application();
    virtual ~Application();
	static void errorCallback(int error, const char* err_str);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void GLClearError();
    static void GLCheckError();
    void run();
    void processInput(GLFWwindow* fenetre);
    void render();

private:
    const int HAUTEUR = 650;
    const int LARGEUR = 1155;
    GLFWwindow* _fenetre;
    GLuint VBO, VAO, EBO, lightVAO;
	Shader* shaderProgram;
	Shader* shaderLumiere;
    TextureJPEG* texture1;
    TexturePNG* texture2;
	float deltaTime;
	float lastFrame;
	float currentFrame;
	float vitesseCamera;
};

#endif /* Application_H */

