#include<gl/glut.h>
#include<math.h>

void sphere() {
	double c = 3.14159 / 180.0, x, y, z;

	for (double phi = -80;phi <= 80;phi += 10) {
		double phir = c * phi, phir10 = c * (phi + 10);
		glBegin(GL_QUAD_STRIP);
		for (double theta = -180;theta <= 180;theta += 10) {
			double thetar = c * theta;
			x = sin(thetar) * cos(phir);
			y = cos(thetar) * cos(phir);
			z = sin(phir);
			glVertex3d(x, y, z);
			x = sin(thetar) * cos(phir10);
			y = cos(thetar) * cos(phir10);
			z = sin(phir10);
			glVertex3d(x, y, z);
		}
		glEnd();
	}


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 1.0);
	z = sin(80 * c);
	for (double theta = -180;theta <= 180;theta += 10) {
		double thetar = c * theta;
		x = sin(thetar) * cos(80 * c);
		y = cos(thetar) * cos(80 * c);
		glVertex3d(x, y, z);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, -1.0);
	z = sin(-80 * c);
	for (double theta = -180;theta <= 180;theta += 10) {
		double thetar = c * theta;
		x = sin(thetar) * cos(-80 * c);
		y = cos(thetar) * cos(-80 * c);
		glVertex3d(x, y, z);
	}
	glEnd();


}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -1);
	glRotatef(60.0, 1.0, 1.0, 0.0);

	sphere();

	glFlush();
}
void init() {
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sphere Display");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	init();
	glutMainLoop();
}