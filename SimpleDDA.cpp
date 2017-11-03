#include <math.h>
#include "simpledda.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

SimpleDDA::SimpleDDA(unsigned char* color, int thickness, string pattern)
{
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->objectName = (char*)"Simple DDA Line";
}

void SimpleDDA::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

void SimpleDDA::draw(int X1, int Y1, int X2, int Y2)
{
	float dx, dy;
	float x, y;
	int LLE;
	
	pair<int, int> currCoords;

//	cout << "X1: " << XCoord1 << "\tY1: " << YCoord1 << "\tX2: " << XCoord2 << "\tY2: " << YCoord2 << endl;
	x = X1;
	y = Y1;
	dx = X2 - X1;
	dy = Y2 - Y1;
	
	LLE = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
//	LLE = maximum(fabs(dx), fabs(dy));
//	cout << "LLE: " << LLE << endl << endl;
//	cout << "(X,Y): (" << x << "," << y << ")" << endl;

	currCoords.first = x;
	currCoords.second = y;
	Coords.push_back(currCoords);
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	glVertex2i(x, y);

	if(fabs(dx) > fabs(dy))
	{
		slopeLT1(LLE, X1, Y1, X2, Y2, x, y, dy);
	}
	else
	{
		slopeGT1(LLE, X1, Y1, X2, Y2, x, y, dx);
	}
	
	glEnd();
	glFlush();
}

void SimpleDDA::slopeLT1(int LLE, int X1, int Y1, int X2, int Y2, float x, float y, float dy)
{
	float yIncr;
	
	pair<int, int> currCoords;
	
	yIncr = fabs(float(dy) / float(LLE));
	
	for (int i=0; i<LLE; i++)
	{
		if (X2 > X1)
		{
			x++;
		}
		else if (X2 < X1)
		{
			x--;
		}

		if (Y2 > Y1)
		{
			y += yIncr;
		}
		else if (Y2 < Y1)
		{
			y -= yIncr;
		}
		
		currCoords.first = x;
		currCoords.second = round(y);
		Coords.push_back(currCoords);
		
		patternIndex = patternIndex % 4;
		
		if(pattern[patternIndex] == '1')
		{
			glVertex2i(x, round(y));
//			cout << "(X,Y): (" << x << "," << round(y) << ")" << endl;
			
//			erasePreviousLine(x, round(y));
//			drawNewLine(x, round(y), LineColor.Red, LineColor.Green, LineColor.Blue);
		}
//		else
//		{
//			erasePreviousLine(x, round(y));
//			drawNewLine(x, round(y), BackgroundColor.Red, BackgroundColor.Green, BackgroundColor.Blue);
//		}
		
		patternIndex++;
	}
}

void SimpleDDA::slopeGT1(int LLE, int X1, int Y1, int X2, int Y2, float x, float y, float dx)
{
	float xIncr;
	
	pair<int, int> currCoords;
	
	xIncr = fabs(float(dx) / float(LLE));
	
	for (int i=0; i<LLE; i++)
	{
		if (X2 > X1)
		{
			x += xIncr;
		}
		else if (X2 < X1)
		{
			x -= xIncr;
		}

		if (Y2 > Y1)
		{
			y++;
		}
		else if (Y2 < Y1)
		{
			y--;
		}
		
		currCoords.first = round(x);
		currCoords.second = y;
		Coords.push_back(currCoords);
		
		patternIndex = patternIndex % 4;
		
		if(pattern[patternIndex] == '1')
		{
			glVertex2i(round(x), y);
//			cout << "(X,Y): (" << round(x) << "," << y << ")" << endl;
			
//			erasePreviousLine(round(x), y);
//			drawNewLine(round(x), y, LineColor.Red, LineColor.Green, LineColor.Blue);
		}
//		else
//		{
//			erasePreviousLine(round(x), y);
//			drawNewLine(round(x), y, BackgroundColor.Red, BackgroundColor.Green, BackgroundColor.Blue);
//		}
		
		patternIndex++;
	}
}

bool SimpleDDA::selectObject(pair<int, int> clickedCoords)
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

void SimpleDDA::translate(int dx, int dy)
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

void SimpleDDA::rotate(int rotAngle, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void SimpleDDA::scale(int scaleX, int scaleY, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void SimpleDDA::setPattern(string pattern)
{
	this->pattern = pattern;
}

void SimpleDDA::setThickness(int thickness)
{
	this->thickness = thickness;
}

void SimpleDDA::setColor(unsigned char *color)
{
	this->color = color;
}

void SimpleDDA::erasePreviousObject()
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

void SimpleDDA::redrawSelectedObject(unsigned char* color, int thickness)
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
