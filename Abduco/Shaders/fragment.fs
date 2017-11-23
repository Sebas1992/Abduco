#version 450 core

in vec3 fragpos;
in vec3 normal;
in vec3 couleurAmbiante;
in vec3 diffuse;
in vec3 specular;
uniform vec3 couleurCube;

out vec4 fragColor;

void main()
{	
	// Resultat
	vec3 resultat = (couleurAmbiante + diffuse + specular) * couleurCube;
	fragColor = vec4(resultat, 1.0);
}