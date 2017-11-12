<<<<<<< HEAD
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class Viewport
{
	public:
		int XMin, YMin, XMax, YMax;
		bool ViewportPresent;
		Viewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void printCoords();
		void setViewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void drawViewport(/*int XCoord1, int YCoord1, int XCoord2, int YCoord2*/);
		void removeViewport();
		bool isClipped(int XCoord, int YCoord);
		bool clipLine(pair<int, int>* start, pair<int, int>* end);
//		void clipLine(int* XCoord1, int* YCoord1, int* XCoord2, int* YCoord2);
};

#endif
=======
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "object.h"
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

class Viewport
{
	public:
		int XMin, YMin, XMax, YMax;
		bool ViewportPresent;
		Viewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void printCoords();
		void setViewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2);
		void drawViewport(/*int XCoord1, int YCoord1, int XCoord2, int YCoord2*/);
		void removeViewport();
		bool isClipped(int XCoord, int YCoord);
		bool clipLine(pair<int, int>* start, pair<int, int>* end);
//		void clipLine(int* XCoord1, int* YCoord1, int* XCoord2, int* YCoord2);
};

#endif
>>>>>>> 39796d7880b44149153aa64f8eadc9dcf0d63da9
