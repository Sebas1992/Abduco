#version 450 core

in vec3 fragpos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 couleurCube;
uniform vec3 couleurLumiere;
uniform vec3 posLumiere;

void main()
{	
	// ambiant
	float forceLumiereAmbiante = 0.1;
	vec3 couleurAmbiante = forceLumiereAmbiante * couleurLumiere;
	
	// diffuse
	vec3 norm = normalize(normal);
	vec3 directionLumiere = normalize(posLumiere - fragpos);
    float diff =  max(dot(norm, directionLumiere), 0.0);
	vec3 diffuse = diff * couleurLumiere;	
	
	// Resultat
	vec3 resultat = (couleurAmbiante + diff) * couleurCube;
	fragColor = vec4(resultat, 1.0);
}