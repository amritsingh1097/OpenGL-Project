#ifndef B_SPLINE_H
#define B_SPLINE_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class B_Spline : public Object
{
	int shapeID;
	public:
		pair<int, int> startCoords, endCoords;
		list< pair<int, int> > controlPoints;
		bool isDrawn;
		B_Spline(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int X1, int Y1, int X2, int Y2);
		void translate(int dx, int dy);
		void rotate(int rotAngle, pair<int, int> pivot);
		void scale(float scaleFactor, pair<int, int> pivot);
		void setPattern(string pattern);
		void setThickness(int thickness);
		void setColor(unsigned char* color);
		bool selectObject(pair<int, int>);
		void erasePreviousObject();
		void redrawSelectedObject(unsigned char* color, int thickness);
		void fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor);
		void floodFill(int x, int y, unsigned char* fillColor);
};

#endif

