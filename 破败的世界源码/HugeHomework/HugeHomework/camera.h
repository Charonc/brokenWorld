#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include "Angel.h"
#include "mat.h"
#include "vec.h"
#include<vector>
#pragma comment(lib, "glew32.lib")

class Camera
{
public:
	vec3 eye;
	vec3 at;
	vec3 up;
	Camera()
	{
		vec3 eye = vec3{ 0.0,1.35,-30.0 };
		vec3 at = vec3{ 0.0,0.0,0.0 };
		vec3 up = vec3{ 0.0,1.0,0.0 };
	}
	Camera(vec3 eye, vec3 at, vec3 up = vec3{0.0,1.0,0.0})
	{
		this->eye = eye;
		this->at = at;
		this->up = up;
	}
	void view1(float radius=100.0f,float rotateAngle=-90.0f,float upAngle=10.0f);
	void view2();

	/** 旋转摄像机方向 */
	void rotateView(float angle, float x, float y, float z);

	/** 根据鼠标设置摄像机观察方向 */
	void setViewByMouse(int x,int y);

	/** 左右摄像机移动 */
	void yawCamera(float speed);

	/** 前后移动摄像机 */
	void moveCamera(float speed,int mode);
	void upDownCamera(float speed);


};

#endif