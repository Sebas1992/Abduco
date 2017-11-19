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
	static void errorCallback(int error, const char* err_str);
    static void GLClearError();
    static void GLCheckError();
    void run();
    void processInput(GLFWwindow* fenetre);
    void render();


private:
    const int HAUTEUR = 650;
    const int LARGEUR = 1155;
    GLFWwindow* _fenetre;
    GLuint VBO, VAO, EBO;
    Shader* shaderProgram;
    TextureJPEG* texture1;
    TexturePNG* texture2;

	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
};

#endif /* Application_H */

