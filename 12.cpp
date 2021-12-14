#include<gl/glut.h>
float ver[8][3] = { {0,0,0},{1,0,0},{1,1,0},{0,1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1} };
float theta[3] = { 0,0,0 };
int axis = 0;

void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
	glColor3fv(ver[a]);
	glVertex3fv(ver[a]);
	glColor3fv(ver[b]);
	glVertex3fv(ver[b]);
	glColor3fv(ver[c]);
	glVertex3fv(ver[c]);
	glColor3fv(ver[d]);
	glVertex3fv(ver[d]);
	glEnd();
}
void Colorcube() {
	polygon(0, 3, 2, 1);
	polygon(1, 2, 6, 5);
	polygon(5, 6, 7, 4);
	polygon(4, 7, 3, 0);
	polygon(0, 1, 5, 4);
	polygon(3, 2, 6, 7);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	Colorcube();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * h / w, 2 * h / w, -10, 10);
	else
		glOrtho(-2 * h / w, 2 * h / w, -2, 2, -10, 10);

	glMatrixMode(GL_MODELVIEW);
}

void spin() {
	theta[axis] += 0.005;
	if (theta[axis] > 360)
		theta[axis] -= 360;
	display();
}
void mouse(int btn, int st, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && st == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && st == GLUT_DOWN)
		axis = 2;
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(spin);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}