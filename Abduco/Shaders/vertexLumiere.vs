#version 450 core

layout(location=0) in vec3 pos;

uniform mat4 projection;
uniform mat4 vue;
uniform mat4 modele;

void main()
{
    gl_Position = projection * vue * modele * vec4(pos, 1.0);
}