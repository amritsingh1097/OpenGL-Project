<<<<<<< HEAD
#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "object.h"
#include<conio.h>
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class BresenhamLDA : public Object
{
	int shapeID;
	public:
		pair<int, int> startCoords, endCoords;
		BresenhamLDA(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void slopeLT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
		void slopeGT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
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
=======
#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "object.h"
#include<conio.h>
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class BresenhamLDA : public Object
{
	int shapeID;
	public:
		pair<int, int> startCoords, endCoords;
		BresenhamLDA(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void slopeLT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
		void slopeGT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy);
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
>>>>>>> 39796d7880b44149153aa64f8eadc9dcf0d63da9
