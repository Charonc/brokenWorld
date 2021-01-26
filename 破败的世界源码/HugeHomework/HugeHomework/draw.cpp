#include"draw.h"

typedef struct texture_data {
	unsigned char* data;
	int width, height;
} texture_data;

const int img_num = 50;
static float fMoonRot = 0.0f;
static float fEarthRot = 0.0f;
GLUquadricObj* e_tex = gluNewQuadric();//texture
GLuint texture[img_num];
texture_data TextureImage[img_num];// 创建纹理的存储空间
int building_now = 0;
vector<shared_ptr<Construction>> buildings;//存储建筑物的数组
map<Point3D, shared_ptr<Construction>> buildingsMap;

texture_data load_texture(const char* path)
{
	texture_data t;
	//unsigned char* image;
	int width, height;
	t.data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	t.width = width;
	t.height = height;
	//SOIL_free_image_data(image);
	return t;
}




void add_textures() // 添加纹理样式
{

	//int Status = FALSE; // 状态指示器
	memset(TextureImage, 0, sizeof(void*) * img_num); // 将指针设为 NULL
	TextureImage[0] = load_texture("pic/skybox2/0_东_F.jpg");
	TextureImage[1] = load_texture("pic/skybox2/1_西_B.jpg");
	TextureImage[2] = load_texture("pic/skybox2/2_南_R.jpg");
	TextureImage[3] = load_texture("pic/skybox2/3_北_L.jpg");
	TextureImage[4] = load_texture("pic/skybox2/4_上_U.jpg");
	TextureImage[5] = load_texture("pic/skybox2/5_下_D.jpg");
	TextureImage[6] = load_texture("pic/stars/universe.png");
	TextureImage[7] = load_texture("pic/stars/sun.jpg");
	TextureImage[8] = load_texture("pic/stars/earth.jpg");
	TextureImage[9] = load_texture("pic/stars/moon.jpg");
	TextureImage[10] = load_texture("pic/stars/mars.jpg");
	TextureImage[11] = load_texture("pic/8_floor2.bmp");
	TextureImage[12] = load_texture("pic/9.bmp");

	TextureImage[15] = load_texture("pic/buildings/15_楼1前后.bmp");
	TextureImage[16] = load_texture("pic/buildings/16_楼1左右.bmp");
	TextureImage[17] = load_texture("pic/buildings/17_楼1上下.bmp");

	TextureImage[18] = load_texture("pic/buildings/18_楼2前后.bmp");
	TextureImage[19] = load_texture("pic/buildings/19_楼2左右.bmp");
	TextureImage[20] = load_texture("pic/buildings/20_楼2上下.bmp");

	TextureImage[21] = load_texture("pic/buildings/21_楼3前后.bmp");
	TextureImage[22] = load_texture("pic/buildings/22_楼3左右.bmp");
	TextureImage[23] = load_texture("pic/buildings/23_楼3上下.bmp");

	TextureImage[24] = load_texture("pic/buildings/24_楼4前后.bmp");
	TextureImage[25] = load_texture("pic/buildings/25_楼4左右.bmp");
	TextureImage[26] = load_texture("pic/buildings/26_楼4上下.bmp");


	TextureImage[39] = load_texture("pic/39_绿地.png");
	TextureImage[40] = load_texture("pic/skybox3/0_东_F.jpg");
	TextureImage[41] = load_texture("pic/skybox3/1_西_B.jpg");
	TextureImage[42] = load_texture("pic/skybox3/2_南_R.jpg");
	TextureImage[43] = load_texture("pic/skybox3/3_北_L.jpg");
	TextureImage[44] = load_texture("pic/skybox3/4_上_U.jpg");
	TextureImage[45] = load_texture("pic/skybox3/5_下_D.jpg");


	//tietu设置！


	glGenTextures(img_num, &texture[0]); // 创建纹理
	for (int i = 0; i < img_num; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i].width, TextureImage[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i].data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线形滤波
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 线形滤波
	}

	for (int i = 0; i < img_num; i++)
	{
		SOIL_free_image_data(TextureImage[i].data);
	}



	building_bind_textures();
	
}
void building_bind_textures()
{
 buildings.push_back((shared_ptr<Construction>)new Construction(p * 30, p * 40, p * 50, &texture[15], &texture[16], &texture[17]));//添加到buildings中
 buildings.push_back((shared_ptr<Construction>)new Construction(p * 40, p * 30, p * 50, &texture[16], &texture[15], &texture[17]));

 buildings.push_back((shared_ptr<Construction>)new Construction(p * 30, p * 40, p * 50, &texture[18], &texture[19], &texture[20]));//添加到buildings中
 buildings.push_back((shared_ptr<Construction>)new Construction(p * 40, p * 30, p * 50, &texture[19], &texture[18], &texture[20]));

 buildings.push_back((shared_ptr<Construction>)new Construction(p * 30, p * 40, p * 50, &texture[21], &texture[22], &texture[23]));//添加到buildings中
 buildings.push_back((shared_ptr<Construction>)new Construction(p * 40, p * 30, p * 50, &texture[22], &texture[21], &texture[23]));

 buildings.push_back((shared_ptr<Construction>)new Construction(p * 30, p * 40, p * 50, &texture[24], &texture[25], &texture[26]));//添加到buildings中
 buildings.push_back((shared_ptr<Construction>)new Construction(p * 40, p * 30, p * 50, &texture[25], &texture[24], &texture[26]));
}
void clear_all_building()
{
	buildingsMap.clear();
}
void cancel_justnow_building()
{
	if (buildingsMap.empty())
	{
		return;
	}
	map<Point3D, shared_ptr<Construction>>::iterator i = buildingsMap.end();
	if (i != buildingsMap.begin())
	{
		i--;
		buildingsMap.erase(i);
	}
	else
	{
		buildingsMap.erase(i);
	}
}
void change_building()
{
	building_now++;
	if (building_now >= buildings.size())
	{
		building_now %= buildings.size();
	}
}
void add_new_building(Point3D p )
{
	buildingsMap.insert(make_pair(p, buildings[building_now]));
}
void draw_building(Point3D center, const Construction& con)
{
	Point3D vertexs[8];
	center.y += con.height / 2.0;
	vertexs[0].x = center.x - con.width / 2.0;
	vertexs[0].y = center.y + con.height / 2.0;
	vertexs[0].z = center.z - con.length / 2.0;

	vertexs[1].x = center.x - con.width / 2.0;
	vertexs[1].y = center.y + con.height / 2.0;
	vertexs[1].z = center.z + con.length / 2.0;

	vertexs[2].x = center.x - con.width / 2.0;
	vertexs[2].y = center.y - con.height / 2.0;
	vertexs[2].z = center.z - con.length / 2.0;

	vertexs[3].x = center.x - con.width / 2.0;
	vertexs[3].y = center.y - con.height / 2.0;
	vertexs[3].z = center.z + con.length / 2.0;

	vertexs[4].x = center.x + con.width / 2.0;
	vertexs[4].y = center.y + con.height / 2.0;
	vertexs[4].z = center.z - con.length / 2.0;

	vertexs[5].x = center.x + con.width / 2.0;
	vertexs[5].y = center.y + con.height / 2.0;
	vertexs[5].z = center.z + con.length / 2.0;

	vertexs[6].x = center.x + con.width / 2.0;
	vertexs[6].y = center.y - con.height / 2.0;
	vertexs[6].z = center.z - con.length / 2.0;

	vertexs[7].x = center.x + con.width / 2.0;
	vertexs[7].y = center.y - con.height / 2.0;
	vertexs[7].z = center.z + con.length / 2.0;

	glDepthMask(GL_TRUE);
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	//六个面
	//1  4 0 2 6 西
	//2  1 5 7 3  东
	//3  0 1 3 2   前
	//4  5 4 6 7  后
	//5  4 5 1 0 上
	//6  6 7 3 2 下


	//东西
	//东面
	glBindTexture(GL_TEXTURE_2D, *con.texture_eastWest);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[1].x, vertexs[1].y, vertexs[1].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[5].x, vertexs[5].y, vertexs[5].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[7].x, vertexs[7].y, vertexs[7].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[3].x, vertexs[3].y, vertexs[3].z);
	//  西面 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[4].x, vertexs[4].y, vertexs[4].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[0].x, vertexs[0].y, vertexs[0].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[2].x, vertexs[2].y, vertexs[2].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[6].x, vertexs[6].y, vertexs[6].z);
	glEnd();


	//南北
	glBindTexture(GL_TEXTURE_2D, *con.texture_southNorth);
	glBegin(GL_QUADS);
	//南面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[5].x, vertexs[5].y, vertexs[5].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[4].x, vertexs[4].y, vertexs[4].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[6].x, vertexs[6].y, vertexs[6].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[7].x, vertexs[7].y, vertexs[7].z);
	//  北面 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[0].x, vertexs[0].y, vertexs[0].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[1].x, vertexs[1].y, vertexs[1].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[3].x, vertexs[3].y, vertexs[3].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[2].x, vertexs[2].y, vertexs[2].z);
	glEnd();


	//上下
	glBindTexture(GL_TEXTURE_2D, *con.texture_upDown);
	glBegin(GL_QUADS);												//  封顶
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[4].x, vertexs[4].y, vertexs[4].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[5].x, vertexs[5].y, vertexs[5].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[1].x, vertexs[1].y, vertexs[1].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[0].x, vertexs[0].y, vertexs[0].z);
	glEnd();
	//下
	glBindTexture(GL_TEXTURE_2D, *con.texture_upDown);
	glBegin(GL_QUADS);												//  封顶
	glTexCoord2f(0.0f, 0.0f); glVertex3f(vertexs[6].x, vertexs[6].y, vertexs[6].z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(vertexs[7].x, vertexs[7].y, vertexs[7].z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(vertexs[3].x, vertexs[3].y, vertexs[3].z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(vertexs[2].x, vertexs[2].y, vertexs[2].z);
	glEnd();




	glBindTexture(GL_TEXTURE_2D, 0);
	//glDepthMask(GL_FALSE);
	glPopAttrib();
}
void draw_buildings()
{
	for (map<Point3D, shared_ptr<Construction>>::iterator i = buildingsMap.begin(); i != buildingsMap.end(); i++)
	{
		draw_building(i->first, *i->second);
	}
}
Point3D getPos(const Camera& cam)
{
	Point3D poi;
	vec3 vector = cam.at - cam.eye;
	vector = normalize(vector);
	poi.x = cam.eye.x + vector.x * p * build_dis;
	poi.z = cam.eye.z + vector.z * p * build_dis;
	//poi.y = 0;
	poi.y = cam.eye.y + vector.y * p * build_dis;
	return poi;
}
Point3D getPos2(const Camera&cam)
{
	Point3D poi;
	vec3 vector = cam.at - cam.eye;
    vector = normalize(vector);
	poi.x = cam.eye.x + vector.x * p * build_dis;
	poi.z = cam.eye.z + vector.z * p * build_dis;
	poi.y = 0;
	return poi;
}


void material_sun()
{
	GLfloat sun_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的环境光颜色，为0
	GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色，为0
	GLfloat sun_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
	GLfloat sun_mat_emission[] = { 1.0f, 1.0f, 1.0f, 0.0f };   //定义材质的辐射广颜色，为偏红色
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	//glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);
}
void draw_sun()
{
	glPushMatrix();
	//glEnable(GL_LIGHTING);
	glTranslatef(p * sun_earth_dis, 0.0f, 0.0f);
	//material_sun();
	/*glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);*/

	gluQuadricTexture(e_tex, GLU_TRUE);
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	//glTranslatef(0.0f, 0.0f, 0.0f);
	gluSphere(e_tex, p * sun_size, 300.0f, 300.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	//glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	gluQuadricTexture(e_tex, GLU_FALSE);
	glPopMatrix();
}
void material_planet()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的环境光颜色，骗蓝色
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //定义材质的漫反射光颜色，偏蓝色
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };   //定义材质的镜面反射光颜色，红色
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
	//GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sun_light_ambient);
	//GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_light_specular);
	//glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 5);
}
void draw_earth()
{

	glPushMatrix();
	//material_planet();
	//glEnable(GL_LIGHTING);

	static float sEarthRot = 0.0f;
	/*glRotatef(aEarthRot, 0.0f, 1.0f, 0.0f);*/
	glTranslatef(0.0f, 0.0f, 0.0f);
	//glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	//glPopMatrix();
	glRotatef(sEarthRot, 0.0f, 0.0f, 1.0f);

	gluQuadricTexture(e_tex, GLU_TRUE);
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_EVN_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	//glColor3ub(0, 0, 255);

	gluSphere(e_tex, p * earth_size, 30.0f, 30.0f);
	glPopAttrib();

	/*gluQuadricTexture(e_tex, GLU_FALSE);
	glColor3ub(200, 200, 200);*/


	sEarthRot += (360.0 / 24.0) * 0.01;
	//std::cout << sEarthRot << std::endl;
	if (sEarthRot >= 360.0f)
		sEarthRot = 0.0f;


	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}
void draw_moon()
{
	glPushMatrix();
	static float aMoonRot = 0.0f;
	static float sMoonRot = 0.0f;
	glBindTexture(GL_TEXTURE_2D, 0);
	glRotatef(aMoonRot, 0.0f, -1.0f, 0.0f);


	glTranslatef(p * moon_earth_dis, 0.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(sMoonRot, 0.0f, 0.0f, 1.0f);

	gluQuadricTexture(e_tex, GLU_TRUE);
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_EVN_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	gluSphere(e_tex, p * moon_size, 30.0f, 30.0f);

	aMoonRot += 3.0f * 0.1;
	if (aMoonRot >= 360.0f)
		aMoonRot = 0.0f;

	sMoonRot += (360.0 / 24.0) * 0.01 /5;
	if (sMoonRot >= 360.0f)
		sMoonRot = 0.0f;

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}
void draw_mars()
{
	static float sMarsRot = 0.0f;
	glPushMatrix();
	//glEnable(GL_LIGHTING);
	glTranslatef(p * mars_earth_dis, 0.0f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	//glPopMatrix();
	glRotatef(sMarsRot, 0.0f, 0.0f, 1.0f);
	//material_sun();
	/*glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_EMISSION, LightEmission);*/

	gluQuadricTexture(e_tex, GLU_TRUE);
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	//glTranslatef(0.0f, 0.0f, 0.0f);
	gluSphere(e_tex, p*mars_size, 30.0f, 30.0f);
	glBindTexture(GL_TEXTURE_2D, 0);

	//glDisable(GL_TEXTURE_2D);
	glPopAttrib();


	sMarsRot += (360.0 / 24.0) * 0.01/1.5;
	//std::cout << sEarthRot << std::endl;
	if (sMarsRot >= 360.0f)
		sMarsRot = 0.0f;


	gluQuadricTexture(e_tex, GLU_FALSE);
	glPopMatrix();
}
void draw_universe(float x, float y, float z, float width, float height, float len)
{
	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glDepthMask(GL_FALSE);
	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, texture[6]);

	//back face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();
	//front face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z + len);
	glEnd();
	//bottom face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y, z);
	glEnd();
	//top face
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y + height, z);


	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);


	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + height, z + len);


	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y + height, z);
	glEnd();
	//left face
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y + height, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + height, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	//right face
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + width, y, z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + width, y, z + len);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + width, y + height, z + len);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + width, y + height, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);



	glDepthMask(GL_TRUE);
	glPopAttrib();

}
void draw_greenGrand()
{
	glBindTexture(GL_TEXTURE_2D, texture[39]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-p * earth_sandbox_length / 2, 0, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, 0, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, 0, -p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, 0, -p * earth_sandbox_length / 2);
	glEnd();
}
void draw_skybox()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);//东    初始正前方 z轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[1]);//西    后   Z轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[2]);//南  右     X轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[3]);//北 左     X轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[4]);//顶   y轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[5]);//底  y轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, p * earth_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2, -p * earth_sandbox_length / 2);
	glEnd();

}
void draw_mars_sky()
{
	glBindTexture(GL_TEXTURE_2D, texture[40]);//东    初始正前方 z轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-p * mars_sandbox_length / 2+p*mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[41]);//西    后   Z轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[42]);//南  右     X轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[43]);//北 左     X轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p*mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[44]);//顶   y轴正方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-p * mars_sandbox_length / 2 + p * mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-p * mars_sandbox_length / 2 + p * mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p * mars_earth_dis, p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p * mars_earth_dis, p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[45]);//底  y轴负方向
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * mars_sandbox_length / 2 + p * mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-p * mars_sandbox_length / 2 + p * mars_earth_dis, -p * mars_sandbox_length / 2, -p * mars_sandbox_length / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-p * mars_sandbox_length / 2 + p * mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * mars_sandbox_length / 2 + p * mars_earth_dis, -p * mars_sandbox_length / 2, p * mars_sandbox_length / 2);
	glEnd();

}
void draw_dormitory()
{
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	glBegin(GL_QUADS);												//  南面
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(p * 30.0f, p * 15.0f, p * 0.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * 0.0f, p * 15.0f, p * 0.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * 0.0f, p * 0.0f, p * 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * 30.0f, p * 0.0f, p * 0.0f);
	//  北面 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * 0.0f, p * 15.0f, -p * 15.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * 30.0f, p * 15.0f, -p * 15.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * 30.0f, p * 0.0f, -p * 15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * 0.0f, p * 0.0f, -p * 15.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[16]);
	glBegin(GL_QUADS);												//  东面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * 30.0f, p * 15.0f, -p * 15.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * 30.0f, p * 15.0f, p * 0.0f); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * 30.0f, p * 0.0f, p * 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * 30.0f, p * 0.0f, -p * 15.0f);
	//  西面 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * 0.0f, p * 15.0f, p * 0.0f); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * 0.0f, p * 15.0f, -p * 15.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * 0.0f, p * 0.0f, -p * 15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * 0.0f, p * 0.0f, p * 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[17]);
	glBegin(GL_QUADS);												//  封顶
	glTexCoord2f(0.0f, 0.0f); glVertex3f(p * 0.0f, p * 15.0f, p * 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(p * 30.0f, p * 15.0f, p * 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(p * 30.0f, p * 15.0f, -p * 15.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(p * 0.0f, p * 15.0f, -p * 15.0f);
	glEnd();

}
