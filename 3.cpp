#include<gl/glut.h>
#include<iostream>
int sb, db;
float x, y, spin = 0.0;
float degToRad = 3.14159 / 180.0;
void spindisplay() {
	spin += 0.025;
	if (spin > 360) spin -= 360;
	x = cos(degToRad * spin);
	y = sin(degToRad * spin);
	glutSetWindow(db);
	glutPostRedisplay();
}
void square() {
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	glVertex2f(x, y);

	glColor3f(0, 1, 0);
	glVertex2f(-y, x);

	glColor3f(0, 0, 1);
	glVertex2f(-x, -y);

	glColor3f(1, 0, 1);
	glVertex2f(y, -x);

	glEnd();
}

void mouse(int btn, int st, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
		glutIdleFunc(spindisplay);
	if (btn == GLUT_RIGHT_BUTTON && st == GLUT_DOWN)
		glutIdleFunc(NULL);
}

void disp() {
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glFlush();
}

void dispD() {
	glClear(GL_COLOR_BUFFER_BIT);
	square();
	glutSwapBuffers();
}
void init() {
	glClearColor(1, 1, 1, 1);
	glColor3i(1, 0, 0);
	gluOrtho2D(-2, 2, -2, 2);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-2.0, 2.0, -2.0 * (float)h / (float)w, 2 * (float)h / (float)w);
	else
		gluOrtho2D(-2.0 * (float)w / (float)h, 2 * (float)w / (float)h, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	sb = glutCreateWindow("single buffer");
	glutDisplayFunc(disp);
	glutReshapeFunc(reshape);
	init();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	db = glutCreateWindow("double");
	init();
	glutDisplayFunc(dispD);
	glutMouseFunc(mouse);
	glutIdleFunc(spindisplay);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}