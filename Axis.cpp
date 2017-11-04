#include <gl/glut.h>
#include "axis.h"
#include "color.h"

extern int ScreenSizeX, ScreenSizeY;

void Axis::drawAxis()
{
	glColor3ubv(Color::GREEN);
	
	glPointSize(7);
	glBegin(GL_POINTS);
		glVertex2i(0, 0);
	glEnd();
	glFlush();
	glPointSize(1);
	
	glBegin(GL_POINTS);
		for(int x = -ScreenSizeX/2; x <= ScreenSizeX/2; x++)
		{
			glVertex2i(x, 0);
		}
		for(int y = -ScreenSizeY/2; y <= ScreenSizeY/2; y++)
		{
			glVertex2i(0, y);
		}
	glEnd();
	glFlush();
}
