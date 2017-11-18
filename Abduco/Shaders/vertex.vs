#version 450 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 colorIn;
layout(location=2) in vec2 inTexCoord;

out vec3 color;
out vec2 textureCoord;

uniform mat4 transformation;

void main()
{
    gl_Position = transformation * vec4(pos, 1.0);
    color = colorIn;
    textureCoord = inTexCoord;
}