#include <math.h>
#include "bresenhamlda.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

BresenhamLDA::BresenhamLDA(unsigned char* color, int thickness, string pattern)
{
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->objectName = (char*)"Bresenham Line";
}

void BresenhamLDA::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

void BresenhamLDA::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	pair<int, int> currCoords;
	int dx, dy;
	int x, y, steps;
	
	x = XCoord1;
	y = YCoord1;
	dx = fabs(XCoord2 - XCoord1);
	dy = fabs(YCoord2 - YCoord1);
	
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	
	currCoords.first = x;
	currCoords.second = y;
	Coords.push_back(currCoords);
	
	if(fabs(dx) > fabs(dy))
	{
		slopeLT1(XCoord1, YCoord1, XCoord2, YCoord2, steps, x, y, dx, dy);
	}
	else
	{
		slopeGT1(XCoord1, YCoord1, XCoord2, YCoord2, steps, x, y, dx, dy);
	}
	glEnd();
	glFlush();
}

void BresenhamLDA::slopeLT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy)
{
	pair<int, int> currCoords;
	float prevDescParam, currDescParam;
	
	prevDescParam = (2 * dy) - dx;
	
	for (int i = 0; i < steps; i++)
	{
		if(XCoord2 > XCoord1)
		{
			x++;
		}
		else if(XCoord2 < XCoord1)
		{
			x--;
		}
		
		if (prevDescParam < 0)
		{
			currDescParam = prevDescParam + (2 * dy);
			prevDescParam = currDescParam;
		}
		else
		{
			if(YCoord2 > YCoord1)
			{
				y++;
			}
			else if(YCoord2 < YCoord1)
			{
				y--;
			}
			currDescParam = prevDescParam + (2 * dy) - (2 * dx);
			prevDescParam = currDescParam;
		}
		prevDescParam = currDescParam;
		
		patternIndex = patternIndex % 4;
		
		currCoords.first = x;
		currCoords.second = y;
		Coords.push_back(currCoords);
		
		if(pattern[patternIndex] == '1')
		{
			glVertex2i(x, y);
//			cout << "(X,Y): (" << x << "," << y << ")" << endl;
			
//			erasePreviousLine(x, y);
//			drawNewLine(x, y, LineColor.Red, LineColor.Green, LineColor.Blue);
		}
//		else
//		{
//			erasePreviousLine(x, y);
//			drawNewLine(x, y, BackgroundColor.Red, BackgroundColor.Green, BackgroundColor.Blue);
//		}
		
		patternIndex++;
	}
}

void BresenhamLDA::slopeGT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy)
{
	pair<int, int> currCoords;
	float prevDescParam, currDescParam;
	
	prevDescParam = (2 * dx) - dy;
	
	for (int i = 0; i < steps; i++)
	{
		if(YCoord2 > YCoord1)
		{
			y++;
		}
		else if(YCoord2 < YCoord1)
		{
			y--;
		}
		
		if (prevDescParam < 0)
		{
			currDescParam = prevDescParam + (2 * dx);
			prevDescParam = currDescParam;
		}
		else
		{
			if(XCoord2 > XCoord1)
			{
				x++;
			}
			else if(XCoord2 < XCoord1)
			{
				x--;
			}
			currDescParam = prevDescParam + (2 * dx) - (2 * dy);
			prevDescParam = currDescParam;
		}
		prevDescParam = currDescParam;
		
		patternIndex = patternIndex % 4;
		
		currCoords.first = x;
		currCoords.second = y;
		Coords.push_back(currCoords);
		
		if(pattern[patternIndex] == '1')
		{
			glVertex2i(x, y);
//			cout << "(X,Y): (" << x << "," << y << ")" << endl;
			
//			erasePreviousLine(x, y);
//			drawNewLine(x, y, LineColor.Red, LineColor.Green, LineColor.Blue);
		}
//		else
//		{
//			erasePreviousLine(x, y);
//			drawNewLine(x, y, BackgroundColor.Red, BackgroundColor.Green, BackgroundColor.Blue);
//		}
		
		patternIndex++;
	}
}

bool BresenhamLDA::selectObject(pair<int, int> clickedCoords)
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

void BresenhamLDA::translate(int dx, int dy)
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

void BresenhamLDA::rotate(int rotAngle, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
//	const float PI = 
}

void BresenhamLDA::scale(int scaleX, int scaleY, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void BresenhamLDA::setPattern(string pattern)
{
	this->pattern = pattern;
}

void BresenhamLDA::setThickness(int thickness)
{
	this->thickness = thickness;
}

void BresenhamLDA::setColor(unsigned char *color)
{
	this->color = color;
}

void BresenhamLDA::erasePreviousObject()
{
	list< pair<int, int> >::iterator it;
	glColor3ubv(Color::BACKGROUND_COLOR);
	
	glPointSize(3);
	glBegin(GL_POINTS);
	
	it = Coords.begin();
	
		glVertex2i((*it).first, (*it).second);
	
	it = Coords.end();
	it--;
	
		glVertex2i((*it).first, (*it).second);
	glEnd();
	glPointSize(1);
	
	glBegin(GL_POINTS);
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		glVertex2i((*it).first, (*it).second);
	}
	glEnd();
	glFlush();
}

void BresenhamLDA::redrawSelectedObject(unsigned char* color, int thickness)
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
