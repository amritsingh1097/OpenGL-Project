#ifndef CONCENTRICELLIPSES_H
#define CONCENTRICELLIPSES_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
#include "ellipse.h"
using namespace std;

class ConcentricEllipses : public Object
{
	int shapeID;
	int numEllipses;
	public:
		list< pair<int, int> > startCoords, endCoords;
		list< MidPoint_Ellipse* > ellipses;
		ConcentricEllipses(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int X1, int Y1, int X2, int Y2);
		void slopeLT1(int X1, int Y1, int X2, int Y2, int steps, int x, int y, int dx, int dy);
		void slopeGT1(int X1, int Y1, int X2, int Y2, int steps, int x, int y, int dx, int dy);
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
		void fourFloodFill(int x, int y, unsigned char* fillColor);
		void eightFloodFill(int x, int y, unsigned char* fillColor);
};

#endif
