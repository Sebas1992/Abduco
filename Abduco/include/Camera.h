#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include<glad/glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

enum mouvementCamera
{
	AVANT,
	ARRIERE,
	GAUCHE,
	DROITE
};

class Camera
{
public:
	Camera();
	~Camera();

	// Accesseurs
	glm::vec3 get_position() { return position; }
	glm::vec3 get_avant() { return avant; }
	glm::vec3 get_direction() { return direction; }
	glm::vec3 get_axe_X() { return axe_X; }
	glm::vec3 get_axe_Y() { return axe_Y; }
	glm::mat4 get_vue();
	float get_fov() { return fov; }

	// Mutateurs
	void set_position(glm::vec3 position)
	{
		this->position = position;
	}

	void traitementClavier(mouvementCamera, float deltaTime);
	void traitementSouris(double xpos, double ypos, float sensibilite);
	void zoomSouris(double yOffset);

private:
	void updateVectors();

	glm::vec3 position;
	glm::vec3 avant;
	glm::vec3 direction;
	glm::vec3 axe_X;
	glm::vec3 axe_Y;
	glm::vec3 haut;
	glm::vec3 hautWorld;
	glm::mat4 vue;
	float fov;
	float yaw;
	float pitch;
	float vitesseMouvement;
	float lastPosX;
	float lastPosY;
	bool firstMouse = true;
};

#endif