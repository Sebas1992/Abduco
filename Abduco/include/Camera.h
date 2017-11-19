#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	// Accesseurs
	glm::vec3 get_position() { return position; }
	glm::vec3 get_cible() { return cible; }
	glm::vec3 get_direction() { return direction; }
	glm::vec3 get_axe_X() { return axe_X; }
	glm::vec3 get_axe_Y() { return axe_Y; }
	glm::mat4 get_vue() { return vue; }

	// Mutateurs
	void set_vue(glm::vec3 position, glm::vec3 cible, glm::vec3 haut)
	{
		this->position = position;
		this->cible = cible;
		this->vue = glm::lookAt(this->position, this->cible, haut);
	}

private:
	glm::vec3 position;
	glm::vec3 cible;
	glm::vec3 direction;
	glm::vec3 axe_X;
	glm::vec3 axe_Y;
	glm::mat4 vue;
};

#endif