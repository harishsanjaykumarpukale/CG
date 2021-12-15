#include<gl/glut.h>
#include<iostream>

double xmin, ymin, xmax, ymax;
double xvmin, yvmin, xvmax, yvmax, n;

struct ls { double x1, y1, x2, y2; };
struct ls ls[10];

bool clipTest(double p, double q, double& u1, double& u2) {
	double r;
	if (p) r = q / p;

	if (p == 0) {
		if (q < 0)
			return false;
	}
	else if (p < 0) {
		if (r > u1) u1 = r;
		if (r > u2) return false;
	}
	else {
		if (r < u1) return false;
		if (r < u2) u2 = r;
	}
	return true;
}

void LineClip(double x1, double y1, double x2, double y2) {
	double dx = x2 - x1, dy = y2 - y1, u1 = 0.0, u2 = 1.0;
	if (clipTest(-dx, x1 - xmin, u1, u2))
		if (clipTest(dx, xmax - x1, u1, u2))
			if (clipTest(-dy, y1 - ymin, u1, u2))
				if (clipTest(dy, ymax - y1, u1, u2)) {
					if (u1 > 0) {
						x1 += u1 * dx;
						y1 += u1 * dy;
					}
					if (u2 < 0) {
						x2 += u2 * dx;
						y2 += u2 * dy;
					}
					double sx = (xvmax - xvmin) / (xmax - xmin); // Scale parameters
					double sy = (yvmax - yvmin) / (ymax - ymin);
					double vx0 = xvmin + (x1 - xmin) * sx;
					double vy0 = yvmin + (y1 - ymin) * sy;
					double vx1 = xvmin + (x2 - xmin) * sx;
					double vy1 = yvmin + (y2 - ymin) * sy;
					glColor3f(0.0, 0.0, 1.0); // draw blue colored clipped line
					glBegin(GL_LINES);
					glVertex2d(vx0, vy0);
					glVertex2d(vx1, vy1);
					glEnd();
				}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(ls[i].x1, ls[i].y1);
		glVertex2d(ls[i].x2, ls[i].y2);
		glEnd();
	}


	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(xmin, ymin);
	glVertex2d(xmax, ymin);
	glVertex2d(xmax, ymax);
	glVertex2d(xmin, ymax);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(xvmin, yvmin);
	glVertex2d(xvmax, yvmin);
	glVertex2d(xvmax, yvmax);
	glVertex2d(xvmin, yvmax);
	glEnd();

	for (int i = 0;i < n;i++)
		LineClip(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);
	glFlush();//makes difference
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	printf("Enter window coordinates: (xmin ymin xmax ymax) \n");
	scanf_s("%lf%lf%lf%lf", &xmin, &ymin, &xmax, &ymax);
	printf("Enter viewport coordinates: (xvmin yvmin xvmax yvmax) \n");
	scanf_s("%lf%lf%lf%lf", &xvmin, &yvmin, &xvmax, &yvmax);
	printf("Enter no. of lines:\n");
	scanf_s("%lf", &n);

	for (int i = 0; i < n; i++)
	{
		printf("Enter coordinates: (x1 y1 x2 y2)\n");
		scanf_s("%lf%lf%lf%lf", &ls[i].x1, &ls[i].y1, &ls[i].x2, &ls[i].y2);
	}
	glutCreateWindow("Liang Barsky Line Clipping Algorithm");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}