#pragma once
#ifndef POINT_H
#define POINT_H


struct Point3D
{
	float x;
	float y;
	float z;
	Point3D(float x_=0,float y_=0,float z_=0)
	{
		this->x = x_;
		this->y = y_;
		this->z = z_;
	}

	bool operator < (const Point3D& a) const 
	{
		/*if (this->x != a.x)
		{
			return this->x < a.x;
		}
		else if (this->y != a.y)
		{
			return this->y < a.y;
		}
		else
		{
			return this->z < a.z;
		}*/
		return true;
	}
};












#endif // !POINT_H

