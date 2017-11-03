#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"
#include <bits/stdc++.h>
#include <conio.h>
#include <gl/glut.h>
using namespace std;

class MidPoint_Circle : public Object
{
	public:
		int centerX, centerY, radius;
		MidPoint_Circle(unsigned char* color, int thickness, string pattern);
		void printCoords();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void swapPoints(int centerX, int centerY, int quad1_X, int quad1_Y);
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
