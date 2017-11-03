#ifndef OBJECT_H
#define OBJECT_H

#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class Object
{
	public:
		char* objectName;
		list< pair<int, int> > Coords;
		unsigned char *color;
		string pattern;
		int thickness;
		int patternIndex;
		
		// Functions
		virtual void printCoords() = 0;
		virtual void draw(int X1, int Y1, int X2, int Y2) = 0;
		virtual bool selectObject(pair<int, int> clickedCoords) = 0;
		virtual void translate(int dx, int dy) = 0;
		virtual void rotate(int rotAngle, pair<int, int> pivot) = 0;
		virtual void scale(int scaleX, int scaleY, pair<int, int> pivot) = 0;
		virtual void setPattern(string pattern) = 0;
		virtual void setThickness(int thickness) = 0;
		virtual void setColor(unsigned char* color) = 0;
		virtual void erasePreviousObject() = 0;
		virtual void redrawSelectedObject(unsigned char* color, int thickness) = 0;
//		virtual void fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor) {}
		virtual void fillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor) {}
};

#endif
