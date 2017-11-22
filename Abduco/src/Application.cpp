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
}

void Application::errorCallback(int error, const char* err_str)
{
	std::cerr << "GLFW Error " << error << ": " << err_str << std::endl;
}

void Application::run()
{   

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
    
    //VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
	// VAOlightning
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	shaderProgram = new Shader("./Shaders/vertex.vs", "./Shaders/fragment.fs");
	shaderLumiere = new Shader("./Shaders/vertexLumiere.vs", "./Shaders/fragmentLumiere.fs");

	// Position de la lumiere
	posLumiere = glm::vec3(1.2f, 1.0f, -2.0f);

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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	// Couleur 
	glm::vec3 lumiere = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 objet = glm::vec3(1.0f, 0.5f, 0.31f);

	//Cube
	shaderProgram->utiliserProgramme();
	glBindVertexArray(VAO);
    
	glm::mat4 modele;
	glm::mat4 projection;
	projection = glm::perspective(camera->get_fov(), (float)LARGEUR / (float)HAUTEUR, 0.1f, 100.0f);

	unsigned int modeleLocation = glGetUniformLocation(shaderProgram->get_program(), "modele");
	unsigned int vueLocation = glGetUniformLocation(shaderProgram->get_program(), "vue");
	unsigned int projectionLocation = glGetUniformLocation(shaderProgram->get_program(), "projection");
	unsigned int couleurObjet = glGetUniformLocation(shaderProgram->get_program(), "couleurCube");
	unsigned int couleurLumiere = glGetUniformLocation(shaderProgram->get_program(), "couleurLumiere");
	unsigned int lumiereLocation = glGetUniformLocation(shaderProgram->get_program(), "posLumiere");

	glUniformMatrix4fv(vueLocation, 1, GL_FALSE, glm::value_ptr(camera->get_vue()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modeleLocation, 1, GL_FALSE, glm::value_ptr(modele));
	glUniform3fv(lumiereLocation, 1, glm::value_ptr(posLumiere));
	glUniform3fv(couleurLumiere, 1, glm::value_ptr(lumiere));
	glUniform3fv(couleurObjet, 1, glm::value_ptr(objet));


	GLClearError();
	glDrawArrays(GL_TRIANGLES, 0, 36);
    GLCheckError();

	// Lumiere
	shaderLumiere->utiliserProgramme();
	glBindVertexArray(lightVAO);

	glm::mat4 modeleLumiere;
	modeleLumiere = glm::translate(modeleLumiere, posLumiere);

	modeleLocation = glGetUniformLocation(shaderLumiere->get_program(), "modele");
	vueLocation = glGetUniformLocation(shaderLumiere->get_program(), "vue");
	projectionLocation = glGetUniformLocation(shaderLumiere->get_program(), "projection");

	projection = glm::perspective(camera->get_fov(), (float)LARGEUR / (float)HAUTEUR, 0.1f, 100.0f);

	glUniformMatrix4fv(vueLocation, 1, GL_FALSE, glm::value_ptr(camera->get_vue()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modeleLocation, 1, GL_FALSE, glm::value_ptr(modeleLumiere));

	GLClearError();
	glDrawArrays(GL_TRIANGLES, 0, 36);
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
		camera-> traitementClavier(GAUCHE, deltaTime);
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