#include "Camera.h"



Camera::Camera()
{
	vitesseMouvement = 2.5f;

	haut = glm::vec3(0.0f, 1.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	avant = glm::vec3(0.0f, 0.0f, -1.0f);
	direction = glm::normalize(position - avant);
	axe_X = glm::normalize(glm::cross(haut, direction));
	axe_Y = glm::normalize(glm::cross(direction, axe_X));
	vue = glm::lookAt(position, avant, haut);
}


Camera::~Camera()
{
}

void Camera::traitementClavier(mouvementCamera direction, float deltaTime)
{
	float velocite = vitesseMouvement * deltaTime;
	if (direction == AVANT)
	{
		position += avant * velocite;
	}
	if (direction == ARRIERE)
	{
		position -= avant * velocite;
	}
	if (direction == GAUCHE)
	{
		position -= axe_X * velocite;
	}
	if (direction == DROITE)
	{
		position += axe_X * velocite;
	}
}

glm::mat4 Camera::get_vue() 
{
	vue = glm::lookAt(position, avant + position, haut);
	return vue;
}