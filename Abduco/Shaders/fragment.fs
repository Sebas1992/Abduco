#version 450 core

in vec3 fragpos;
in vec3 normal;
in vec3 couleurAmbiante;
in vec3 diffuse;
uniform vec3 couleurCube;

out vec4 fragColor;

void main()
{	
	// Resultat
	vec3 resultat = (couleurAmbiante + diffuse) * couleurCube;
	fragColor = vec4(resultat, 1.0);
}