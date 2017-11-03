#include <math.h>
#include "symmetricdda.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

SymmetricDDA::SymmetricDDA(unsigned char* color, int thickness, string pattern)
{
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->objectName = (char*)"Symmetric DDA Line";
}

void SymmetricDDA::printCoords()
{
	list< pair<int, int> >::iterator it;
	
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		cout << "Coordinates: (" << (*it).first << ", " << (*it).second << ")" << endl;
	}
	
}

void SymmetricDDA::draw(int X1, int Y1, int X2, int Y2)
{
	float x, y;
	float dx, dy, xIncr, yIncr;
	int LLE, max, power;
	
	pair<int, int> currCoords;

	x = X1 + 0.5;
	y = Y1 + 0.5;
	dx = X2 - X1;
	dy = Y2 - Y1;
//	max = maximum(fabs(dx), fabs(dy));
	max = dx > dy ? dx : dy;

	cout << "X: " << x << "\t";
	cout << "Y: " << y << endl << endl;

	for (int i = 0; i < max; i++)
	{
		if (max >= pow(2, i-1) && max < pow(2, i))
		{
			power = i;
		}
	}
	
	LLE = pow(2, power);

	cout << "LLE: " << LLE << endl << endl;

	xIncr = float(dx) / float(LLE);
	yIncr = float(dy) / float(LLE);

	cout << "X Incr: " << xIncr << "\t";
	cout << "Y Incr: " << yIncr << endl << endl;

	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	glVertex2i(round(x), round(y));

	currCoords.first = round(x);
	currCoords.second = round(y);
	Coords.push_back(currCoords);

	for (int i=0; i<LLE; i++)
	{
		x += xIncr;
		y += yIncr;
		
		currCoords.first = round(x);
		currCoords.second = round(y);
		Coords.push_back(currCoords);
		
		patternIndex = patternIndex % 4;
		
		if(pattern[patternIndex] == '1')
		{
			glVertex2i(round(x), round(y));
//			cout << "(X,Y): (" << round(x) << "," << round(y) << ")" << endl;
			
//			erasePreviousLine(round(x), round(y));
//			drawNewLine(round(x), round(y), LineColor.Red, LineColor.Green, LineColor.Blue);
		}
//		else
//		{
//			erasePreviousLine(round(x), round(y));
//			drawNewLine(round(x), round(y), BackgroundColor.Red, BackgroundColor.Green, BackgroundColor.Blue);
//		}
		
		patternIndex++;
	}
	
	glEnd();
	glFlush();
//	LastThickness = LineThickness;
}

bool SymmetricDDA::selectObject(pair<int, int> clickedCoords)
{
	list< pair<int, int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		if((*it).first == clickedCoords.first && (*it).second == clickedCoords.second)
		{
			redrawSelectedObject(Color::RED, thickness);
			return true;
		}
	}
	return false;
}

void SymmetricDDA::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
	redrawAllObjects();
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
}

void SymmetricDDA::rotate(int rotAngle, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void SymmetricDDA::scale(int scaleX, int scaleY, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void SymmetricDDA::setPattern(string pattern)
{
	this->pattern = pattern;
}

void SymmetricDDA::setThickness(int thickness)
{
	this->thickness = thickness;
}

void SymmetricDDA::setColor(unsigned char *color)
{
	this->color = color;
}

void SymmetricDDA::erasePreviousObject()
{
	list< pair<int, int> >::iterator it;
	
	glColor3ubv(Color::BACKGROUND_COLOR);
	glBegin(GL_POINTS);
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		glVertex2i((*it).first, (*it).second);
	}
	glEnd();
	glFlush();
}

void SymmetricDDA::redrawSelectedObject(unsigned char* color, int thickness)
{
	glColor3ubv(color);
	glPointSize(thickness);
	
	list< pair<int, int> >::iterator it;
	glBegin(GL_POINTS);
		for(it = Coords.begin(); it != Coords.end(); it++)
		{
			patternIndex %= 4;
			if(pattern[patternIndex] == '1')
			{
				glVertex2i((*it).first, (*it).second);
			}
			patternIndex++;
		}
	glEnd();
	glFlush();
}
