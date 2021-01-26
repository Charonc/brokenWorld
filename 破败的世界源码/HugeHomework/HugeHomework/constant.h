#pragma once
#ifndef CONSTANT_H
#define CONSTANT_H
#include<math.h>

const float earth_sandbox_length = 1000.0f;
const float p = 0.3f;//整体尺寸 越大 建筑物越大 
const float earth_size = sqrt(3.3) / 2.0 * earth_sandbox_length;
const float sun_size = 3 * earth_size;
const float mars_size = earth_size * 0.533;
const float mars_sandbox_length = mars_size * 2 / sqrt(3.5);
const float moon_size = earth_size*0.2725;
const float mars_earth_dis = sun_size * 11.0f;
const float sun_earth_dis = sun_size * 5.0f;
const float moon_earth_dis = earth_size * 3.0f;
const float build_dis = 30.0f;
static  float speed = 5.0f;
const int skyModeNum = 3;

















#endif // !CONSTANT
