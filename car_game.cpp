#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10
#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

int rotCar = 0;
int rotObj = 0;

bool pauseMotion = false;
bool objVisible = false;
bool objCollision = false;

float obj[4] = { 13, 2, 0 };
float car[4] = { 13, 2, 0 };

float d2r(int degree) { return ((PI / 180.0) * degree); } //degree to radians

void writeBitmapString(void *font, char *string) {
	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}
void drawAxis(float size) {
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);
	glEnd();

	glRasterPos3f(size, 0, 0.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+X");

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, -size, 0);
	glVertex3f(0, size, 0);
	glEnd();

	glRasterPos3f(0, size, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Y");

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);
	glEnd();

	glRasterPos3f(0, 0, size);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Z");
}

void drawDisc(float R, float X, float Y, float Z, bool dash) {

	if (dash) glBegin(GL_LINES);
	else glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= N; ++i) {
		float t = 2 * PI * i / N;
		glVertex3f(X + cos(t) * R, Y, Z + sin(t) * R);
	}
	glEnd();
}
void drawRandomObjects() {
	int p = 17;
	glPushMatrix();
	glScalef(1, 3, 1);
	glPushMatrix();
	glTranslatef(p, 1, 0);
	glColor3f(0, 0, 0); glutWireCube(2);
	glColor3f(0, 1, 0); glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-p, 1, 0);
	glColor3f(0, 0, 0); glutWireCube(2);
	glColor3f(0, 0, 1); glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 1, -p);
	glColor3f(0, 0, 0); glutWireCube(2);
	glColor3f(0, 1, 1); glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 1, p);
	glColor3f(0, 0, 0); glutWireCube(2);
	glColor3f(1, 0, 0); glutSolidCube(2);
	glPopMatrix();
	glPopMatrix();
}
void drawCar(float x, float y, float z, int angle) {

	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	glTranslatef(car[0], 0, car[2]);
	glPushMatrix();
	glTranslatef(0, car[1] / 2, -2);
	glScalef(2, 1, 1);
	glColor3f(0, 0, 0); glutWireCube(2);
	glColor3f(1, 0, 1); glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, car[1], 1);
	glColor3f(0, 0, 0); glutWireCube(4);
	glColor3f(1, 0, 1); glutSolidCube(4);
	glPopMatrix();
	glPopMatrix();
}
void drawRoad() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	drawDisc(10, 0, 0, 0, false);
	drawDisc(16, 0, 0, 0, false);
	drawDisc(13, 0, 0, 0, true);
	glPopMatrix();
}

void drawObstacle(float x, float y, float z, int angle) {
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	glTranslatef(x, y, z);
	glColor3f(0, 0, 0); glutWireCube(3);
	glColor3f(0.5, 0.5, 0.5); glutSolidCube(3);
	glPopMatrix();
}

// Drawing routine.
void drawScene(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//------------------------------------------------
	glViewport(0, 0, 500, 500);
	glLoadIdentity();
	gluLookAt(10, 15, 25, 0, 0, 0, 0, 1, 0);

	//------------------------------------------------
	drawAxis(20);
	drawRoad();
	drawRandomObjects();

	drawCar(car[0], car[1], car[2], rotCar);

	if (objVisible)
		drawObstacle(obj[0], obj[1], obj[2], rotObj);

	//------------------------------------------------
	if (objCollision) {
		glViewport(150, 200, 200, 100);

		glScissor(150, 200, 200, 100);
		glEnable(GL_SCISSOR_TEST);
		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-20, 20, -10, 10, -1, 5);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(1, 1, 1); glRasterPos3f(-15, 0, 0);
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Collusion!");
		glRasterPos3f(-15, -5, 0);
		writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Try again! Press 'O'");

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	//-------------------------------------------------
	glDisable(GL_DEPTH_TEST);
	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		pauseMotion = (pauseMotion + 1) % 2;
		break;
	case 'o':
		objVisible = (objVisible + 1) % 2;
		rotObj = (rand() % 360);
		objCollision = false;
		pauseMotion = false;
		break;
	default:
		break;
	}
}

bool checkCollision() {
	float cx = car[0] * cos(d2r(rotCar)) + car[2] * sin(d2r(rotCar));
	float cy = car[1];
	float cz = -car[0] * sin(d2r(rotCar)) + car[2] * cos(d2r(rotCar));

	float ox = obj[0] * cos(d2r(rotObj)) + obj[2] * sin(d2r(rotObj));
	float oy = obj[1];
	float oz = -obj[0] * sin(d2r(rotObj)) + obj[2] * cos(d2r(rotObj));

	float r = 5;
	float distSq = ((cx - ox)*(cx - ox)) + ((cy - oy)*(cy - oy)) + ((cz - oz)*(cz - oz));

	if (r*r > distSq)
		return true;
	else
		return false;
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value) {

	if (!pauseMotion)
		rotCar = (rotCar + 1) % 360;

	if (objVisible)
		objCollision = checkCollision();

	if (objCollision)
		pauseMotion = true;

	glutPostRedisplay();
	glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv) {
	srand(time(0));

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modelview Transformation Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

	glewExperimental = GL_TRUE;
	glewInit();

	glutMainLoop();
}