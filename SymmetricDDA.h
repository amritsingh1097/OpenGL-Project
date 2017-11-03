#ifndef SYMMETRICDDA_H
#define SYMMETRICDDA_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>

class SymmetricDDA : public Object
{
	public:
		SymmetricDDA(unsigned char* color, int thickness, string pattern);
		void printCoords();
		void draw(int X1, int Y1, int X2, int Y2);
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
