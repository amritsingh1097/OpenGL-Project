#include "viewport.h"
#include "color.h"
using namespace std;

extern int ScreenSizeX, ScreenSizeY;

Viewport::Viewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	setViewport(XCoord1, YCoord1, XCoord2, YCoord2);
//	this->XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
//	this->YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
//	this->XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
//	this->YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
}

void Viewport::printCoords()
{
//	cout << "XMIN: " << XMin << "\tYMIN: " << YMin << "\tXMAX: " << XMax << "\tYMAX: " << YMax << endl;
}

void Viewport::setViewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	this->XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
	this->YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
	this->XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
	this->YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
}

void Viewport::drawViewport(/*int XCoord1, int YCoord1, int XCoord2, int YCoord2*/)
{
//	XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
//	YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
//	XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
//	YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
	
	glColor3ubv(Color::VIEWPORT_COLOR);
	glBegin(GL_LINES);
		glVertex2i(XMin, YMin);
		glVertex2i(XMax, YMin);
		glVertex2i(XMin, YMin);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMin);
		glVertex2i(XMax, YMax);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMax);
	glEnd();
	glFlush();
}

void Viewport::removeViewport()
{
	
	XMin = -ScreenSizeX/2;
	YMin = -ScreenSizeY/2;
	XMax = ScreenSizeX/2;
	YMax = ScreenSizeY/2;
	
	glColor3ubv(Color::VIEWPORT_COLOR);
	glBegin(GL_LINES);
		glVertex2i(XMin, YMin);
		glVertex2i(XMax, YMin);
		glVertex2i(XMin, YMin);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMin);
		glVertex2i(XMax, YMax);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMax);
	glEnd();
	glFlush();
}

bool Viewport::isClipped(int XCoord, int YCoord)
{
//	cout << "XMIN: " << XMin << "\tYMIN: " << YMin << "\tXMAX: " << XMax << "\tYMAX: " << YMax << endl;
	if((XCoord > XMin && XCoord < XMax) && (YCoord > YMin && YCoord < YMax))	return false;
	return true;
}

// Line Clipping Code Goes Here...
void Viewport::clipPoints(int* XCoord1, int* YCoord1, int* XCoord2, int* YCoord2)
{
	
}
