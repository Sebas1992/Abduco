#include "Camera.h"



Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	cible = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(position - cible);
	axe_X = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
	axe_Y = glm::normalize(glm::cross(direction, axe_X));
	vue = glm::lookAt(position, cible, glm::vec3(0.0f, 1.0f, 0.0f));
}


Camera::~Camera()
{
}

void Camera::set_vue(glm::vec3 position, glm::vec3 cible, glm::vec3 haut)
{
	this->position = position;
	this->cible = cible;
	this->vue = glm::lookAt(this->position, this->cible + this->position, haut);
}
