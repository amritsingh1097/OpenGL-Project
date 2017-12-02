#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class Object
{
	public:
		int shapeID;
		char* objectName;
		list< pair<int, int> > Coords;
		unsigned char *color;
		string pattern;
		int thickness;
		int patternIndex;
		bool isFilled;
		unsigned char* fillColor;
		
		// Functions
		virtual void printCoords() = 0;
		virtual int getShapeID() = 0;
		virtual void draw(int X1, int Y1, int X2, int Y2) = 0;
		virtual bool selectObject(pair<int, int> clickedCoords) = 0;
		virtual void translate(int dx, int dy) = 0;
		virtual void rotate(int rotAngle, pair<int, int> pivot) = 0;
		virtual void scale(float scaleFactor, pair<int, int> pivot) = 0;
		virtual void setPattern(string pattern) = 0;
		virtual void setThickness(int thickness) = 0;
		virtual void setColor(unsigned char* color) = 0;
		virtual void erasePreviousObject() = 0;
		virtual void redrawSelectedObject(unsigned char* color, int thickness) = 0;
		virtual void setFillColor(unsigned char *fillColor) {}
		virtual void fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor) {}
		virtual void eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor) {}
		virtual void fourFloodFill(int x, int y, unsigned char* fillColor) {}
		virtual void eightFloodFill(int x, int y, unsigned char* fillColor) {}
};

#endif
