#include<gl/glut.h>
#include<iostream>
int xc, yc, x, y, r, flag;

void dispCP(int xc, int yc, int x, int y) {
	glColor3i(1, 0, 0);
	glPointSize(3);
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

void bresC() {
	int px = 0, py = r;
	int d = 3 - 2 * r;
	while (py >= px) {
		dispCP(xc, yc, px, py);
		if (d < 0)
			d += 4 * py + 6;
		else {
			y--;
			d += 4 * (py - px) + 10;
		}
	}
}

void mouse(int btn, int st, int mx, int my) {
	if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
		if (flag == 0) {
			xc = mx - 250;
			yc = 250 - my;
			flag++;
		}
		else {
			x = mx - 250;
			y = 250 - my;
			int r2 =  (xc - x) * (xc - x) + (yc - y) * (yc - y);
			r = sqrt(r2);
			flag = 0;
			bresC();
		}
	}
}

void display() {}


void init() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}


int main(int argc, char* argv[]) {
	int ch;
	cout << "Enter the choice :";
	cin >> ch;
	if (ch == 1) 
		cin >> xc >> yc >> r;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circle");
	if (ch == 1) 
		glutDisplayFunc(bresC);
	else {
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	}
	init();
	glutMainLoop();
	return 0;
}