#include"draw.h"


/*---------------------------------------------------------------�����������---------------------------------------------------------------------------------------*/
int mainWindow;
static int oldmy = -1, oldmx = -1; //du���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���
float radius = 100.0f;
float rotateAngle = -90.0f;
float upAngle = 10.0f;
// �������
bool camera_mode1 = true;//trueΪ�������ģʽ  falseΪ���ģʽ
int camera_mode2 = 1;//0����ģʽ  1�̶�ģʽ
int build_mode = 0;//0���潨��  1���ɽ���
Camera cam(vec3(0.0, 10.0*p, -30.0),vec3(0.0, 0.0,0.0));
POINT clickPos;
GLfloat deltax = 0.0f;
GLfloat deltay = 0.0f;
static int skyMode = 0;
/*---------------------------------------------------------------�����������---------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------���������---------------------------------------------------------------------------------------*/
void Mouse(int button, int state, int x, int y) //���������
{
	if (button == 3 || button == 4) {
		if (button == 3)
			radius -= 10;

		if (button == 4)
			radius += 10;

	}

	
	if (state == GLUT_DOWN) {
		GetCursorPos(&clickPos);
		oldmx = x, oldmy = y;
	}
	
}
void motion(int x, int y)
{
	//std::cout << x << std::endl;
	if (camera_mode1 == true)
	{
		cam.setViewByMouse(clickPos.x, clickPos.y);
		glutPostRedisplay();

	}
	else 
	{
		deltax = x - oldmx; //����ڴ���x�᷽���ϵ������ӵ��ӵ���y��ĽǶ��ϣ�����������ת��
		deltay = y - oldmy; //����ڴ���y�᷽���ϵĸı�ӵ��ӵ��y�����ϣ�������ת��
		rotateAngle += deltax;
		upAngle += deltay;
		oldmx = x, oldmy = y; //�Ѵ�ʱ�����������Ϊ��ֵ��Ϊ��һ�μ���������׼��
	}

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'W':
		cam.moveCamera(p*speed,camera_mode2);
		break;
	case 'S':
		cam.moveCamera(p*-speed, camera_mode2);
		break;
	case 'A':
		cam.yawCamera(p*-speed);
		break;
	case 'D':
		cam.yawCamera(p*speed);
		break;
	case 'Q':
		cam.upDownCamera(p * speed);
		break;
	case 'E':
		cam.upDownCamera(-p * speed);
		break;
	case 'C':
		clear_all_building();
		break;
	case 'K':
		++skyMode%=skyModeNum;
		break;
	case 'P':
		++build_mode %= 2;
		break;
	case 'Z':
		cancel_justnow_building();
		break;
	case 'M':
		camera_mode1 = !camera_mode1;
		//std::cout << camera_mode << std::endl;
		break;
	case '	':
		change_building();
		break;
	case 'R':
		if (build_mode == 1)
			add_new_building(getPos(cam));
		else
			add_new_building(getPos2(cam));
		break;
	case '+':
		speed += 1;
		break;
	case '-':
		speed -= 1;
		break;
	case 033:
		// Esc����
		exit(EXIT_SUCCESS);
		break;
	}




	glutPostWindowRedisplay(mainWindow);
}
/*----------------------------------------------------------------���������---------------------------------------------------------------------------------------*/




/*----------------------------------------------------------------��ʼ�����---------------------------------------------------------------------------------------*/
void RenderScene(void)
{

	if (camera_mode1 == false)
	{
		cam.view1(radius, rotateAngle, upAngle);
	}
	if (camera_mode1 == true)
	{
		cam.view2();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);


	glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT);
	glDepthMask(GL_TRUE);
	glEnable(GL_TEXTURE_2D);




	//diaoyong
	draw_universe(-1000 * p + cam.eye.x, -1000 * p + cam.eye.y, -1000 * p + cam.eye.z, 3000.0f * p, 3000.0f * p, 3000.0f * p);
	if (skyMode == 0)
	{
		draw_skybox();
		draw_earth();
	}
	draw_sun();
	if (skyMode == 2)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	draw_moon();
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_mars();
	draw_mars_sky();
	draw_dormitory();
	draw_greenGrand();
	draw_buildings();







	glBindTexture(GL_TEXTURE_2D, 0);
	glPopAttrib();
	glutPostWindowRedisplay(mainWindow);
	glutSwapBuffers();
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, fAspect, 1.0, 40000 * p);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()//opengl��ʼ��
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // ����֧��˫�ػ������Ȳ���
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(1600, 900);
	mainWindow = glutCreateWindow("�ưܵ�����");
	glewExperimental = GL_TRUE;
	glewInit();


	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	add_textures();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);



	glutDisplayFunc(RenderScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(ChangeSize);
	glEnable(GL_DEPTH_TEST);
}
/*----------------------------------------------------------------��ʼ�����---------------------------------------------------------------------------------------*/

//����
void printHelp() {
	string words = "��ӭ�����ưܵ����棬������Ҫ������� ������ʿ �ؽ���ļ�԰ \n ��Ϸ�淨��WSADǰ������\n QE�����½�\n R����\n TAB �л�����\n M�л�ģʽ 1.����ϵ�ģʽ 2.����ģʽ\n C ���������ӵĽ���\n K �л����ģʽ\n P�л�����ģʽ \n Z ��������";
	cout << words << endl;

}

//������
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init();
	printHelp();
	glutMainLoop();
	return 0;
}

















