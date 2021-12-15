#include<gl/glut.h>
#include<iostream>
using namespace std;
int angle;
float m, c;
int h[11][2] = { {100,200},{200,250},{300,200},{100,200},{100,100},{175,100},{175,150},{225,150},{225,100},{300,100},{300,200} };
void init() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, -500, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void dH() {
	glBegin(GL_LINE_LOOP);
	for (int i = 0;i < 11;i++)
		glVertex2iv(h[i]);
	glEnd();
}
void display() {
	init();
	glColor3f(1, 0, 0);
	dH();

	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-100, -100, 0);

	glColor3f(1, 1, 0);
	dH();
	glPopMatrix();
	glFlush();
}

void reflect() {
	init();
	glColor3f(1, 0, 0);
	dH();

	float x1 = 0, x2 = 500;
	float yc1 = m * x1 + c, y2 = m * x2 + c;
	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, yc1);
	glVertex2f(x2, y2);
	glEnd();

	glPushMatrix();
	glTranslatef(0, -c, 0);
	float theta = atan(m);
	theta *= 180.0 / 3.14159;
	glRotatef(theta, 0, 0, 1);
	glScalef(1, -1, 1);
	glRotatef(-theta, 0, 0, 1);
	glTranslatef(0, c, 0);
	glColor3f(1, 1, 0);
	dH();
	glPopMatrix();
	glFlush();
}
void mouse(int btn, int st, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
		display();
	if (btn == GLUT_RIGHT_BUTTON && st == GLUT_DOWN)
		reflect();
}
int main(int argc, char* argv[]) {
	cout << "Enter the angle in deg:";
	cin >> angle;
	cout << "Enter the m and c";
	cin >> m >> c;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("house");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
}