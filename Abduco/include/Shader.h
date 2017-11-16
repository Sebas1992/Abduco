#ifndef SHADER_H
#define SHADER_H

#include<iostream>
#include<fstream>
#include<sstream>

#ifdef GLAD_H
    #include<glad/glad.h>
#elif defined GLEW_H
    #include<GLEW/glew.h>
#endif

class Shader
{
    public:
        Shader(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* tessellationControlSource = NULL, const GLchar* tessellationEvaluationSource = NULL, const GLchar* geometrySource = NULL);
        ~Shader();
        void utiliserProgramme();
        GLint get_program(){return program;}
    private:
        GLuint program;
};

#endif // SHADER_H
