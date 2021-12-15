#include<gl/glut.h>
#include<iostream>
using namespace std;
int n;
typedef float point[3];
point v[4] = { {0,100,-100},{0,0,100},{100,-100,-100},{-100,-100,-100} };

void drawTriangle(point a, point b, point c) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}
void drawTetra(point v0, point v1, point v2, point v3) {
	glColor3f(1, 0, 0);
	drawTriangle(v0, v1, v2);

	glColor3f(1, 1, 0);
	drawTriangle(v1, v2, v3);

	glColor3f(0, 1, 0);
	drawTriangle(v1, v3, v0);

	glColor3f(1, 0, 1);
	drawTriangle(v0, v2, v3);
}
void divideTetra(point v0, point v1, point v2, point v3, int n) {
	point mid[6];

	if (n > 0) {
		for (int i = 0;i < 3;i++) mid[0][i] = (v0[i] + v1[i]) / 2;
		for (int i = 0;i < 3;i++) mid[1][i] = (v1[i] + v2[i]) / 2;
		for (int i = 0;i < 3;i++) mid[2][i] = (v1[i] + v3[i]) / 2;
		for (int i = 0;i < 3;i++) mid[3][i] = (v0[i] + v3[i]) / 2;
		for (int i = 0;i < 3;i++) mid[4][i] = (v0[i] + v2[i]) / 2;
		for (int i = 0;i < 3;i++) mid[5][i] = (v3[i] + v2[i]) / 2;

		divideTetra(v0, mid[0], mid[3], mid[4], n - 1);
		divideTetra(v1, mid[0], mid[1], mid[2], n - 1);
		divideTetra(v2, mid[1], mid[4], mid[5], n - 1);
		divideTetra(v3, mid[2], mid[3], mid[5], n - 1);
	}
	else
		drawTetra(v0, v1, v2, v3);
}
void tetrahedron() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divideTetra(v[0], v[1], v[2], v[3], n);
	glFlush();
}
void init() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150, 150, -150, 150, -150, 150);
}
int main(int argc, char* argv[]) {
	cout << "enter the n";
	cin >> n;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("sirepinski");
	glutDisplayFunc(tetrahedron);
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
	return 0;
}