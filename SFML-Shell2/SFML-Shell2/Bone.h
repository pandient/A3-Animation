#pragma once
#include<vector>
class Bone
{
public:
	float x,y,a,l,offA,offL;
	std::vector<Bone> child;
	Bone * parent; 
	Bone(void);
	~Bone(void);
	void Draw();
};

