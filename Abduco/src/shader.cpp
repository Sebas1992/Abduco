#include "Shader.h"

Shader::Shader(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* tessellationControlSource, const GLchar* tessellationEvaluationSource, const GLchar* geometrySource)
{
    // Verifie si on a specifie un tessellationControl shader
    bool tessellation;
    bool geometry;

    //Verifie si on a specifie la tessellation et le geometry shader
    if(tessellationControlSource==NULL)
    {
        tessellation = false;
    }
    else
    {
        tessellation = true;
    }
    if(geometrySource == NULL)
    {
        geometry = false;
    }
    else
    {
        geometry = true;
    }

    std::ifstream fichierVertex;
    std::ifstream fichierFragment;
    std::ifstream fichierTessellationControl;
    std::ifstream fichierTessellationEvaluation;
    std::ifstream fichierGeometry;

    std::stringstream chaineVertex;
    std::stringstream chaineFragment;
    std::stringstream chaineTessellationControl;
    std::stringstream chaineTessellationEvaluation;
    std::stringstream chaineGeometry;

    std::string stringVertex;
    std::string stringFragment;
    std::string stringTessellationControl;
    std::string stringTessellationEvaluation;
    std::string stringGeometry;

    const GLchar* charVertex;
    const GLchar* charFragment;
    const GLchar* charTessellationControl;
    const GLchar* charTessellationEvaluation;
    const GLchar* charGeometry;

    fichierVertex.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fichierFragment.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fichierTessellationControl.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fichierTessellationEvaluation.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fichierGeometry.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        fichierVertex.open(vertexSource);
        fichierFragment.open(fragmentSource);

        chaineVertex << fichierVertex.rdbuf();
        chaineFragment << fichierFragment.rdbuf();

        stringVertex = chaineVertex.str();
        stringFragment = chaineFragment.str();

        charVertex = stringVertex.c_str();
        charFragment = stringFragment.c_str();

        fichierVertex.close();
        fichierFragment.close();

        if(tessellation)
        {
            fichierTessellationControl.open(tessellationControlSource);
            chaineTessellationControl << fichierTessellationControl.rdbuf();
            stringTessellationControl = chaineTessellationControl.str();
            charTessellationControl = stringTessellationControl.c_str();
            fichierTessellationControl.close();

            fichierTessellationEvaluation.open(tessellationEvaluationSource);
            chaineTessellationEvaluation << fichierTessellationEvaluation.rdbuf();
            stringTessellationEvaluation = chaineTessellationEvaluation.str();
            charTessellationEvaluation = stringTessellationEvaluation.c_str();
            fichierTessellationEvaluation.close();
        }
        if(geometry)
        {
            fichierGeometry.open(geometrySource);
            chaineGeometry << fichierGeometry.rdbuf();
            stringGeometry = chaineGeometry.str();
            charGeometry = stringGeometry.c_str();
            fichierGeometry.close();
        }

    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "Erreur lors de la lecture des shaders" << std::endl;
    }

    // Cree et compile le vertexShader
    GLuint vertexShader;
    GLint succesVertex;
    GLchar infoLogVertex[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &charVertex, NULL);
    glCompileShader(vertexShader);

    // Verifie la compilation du vertexShader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succesVertex);
    if (!succesVertex)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIED" << infoLogVertex << std::endl;
    }

    // Cree et compile le fragmentShader
    GLuint fragmentShader;
    GLint succesFragment;
    GLchar infoLogFragment[512];
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &charFragment, NULL);
    glCompileShader(fragmentShader);

    // Verifie la compilation de fragmentShader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succesFragment);
    if (!succesFragment)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FALIED" << infoLogFragment<< std::endl;
    }

    // Cree et compile le tessellationControlShader s'il existe
    GLuint tessellationControlShader;
    if(tessellation)
    {
        GLint succesTessellationControl;
        GLchar infoLogTessellationControl[512];
        tessellationControlShader = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessellationControlShader, 1, &charTessellationControl, NULL);
        glCompileShader(tessellationControlShader);

        // Verifie  la compilation du tessellationControlShader
        glGetShaderiv(tessellationControlShader, GL_COMPILE_STATUS, &succesTessellationControl);
        if (!succesTessellationControl)
        {
            glGetShaderInfoLog(tessellationControlShader, 512, NULL, infoLogTessellationControl);
            std::cout << "ERROR::SHADER::TESSELLATION::CONTROL::COMPILATION_FALIED" << infoLogTessellationControl << std::endl;
        }
    }

    // Cree et compile le tessellationEvaluationShader s'il existe
    GLuint tessellationEvaluationShader;
    if(tessellation)
    {
        GLint succesTessellationEvaluation;
        GLchar infoLogTessellationEvaluation[512];
        tessellationEvaluationShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tessellationEvaluationShader, 1, &charTessellationEvaluation, NULL);
        glCompileShader(tessellationEvaluationShader);

        // Verifie  la compilation du tessellationControlShader
        glGetShaderiv(tessellationEvaluationShader, GL_COMPILE_STATUS, &succesTessellationEvaluation);
        if (!succesTessellationEvaluation)
        {
            glGetShaderInfoLog(tessellationEvaluationShader, 512, NULL, infoLogTessellationEvaluation);
            std::cout << "ERROR::SHADER::TESSELLATION::EVALUATION::COMPILATION_FALIED" << infoLogTessellationEvaluation << std::endl;
        }
    }

    // Cree et compile le GeometryShader s'il existe
    GLuint geometryShader;
    if(geometry)
    {
        GLint succesGeometry;
        GLchar infoLogGeometry[512];
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &charGeometry, NULL);
        glCompileShader(geometryShader);

        // Verifie  la compilation du geometryShader
        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &succesGeometry);
        if (!succesGeometry)
        {
            glGetShaderInfoLog(geometryShader, 512, NULL, infoLogGeometry);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FALIED" << infoLogGeometry << std::endl;
        }
    }

    // Cree le programme, attache et lie les shaders
    program = glCreateProgram();
    GLint succesProgram;
    GLchar infoLogProgram[512];
    glAttachShader(program, fragmentShader);
    glAttachShader(program, vertexShader);
    if(tessellation)
    {
        glAttachShader(program, tessellationControlShader);
        glAttachShader(program, tessellationEvaluationShader);
    }
    if(geometry)
    {
        glAttachShader(program, geometryShader);
    }
    glLinkProgram(program);

    // Verifie que le programme est bien creer et lier
    glGetProgramiv(program, GL_LINK_STATUS, &succesProgram);
    if(!succesProgram)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLogProgram);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED" << infoLogProgram << std::endl;
    }

    // Detruit les shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if(tessellation)
    {
        glDeleteShader(tessellationControlShader);
        glDeleteShader(tessellationEvaluationShader);
    }
    if(geometry)
    {
        glDeleteShader(geometryShader);
    }
}

Shader::~Shader()
{
    
}

void Shader::utiliserProgramme()
{
    glUseProgram(program);
}
