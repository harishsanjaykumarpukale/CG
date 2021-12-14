#include<gl/glut.h>
#include<iostream>
using namespace std;
int cp[20][2], cps, opp[20][2], ops, pp[20][2], ps;

void dP(int p[][2], int n) {
	glBegin(GL_POLYGON);
	for (int i = 0;i < n;i++)
		glVertex2iv(p[i]);
	glEnd();
}

int xints(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x3 * y4 - y3 * x4) * (x1 - x2);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

int yints(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int num = (x1 * y2 - y1 * x2) * (y3 - y4) - (x3 * y4 - y3 * x4) * (y1 - y2);
	int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

void clip(int p[][2], int& ps, int x1, int y1, int x2, int y2) {
	int np[20][2], nps = 0;
	for (int i = 0;i < ps;i++) {
		int k = (i + 1) % ps;
		int ix = p[i][0], iy = p[i][1];
		int kx = p[k][0], ky = p[k][1];

		int iloc = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);
		int kloc = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		if (iloc >= 0 && kloc >= 0) {
			np[nps][0] = kx;
			np[nps++][1] = ky;
		}
		else if (iloc < 0 && kloc >= 0) {
			np[nps][0] = xints(x1, y1, x2, y2, ix, iy, kx, ky);
			np[nps++][1] = yints(x1, y1, x2, y2, ix, iy, kx, ky);
			np[nps][0] = kx;
			np[nps++][1] = ky;
		}
		else if (iloc >= 0 && kloc < 0) {
			np[nps][0] = xints(x1, y1, x2, y2, ix, iy, kx, ky);
			np[nps++][1] = yints(x1, y1, x2, y2, ix, iy, kx, ky);
		}
	}

	ps = nps;
	for (int i = 0;i < ps;i++) {
		pp[i][0] = np[i][0];
		pp[i][1] = np[i][1];
	}
}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, 0.0, 500.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void display() {
	init();

	glColor3f(1.0f, 0.0f, 0.0f);
	dP(cp, cps);

	glColor3f(0.0f, 1.0f, 0.0f);
	dP(opp, ops);

	for (int i = 0;i < cps;i++) {
		int k = (i + 1) % cps;
		clip(pp, ps, cp[i][0], cp[i][1], cp[k][0], cp[k][1]);
	}

	glColor3f(0.0f, 0.0f, 1.0f);
	dP(pp, ps);

	glFlush();
}
int main(int argc, char* argv[]) {
	cout << "enter the no. of vertices of clipper : ";
	cin >> cps;
	for (int i = 0;i < cps;i++)
		cin >> cp[i][0] >> cp[i][1];
	cout << "enter the polgon points";
	cin >> ps;
	ops = ps;
	for (int i = 0;i < ps;i++) {
		cin >> opp[i][0] >> opp[i][1];
		pp[i][0] = opp[i][0];
		pp[i][1] = opp[i][1];
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Polygon Clipping!");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}