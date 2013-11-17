#include "Bone.h"



Bone::Bone(void)
{
}


Bone::~Bone(void)
{
	delete child;
}


Bone :: Bone(float x ,float y ,float a ,float l, Bone * parent) : x(x) , y(y) , l(l) , a(a) , parent(parent)
{
	Bone::child  = new std::vector<Bone*>();

	sf::Vector3f Vertices[4];
    Vertices[0] = sf::Vector3f(x - bwidth, y, 0.0f);
    Vertices[1] = sf::Vector3f(x - bwidth, y + l, 0.0f);
    Vertices[2] = sf::Vector3f(x + bwidth, y + l, 0.0f);
	Vertices[3] = sf::Vector3f(x + bwidth, y, 0.0f);

	/*Vector3f Vertices[4];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
    Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);*/

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	 unsigned int Indices[] = { 0, 1, 2,
                               2, 3, 0};

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void Bone::Draw(){

	    glClear(GL_DEPTH_BUFFER_BIT);
		
		Pipeline p;
		p.Scale(1.0f,1.0f, 1.0f);
		p.WorldPos(x, y, 0.0f);
		p.Rotate(0.0f, 0.0f, a);

		
   glUniformMatrix4fv(Shader::gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());


		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);

	for(std::vector<Bone*>::iterator it = child->begin(); it != child->end(); it++){
			(*it)->Draw();
	}
}

void Bone::AddChild(Bone * childBone){
	child->push_back(childBone);
}