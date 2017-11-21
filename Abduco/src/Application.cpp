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

	glfwSetErrorCallback(errorCallback);
    
    //Set-up de la fenetre
    _fenetre = glfwCreateWindow(LARGEUR, HAUTEUR, "LearnOpenGL", NULL, NULL);
    if(_fenetre == NULL)
    {
        std::cerr << "Failed to initialize window" << std::endl;
        glfwTerminate();
    }
    
    glfwMakeContextCurrent(_fenetre);
    
    //Set-up de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }    
    
	glfwSetInputMode(_fenetre, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(_fenetre, mouseCallback);
	glfwSetScrollCallback(_fenetre, scrollCallback);
    glViewport(0, 0, LARGEUR, HAUTEUR);
}

Application::~Application() 
{
	delete camera;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    delete shaderProgram;
    delete texture1;
    delete texture2;
}

void Application::errorCallback(int error, const char* err_str)
{
	std::cerr << "GLFW Error " << error << ": " << err_str << std::endl;
}

void Application::run()
{   
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
    
	/*
    const unsigned int indices[] = {
        0, 1, 2, 
        0, 3, 2
    };
     */
    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
   
	/*
    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    shaderProgram = new Shader("./Shaders/vertex.vs", "./Shaders/fragment.fs");
    
    //Texture
    texture1 = new TextureJPEG("./Image/container.jpg");
    texture2 = new TexturePNG("./Image/awesomeface.png");
    
    //Dit a OpenGL quel sampler dans le shader correspond a quel texture
    shaderProgram->utiliserProgramme();
    glUniform1i(glGetUniformLocation(shaderProgram->get_program(), "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram->get_program(), "texture2"), 1);

	glEnable(GL_DEPTH_TEST);

	//Initialisation de la fenetre
	camera = new Camera();

    while(!glfwWindowShouldClose(_fenetre))
    {
        processInput(_fenetre);
		// utilise pour la normalisation de la vitesse de la camera
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

        this->render();
        
        glfwSwapBuffers(_fenetre);
        glfwPollEvents();
    }
    
    glBindVertexArray(0);
}

void Application::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	shaderProgram->utiliserProgramme();
	glBindVertexArray(VAO);
    
	glm::mat4 modele;
	glm::mat4 projection;
	modele = glm::rotate(modele, glm::radians((float)glfwGetTime() * 50), glm::vec3(0.5f, 1.0f, 0.0f));
	projection = glm::perspective(camera->get_fov(), (float)LARGEUR / (float)HAUTEUR, 0.1f, 100.0f);

	float rayon = 10.0f;
	float camX = sin(glfwGetTime()) * rayon;
	float camZ = cos(glfwGetTime()) * rayon;

	unsigned int modeleLocation = glGetUniformLocation(shaderProgram->get_program(), "modele");
	unsigned int vueLocation = glGetUniformLocation(shaderProgram->get_program(), "vue");
	unsigned int projectionLocation = glGetUniformLocation(shaderProgram->get_program(), "projection");

	//glUniformMatrix4fv(modeleLocation, 1, GL_FALSE, glm::value_ptr(modele));
	glUniformMatrix4fv(vueLocation, 1, GL_FALSE, glm::value_ptr(camera->get_vue()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    // Determine quelles texture ut lier et les lie
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1->get_texture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2->get_texture());
	
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 modele;
		float angle = 20.0f * i;
		modele = glm::translate(modele, cubePositions[i]);
		modele = glm::rotate(modele, glm::radians(angle) * (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.0f));
		glUniformMatrix4fv(modeleLocation, 1, GL_FALSE, glm::value_ptr(modele));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	GLClearError();

    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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

void Application::processInput(GLFWwindow* fenetre)
{
	if (glfwGetKey(fenetre, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(fenetre, true);
	}

	if (glfwGetKey(this->_fenetre, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->traitementClavier(AVANT, deltaTime);
	}
	
	if (glfwGetKey(this->_fenetre, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->traitementClavier(ARRIERE, deltaTime);
	}
	if (glfwGetKey(this->_fenetre, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->traitementClavier(GAUCHE, deltaTime);
	}
	if (glfwGetKey(this->_fenetre, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->traitementClavier(DROITE, deltaTime);
	}
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	camera->traitementSouris(xpos, ypos, sensibiliteSouris);
}

void Application::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera->zoomSouris(yOffset);
}