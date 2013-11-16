#pragma once
#include <GL\glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <SFML/Window.hpp>
#include <iostream>
class Shader
{
public:
	Shader(void);
	~Shader(void);
    void CompileShaders();
	
private:
	static const char* pVS;
	static const char* pFS;
	static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
};

