#include<gl/glut.h>
#include<iostream>

using namespace std;

int x1, yc1, x2, y2, flag = 0;

void dP(int x, int y) {
	glColor3f(1, 0, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void dispLine() {
	int dx = x2 - x1, dy = y2 - yc1, x, y, ip;
	int incx = 1, incy = 1, inc1, inc2;

	if (dx < 0) {
		incx = -1;
		dx = -dx;
	}

	if (dy < 0) {
		incy = -1;
		dy = -dy;
	}

	if (dx == 0) {
		for (int i = yc1;i != y2;i += incy)
			dP(x1, i);
		return;
	}

	if (dy == 0) {
		for (int i = x1;i != x2;i += incx)
			dP(i, yc1);
		return;
	}
	x = x1;
	y = yc1;

	if (dx > dy) {
		dP(x, y);
		ip = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (int i = 0;i < dx;i++) {
			if (ip >= 0) {
				ip += inc1;
				y += incy;
			}
			else
				ip += inc2;
			x += incx;
			dP(x, y);
		}
	}
	else {
		dP(x1, yc1);
		ip = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;

		for (int i = 0;i < dy;i++) {
			if (ip >= 0) {
				ip += inc1;
				x += incx;
			}
			else
				ip += inc2;
			y += incy;
			dP(x, y);
		}
	}
}

void mouse(int btn, int st, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
		if (flag == 0) {
			x1 = x - 250;
			yc1 = 250 - y;
			flag++;
		}
		else {
			x2 = x - 250;
			y2 = 250 - y;
			flag = 0;
			dispLine();
		}
	}
}


void display() {}

void init() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}


int main(int argc, char* argv[]) {
	int ch;

	cout << "Enter the choice ";
	cin >> ch;

	if (ch == 1) {
		cin >> x1 >> yc1 >> x2 >> y2;
		cout << x1 << yc1 << x2 << y2;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Line");

	if (ch == 1)
		glutDisplayFunc(dispLine);
	else {
		glutMouseFunc(mouse);
		glutDisplayFunc(display);
	}

	init();
	glutMainLoop();

	return 0;
}
