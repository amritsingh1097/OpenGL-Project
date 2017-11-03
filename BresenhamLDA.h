#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class BresenhamLDA : public Object
{
	public:
		BresenhamLDA(unsigned char* color, int thickness, string pattern);
		void printCoords();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void slopeLT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
		void slopeGT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
		void translate(int dx, int dy);
		void rotate(int rotAngle, pair<int, int> pivot);
		void scale(int scaleX, int scaleY, pair<int, int> pivot);
		void setPattern(string pattern);
		void setThickness(int thickness);
		void setColor(unsigned char* color);
		bool selectObject(pair<int, int>);
		void erasePreviousObject();
		void redrawSelectedObject(unsigned char* color, int thickness);
};

#endif
