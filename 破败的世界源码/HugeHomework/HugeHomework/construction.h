#pragma once
#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H


#include <GL\glew.h>
#include "point3D.h"
#include"constant.h"
class Construction
{
public:

	//一个建筑有三个贴图 东西一样 南北一样 上下一样 
	float length, width, height;
	GLuint *texture_eastWest;
	GLuint* texture_southNorth;
	GLuint* texture_upDown;

public:
	Construction(float l, float w, float h, GLuint* eastW, GLuint* southN, GLuint* upD);
	~Construction()
	{

	}
};



#endif