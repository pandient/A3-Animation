#include "Shader.h"
#include <stdio.h>
using namespace std;

const char* Shader::pVS= "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 Position;                                       \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);  \n\
}";

 const char* Shader::pFS = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 FragColor;                                                           \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);                                     \n\
}";

Shader::~Shader(void)
{
}

Shader::Shader(void)
{
	


}

 void Shader::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType){
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        cout<< "Error creating shader type" << ShaderType <<endl;
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		cout << "" << ShaderType << "  " << InfoLog << "  " << endl;
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
 }

void Shader::CompileShaders(void)
{
GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
       
		cout << "Error creating shader program\n" << endl;
		exit(1);
    }

    AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
    AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		//fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		cout << "Error linking shader program: " << ErrorLog << endl;
        exit(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
       // fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}