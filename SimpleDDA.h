#ifndef SIMPLEDDA_H
#define SIMPLEDDA_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class SimpleDDA : public Object
{
	int shapeID;
	public:
		pair<int, int> startCoords, endCoords;
		SimpleDDA(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int X1, int Y1, int X2, int Y2);
		void slopeLT1(int LLE, int X1, int Y1, int X2, int Y2, float x, float y, float dy);
		void slopeGT1(int LLE, int X1, int Y1, int X2, int Y2, float x, float y, float dx);
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
