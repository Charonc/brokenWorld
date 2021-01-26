#include"construction.h"


Construction::Construction( float l, float w, float h, GLuint* eastW, GLuint* southN, GLuint* upD)
{
		this->length = l;
		this->width = w;
		this->height = h;
		this->texture_eastWest = eastW;
		this->texture_southNorth = southN;
		this->texture_upDown = upD;
}



