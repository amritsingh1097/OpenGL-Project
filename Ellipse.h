#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class MidPoint_Ellipse : public Object
{
	int shapeID;
	public:
		int endX, endY;
		int centerX, centerY, radiusX, radiusY;
		list< pair<int, int> > filledCoords;
		MidPoint_Ellipse(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void horizontalEllipse();
		void verticalEllipse();
		bool selectObject(pair<int, int> clickedCoords);
		void translate(int dx, int dy);
		void rotate(int rotAngle, pair<int, int> pivot);
		void scale(float scaleFactor, pair<int, int> pivot);
		void setPattern(string pattern);
		void setThickness(int thickness);
		void setColor(unsigned char* color);
		void setFillColor(unsigned char* fillColor);
		void erasePreviousObject();
		void redrawSelectedObject(unsigned char* color, int thickness);
//		void fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void fourFloodFill(int x, int y, unsigned char* fillColor);
		void eightFloodFill(int x, int y, unsigned char* fillColor);
};

#endif
