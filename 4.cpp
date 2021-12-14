#include<gl/glut.h>

void dCP(int xc, int yc, int x, int y) {
	//glColor3f(1, 0, 0);
	//glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + x, yc - y);

	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc - y, yc - x);
	glVertex2i(xc + y, yc - x);

	glEnd();
	glFlush();
}

void midPC(int xc, int yc, int r) {
	int d = 1 - r, x = 0, y = r;
	while (y >= x) {
		dCP(xc, yc, x, y);
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 6;
			y--;
		}
		x++;
	}
}
void drawC() {
	int xc = 200, yc = 200, r = 50, n = 50;
	for (int i = 0; i < n; i += 3)
		midPC(xc, yc + i, r);
}

void dR(int x1, int yc1, int x2, int y2) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, yc1);
	glVertex2i(x2, yc1);
	glVertex2i(x2, y2);
	glVertex2i(x1, y2);
	glEnd();
}
void drawP() {
	int x1 = 100, yc1 = 100, x2 = 300, y2 = 170;
	for (int i = 0; i < 50; i += 2)
		dR(x1 + i, yc1 + i, x2 + i, y2 + i);
}

void dispC() {
	glColor3f(1, 0, 0);
	drawC();
	glFlush();
}

void dispP() {
	glColor3f(0, 1, 0);
	drawP();
	glFlush();
}
void init() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	int c = glutCreateWindow("cylinder");
	glutSetWindow(c);
	glutDisplayFunc(dispC);
	init();


	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 0);
	int p = glutCreateWindow("parallelopiped");
	glutSetWindow(p);
	glutDisplayFunc(dispP);
	init();

	glutMainLoop();

	return 0;

}