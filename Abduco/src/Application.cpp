/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Display.cpp
 * Author: sebas
 * 
 * Created on 13 novembre 2017, 17:57
 */

#include "Application.h"

Application::Application() 
{
    
    //Set-up de GLFW
    if(glfwInit() == GL_FALSE)
    {
        std::cerr << "Error while initializing GLFW" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    //Set-up de la fenetre
    _fenetre = glfwCreateWindow(LARGEUR, HAUTEUR, "LearnOpenGL", NULL, NULL);
    if(_fenetre == NULL)
    {
        std::cerr << "Failed to initialize window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(_fenetre);
    
    glfwSetFramebufferSizeCallback(_fenetre, framebuffer_size_callback);
    
    //Set-up de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }    
    
    glViewport(0, 0, LARGEUR, HAUTEUR);
}

Application::~Application() 
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    delete shaderProgram;
    delete texture1;
    delete texture2;
}

//Methode pour redimensionner le viewport quand l'utilisateur redimensionne la fenetre
void Application::framebuffer_size_callback(GLFWwindow* fenetre, int hauteur, int largeur)
{
    glViewport(0, 0, largeur, hauteur);
}

void Application::run()
{   
    const float vertices[] = { // Positions          // Couleurs          // TexCoord
                              -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
                               0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
                               0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
                              -0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 1.0f};
    
    const unsigned int indices[] = {
        0, 1, 2, 
        0, 3, 2
    };
     
    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
   
    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    shaderProgram = new Shader("./Shaders/vertex.vs", "./Shaders/fragment.fs");
    
    //Texture
    texture1 = new TextureJPEG("./Image/container.jpg");
    texture2 = new TexturePNG("./Image/awesomeface.png");
    
    //Dit a OpenGL quel sampler dans le shader correspond a quel texture
    shaderProgram->utiliserProgramme();
    glUniform1i(glGetUniformLocation(shaderProgram->get_program(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram->get_program(), "texture2"), 1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while(!glfwWindowShouldClose(_fenetre))
    {
        processInput(_fenetre);
        
        this->render();
        
        glfwSwapBuffers(_fenetre);
        glfwPollEvents();
    }
    
    glBindVertexArray(0);
}

void Application::processInput(GLFWwindow* fenetre)
{
    if(glfwGetKey(fenetre, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(fenetre, true);
    }
}

void Application::render()
{
    const GLfloat color[] = {0.2f, 0.3f, 0.3f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    
    // Determine quelles texture ut lier et les lie
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->get_texture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2->get_texture());
    
    shaderProgram->utiliserProgramme();
    glBindVertexArray(VAO);
    
    GLClearError();
    //glDrawArrays(GL_TRIANGLES, 0, 3);

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.0f, 0.0f, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));

	unsigned int matLocation = glGetUniformLocation(shaderProgram->get_program(), "transformation");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glm::mat4 trans1;
	trans1 = glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
	//trans = glm::rotate(trans, glm::radians((float)glfwGetTime() * 100), glm::vec3(0.0f, 0.0f, 1.0f));
	trans1 = glm::scale(trans1, glm::vec3(sin(glfwGetTime()), 0.5f, 1.0f));
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, glm::value_ptr(trans1));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    GLCheckError();
}

void Application::GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

void Application::GLCheckError()
{
    while(GLenum error = glGetError())
    {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}