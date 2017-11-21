#version 450 core

out vec4 fragColor;

uniform vec3 couleurCube;
uniform vec3 couleurLumiere;

void main()
{
    fragColor = vec4(couleurCube * couleurLumiere, 1.0f);
}