#include <math.h>
#include "mid_pointlda.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

Mid_PointLDA::Mid_PointLDA(unsigned char* color, int thickness, string pattern)
{
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->objectName = (char*)"Mid-Point Line";
}

void Mid_PointLDA::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

void Mid_PointLDA::draw(int X1, int Y1, int X2, int Y2)
{
	pair<int, int> currCoords;
	int dx, dy;
	int x, y, steps;
	
	x = X1;
	y = Y1;
	dx = abs(X2 - X1);
	dy = abs(Y2 - Y1);
	
	steps = max(fabs(dx), fabs(dy));

//	cout << "Steps: " << steps << endl << endl;
//	cout << "(X,Y): (" << x << "," << y << ")" << endl;
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	
	currCoords.first = x;
	currCoords.second = y;
	Coords.push_back(currCoords);
	
	if(fabs(dx) > fabs(dy))
	{
		slopeLT1(X1, Y1, X2, Y2, steps, x, y, dx, dy);
	}
	else
	{
		slopeGT1(X1, Y1, X2, Y2, steps, x, y, dx, dy);
	}
	
	glEnd();
	glFlush();
}

void Mid_PointLDA::slopeLT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy)
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
			currDescParam = prevDescParam + dy;
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
			currDescParam = prevDescParam + dy - dx;
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

void Mid_PointLDA::slopeGT1(int XCoord1, int YCoord1, int XCoord2, int YCoord2, int steps, int x, int y, int dx, int dy)
{
	pair<int, int> currCoords;
	float prevDescParam, currDescParam;
	int index = 0;
	
	prevDescParam = -(dy / 2) + dx;
	
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
			currDescParam = prevDescParam + dx;
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
			currDescParam = prevDescParam - dy + dx;
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

bool Mid_PointLDA::selectObject(pair<int, int> clickedCoords)
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

void Mid_PointLDA::translate(int dx, int dy)
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

void Mid_PointLDA::rotate(int rotAngle, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void Mid_PointLDA::scale(int scaleX, int scaleY, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
}

void Mid_PointLDA::setPattern(string pattern)
{
	this->pattern = pattern;
}

void Mid_PointLDA::setThickness(int thickness)
{
	this->thickness = thickness;
}

void Mid_PointLDA::setColor(unsigned char *color)
{
	this->color = color;
}

void Mid_PointLDA::erasePreviousObject()
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

void Mid_PointLDA::redrawSelectedObject(unsigned char* color, int thickness)
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
