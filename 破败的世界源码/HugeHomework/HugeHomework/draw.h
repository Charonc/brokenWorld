#pragma once
#ifndef DRAW_H
#define DRAW_H
#include<GL\glew.h>
#include<iostream>
//#include<iterator>
#include<vector>
#include<map>
#include<memory>
#include<vector>
#include<string.h>
#include<Windows.h>
#include"constant.h"
#include"construction.h"
#include"camera.h"
#include "SOIL.h"
#include "Angel.h"
#include "mat.h"
#include "vec.h"
#include"point3D.h"

using namespace std;
#pragma comment(lib, "glew32.lib")
struct texture_data;





texture_data load_texture(const char* path);
Point3D getPos(const Camera& cam);
Point3D getPos2(const Camera &cam);
void building_bind_textures();//建筑物绑定贴图同时添加到建筑物数组中
void draw_buildings();
void change_building();
void add_new_building(Point3D p);
void add_textures();
void clear_all_building();
void cancel_justnow_building();
void material_sun();
void draw_sun();
void material_planet();
void draw_earth();
void draw_moon();
void draw_mars();
void draw_mars_sky();
void draw_universe(float x, float y, float z, float width, float height, float len);
void draw_greenGrand();
void draw_building(Point3D center, const Construction& con);
void draw_skybox();
void draw_dormitory();




















#endif // !1

