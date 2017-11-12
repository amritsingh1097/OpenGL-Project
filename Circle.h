<<<<<<< HEAD
#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"
#include <bits/stdc++.h>
#include <conio.h>
#include <gl/glut.h>
using namespace std;

class MidPoint_Circle : public Object
{
	int shapeID;
	public:
		int centerX, centerY, clickedRadiusX, clickedRadiusY, radius;
//		bool isFilled;
		list< pair<int, int> > filledCoords;
		MidPoint_Circle(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void swapPoints(int centerX, int centerY, int quad1_X, int quad1_Y);
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
=======
#ifndef CIRCLE_H
#define CIRCLE_H

#include "object.h"
#include <bits/stdc++.h>
#include <conio.h>
#include <gl/glut.h>
using namespace std;

class MidPoint_Circle : public Object
{
	int shapeID;
	public:
		int centerX, centerY, clickedRadiusX, clickedRadiusY, radius;
//		bool isFilled;
		list< pair<int, int> > filledCoords;
		MidPoint_Circle(unsigned char* color, int thickness, string pattern);
		void printCoords();
		int getShapeID();
		void draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void swapPoints(int centerX, int centerY, int quad1_X, int quad1_Y);
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
		void floodFill(int x, int y, unsigned char* fillColor);
};

#endif
>>>>>>> 39796d7880b44149153aa64f8eadc9dcf0d63da9
