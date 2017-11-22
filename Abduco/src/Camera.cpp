#include "Camera.h"



Camera::Camera()
{
	vitesseMouvement = 2.5f;

	hautWorld = glm::vec3(0.0f, 1.0f, 0.0f);
	haut = glm::vec3(0.0f, 1.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	avant = glm::vec3(0.0f, 0.0f, -1.0f);
	direction = glm::normalize(position - avant);
	axe_X = glm::normalize(glm::cross(haut, direction));
	axe_Y = glm::normalize(glm::cross(direction, axe_X));
	vue = glm::lookAt(position, avant, haut);
	yaw = 0.0f;
	pitch = 0.0f;
	fov = 45.0f;
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

void Camera::traitementSouris(double xpos, double ypos, float sensibilite)
{
	if (firstMouse)
	{
		lastPosX = xpos;
		lastPosY = ypos;
		firstMouse = false;
	}

	float xOffset, yOffset;
	xOffset = xpos - lastPosX;
	yOffset = lastPosY - ypos;
	lastPosX = xpos;
	lastPosY = ypos;

	xOffset *= sensibilite;
	yOffset *= sensibilite;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateVectors();
}

glm::mat4 Camera::get_vue() 
{
	vue = glm::lookAt(position, position + avant, haut);
	return vue;
}

void Camera::updateVectors()
{
	glm::vec3 avantTemp;
	avantTemp.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	avantTemp.y = sin(glm::radians(pitch));
	avantTemp.z = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	avant = glm::normalize(avantTemp);

	axe_X = glm::normalize(glm::cross(avant, hautWorld));
	axe_Y = glm::normalize(glm::cross(axe_X, avant));
}

void Camera::zoomSouris(double yOffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
	{
		fov -= yOffset * 0.05f;
	}
	if (fov <= 1.0f)
	{
		fov = 1.0f;
	}
	if (fov >= 45.0f)
	{
		fov = 45.0f;
	}
}
