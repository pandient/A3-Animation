#pragma once
#include <GL\glew.h>
#include<vector>
#include"SFML\OpenGL.hpp"
#include"SFML\Graphics.hpp"
#include "Pipeline.h"
#include "Shader.h"
#define bwidth 0.05
class Bone
{
public:
	float x,y,a,l;

	std::vector<Bone*> *child;
	Bone * parent; 
	Bone(void);
	~Bone(void);
	Bone(float x ,float y ,float a ,float l, Bone * parent);
	void AddChild(Bone* childBone);
	
	void Draw();
private:
	GLuint VBO;
	GLuint IBO;

};

