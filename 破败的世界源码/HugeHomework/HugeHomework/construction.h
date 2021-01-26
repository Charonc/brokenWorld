#pragma once
#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H


#include <GL\glew.h>
#include "point3D.h"
#include"constant.h"
class Construction
{
public:

	//һ��������������ͼ ����һ�� �ϱ�һ�� ����һ�� 
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