#version 450 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 anormal;

out vec3 normal;
out vec3 fragpos;

uniform mat4 projection;
uniform mat4 vue;
uniform mat4 modele;

void main()
{
	fragpos = vec3(modele * vec4(pos, 1.0f));
	normal = mat3(transpose(inverse(modele))) * anormal;
    gl_Position = projection * vue * vec4(fragpos, 1.0);
}