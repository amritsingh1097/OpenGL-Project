#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class MidPoint_Ellipse : public Object
{
	public:
		int centerX, centerY, radiusX, radiusY;
		MidPoint_Ellipse(unsigned char* color, int thickness, string pattern);
		void printCoords();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void horizontalEllipse();
		void verticalEllipse();
		bool selectObject(pair<int, int> clickedCoords);
		void translate(int dx, int dy);
		void rotate(int rotAngle, pair<int, int> pivot);
		void scale(int scaleX, int scaleY, pair<int, int> pivot);
		void setPattern(string pattern);
		void setThickness(int thickness);
		void setColor(unsigned char* color);
		void erasePreviousObject();
		void redrawSelectedObject(unsigned char* color, int thickness);
//		void fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void fillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor);
};

#endif
