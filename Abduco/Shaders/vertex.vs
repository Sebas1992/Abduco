#version 450 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 anormal;

out vec3 normal;
out vec3 fragpos;
out vec3 couleurAmbiante;
out vec3 diffuse;

uniform mat4 projection;
uniform mat4 vue;
uniform mat4 modele;
uniform vec3 couleurLumiere;
uniform vec3 posLumiere;

float specularStrength = 0.5;
float forceLumiereAmbiante = 0.1;

void main()
{
	
	fragpos = vec3(modele * vec4(pos, 1.0f));
	//normal = mat3(transpose(inverse(modele))) * anormal;
    gl_Position = projection * vue * modele * vec4(fragpos, 1.0);

	// Ambiante
	couleurAmbiante = couleurLumiere * forceLumiereAmbiante;

	// Diffuse
	normal = normalize(anormal);
	vec3 directionLumiere = normalize(posLumiere-fragpos);
	float diff = max(dot(normal, directionLumiere), 0.0);
	diffuse = diff * couleurLumiere;
}