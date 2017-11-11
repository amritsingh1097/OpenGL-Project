#include <math.h>
#include "ellipse.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;
extern int ScreenSizeX, ScreenSizeY;

extern void redrawAllObjects();

MidPoint_Ellipse::MidPoint_Ellipse(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 8;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->isFilled = false;
	this->objectName = (char*)"MidPoint_Ellipse";
}

void MidPoint_Ellipse::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int MidPoint_Ellipse::getShapeID()
{
	return shapeID;
}

void MidPoint_Ellipse::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	centerX = XCoord1;
	centerY = YCoord1;
	
	radiusX = abs(XCoord2 - XCoord1);
	radiusY = abs(YCoord2 - YCoord1);
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	
	if(radiusX < radiusY)
	{
		cout << "Vertical MidPoint_Ellipse" << endl;
		verticalEllipse();
	}
	else
	{
		cout << "Horizontal MidPoint_Ellipse" << endl;
		horizontalEllipse();
	}
	
	glEnd();
	glFlush();
}

void MidPoint_Ellipse::horizontalEllipse()
{
	pair<int, int> currCoords;
	int RXSquare, RYSquare;
	int prevDescParamR1, prevDescParamR2, currDescParamR1, currDescParamR2;
	int quad1_X, quad1_Y, quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	
	cout << "Center X: " << centerX << "\tCenter Y: " << centerY << endl;
	cout << "Radius X: " << radiusX << "\tRadius Y: " << radiusY << endl;
	
	RXSquare = pow(radiusX, 2);
	RYSquare = pow(radiusY, 2);
	
	quad1_X = radiusX;
	quad1_Y = 0;
	
	prevDescParamR1 = RYSquare - (RXSquare * radiusY) + ((1/4) * RXSquare);
	
//	glBegin(GL_POINTS);
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))		glVertex2i(quad1_X + centerX, quad1_Y + centerY);
//	if(!viewport->isClipped(quad1_Y + centerX, quad1_X + centerY))		glVertex2i(-quad1_Y + centerX, quad1_X + centerY);
	if(!viewport->isClipped(quad1_X + centerX, -quad1_Y + centerY))		glVertex2i(-quad1_X + centerX, -quad1_Y + centerY);
//	if(!viewport->isClipped(quad1_Y + centerX, quad1_X + centerY))		glVertex2i(quad1_Y + centerX, quad1_X + centerY);
	
	currCoords.first = quad1_X + centerX;
	currCoords.second = quad1_Y + centerY;
	Coords.push_back(currCoords);
	
//	currCoords.first = -quad1_Y + centerX;
//	currCoords.second = quad1_X + centerY;
//	Coords.push_back(currCoords);
	
	currCoords.first = -quad1_X + centerX;
	currCoords.second = -quad1_Y + centerY;
	Coords.push_back(currCoords);
	
//	currCoords.first = quad1_Y + centerX;
//	currCoords.second = quad1_X + centerY;
//	Coords.push_back(currCoords);
	
	quad2_X = -quad1_X;
	quad3_X = -quad1_X;
	quad4_X = quad1_X;
//	cout << "PrevDescParam: " << prevDescParamR1 << endl;
	while((2 * RXSquare * quad1_Y) <= (2 * RYSquare * quad1_X))
	{
//		glBegin(GL_POINTS);
		quad1_Y++;
		
		quad2_Y = quad1_Y;
		quad3_Y = -quad1_Y;
		quad4_Y = -quad1_Y;
		
		if(prevDescParamR1 < 0)
		{
			currDescParamR1 = prevDescParamR1 + (2 * RXSquare * (quad1_Y)) + RXSquare;
		}
		else
		{
			quad1_X--;
			quad2_X = -quad1_X;
			quad3_X = -quad1_X;
			quad4_X = quad1_X;
			currDescParamR1 = prevDescParamR1 + (2 * RXSquare * (quad1_Y)) + RXSquare - (2 * RYSquare * quad1_X);
		}
		
		prevDescParamR1 = currDescParamR1;
		
		currCoords.first = quad1_X + centerX;
		currCoords.second = quad1_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad2_X + centerX;
		currCoords.second = quad2_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad3_X + centerX;
		currCoords.second = quad3_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad4_X + centerX;
		currCoords.second = quad4_Y + centerY;
		Coords.push_back(currCoords);
		
//		cout << "Quad1_X: " << quad1_X << "\tQuad1_Y: " << quad1_Y << endl;
//		cout << "CurrDescParamR1: " << currDescParamR1 << endl << endl;
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
//		glEnd();
//		glFlush();
	}
	
//	cout << "Boundary Hit" << endl;
	prevDescParamR2 = (RXSquare * (quad1_Y + 0.5) * (quad1_Y + 0.5)) + (RYSquare * (quad1_X - 1) * (quad1_X - 1)) - (RXSquare * RYSquare);
	while(quad1_X >= 0)
	{
//		glBegin(GL_POINTS);
		quad1_X--;
		
		quad2_X = -quad1_X;
		quad3_X = -quad1_X;
		quad4_X = quad1_X;

		if(prevDescParamR2 < 0)
		{
			quad1_Y++;
			quad2_Y = quad1_Y;
			quad3_Y = -quad1_Y;
			quad4_Y = -quad1_Y;
			currDescParamR2 = prevDescParamR2 + (2 * RXSquare * quad1_Y) - (2 * RYSquare * quad1_X) + RYSquare;
		}
		else
		{
			currDescParamR2 = prevDescParamR2 - (2 * RYSquare * quad1_X) + RYSquare;
		}
		
		prevDescParamR2 = currDescParamR2;
		
		currCoords.first = quad1_X + centerX;
		currCoords.second = quad1_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad2_X + centerX;
		currCoords.second = quad2_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad3_X + centerX;
		currCoords.second = quad3_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad4_X + centerX;
		currCoords.second = quad4_Y + centerY;
		Coords.push_back(currCoords);
		
//		cout << "Quad1_X: " << quad1_X << "\tQuad1_Y: " << quad1_Y << endl;
//		cout << "CurrDescParamR2: " << currDescParamR2 << endl << endl;
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
//		glEnd();
//		glFlush();
	}
	
	
	
//	glEnd();
//	glFlush();
}

void MidPoint_Ellipse::verticalEllipse()
{
	pair<int, int> currCoords;
	int RXSquare, RYSquare;
	int prevDescParamR1, prevDescParamR2, currDescParamR1, currDescParamR2, XDescParam, YDescParam;
	int quad1_X, quad1_Y, quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	
//	cout << "Center X: " << centerX << "\tCenter Y: " << centerY << endl;
//	cout << "Radius X: " << radiusX << "\tRadius Y: " << radiusY << endl;
	
	quad1_X = 0;
	quad1_Y = radiusY;
	
	RXSquare = pow(radiusX, 2);
	RYSquare = pow(radiusY, 2);
	
//	XDescParam = 2 * RYSquare * quad1_X;
//	XDescParam = 0;
//	YDescParam = 2 * RXSquare * quad1_Y;
	prevDescParamR1 = RYSquare - (RXSquare * radiusY) + (0.25 * RXSquare);
	
//	glBegin(GL_POINTS);
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))		glVertex2i(quad1_X + centerX, quad1_Y + centerY);
	if(!viewport->isClipped(-quad1_Y + centerX, quad1_X + centerY))		glVertex2i(-quad1_Y + centerX, quad1_X + centerY);
	if(!viewport->isClipped(quad1_X + centerX, -quad1_Y + centerY))		glVertex2i(quad1_X + centerX, -quad1_Y + centerY);
	if(!viewport->isClipped(quad1_Y + centerX, quad1_X + centerY))		glVertex2i(quad1_Y + centerX, quad1_X + centerY);
	
	currCoords.first = quad1_X + centerX;
	currCoords.second = quad1_Y + centerY;
	Coords.push_back(currCoords);
	
	currCoords.first = -quad1_Y + centerX;
	currCoords.second = quad1_X + centerY;
	Coords.push_back(currCoords);
	
	currCoords.first = quad1_X + centerX;
	currCoords.second = -quad1_Y + centerY;
	Coords.push_back(currCoords);
	
	currCoords.first = quad1_Y + centerX;
	currCoords.second = quad1_X + centerY;
	Coords.push_back(currCoords);
	
	quad2_Y = quad1_Y;
	quad3_Y = -quad1_Y;
	quad4_Y = -quad1_Y;
	
//	cout << "PrevDescParam: " << prevDescParamR1 << endl;
//	while(XDescParam < YDescParam)
	while((2 * RYSquare * quad1_X) < (2 * RXSquare * quad1_Y))
	{
//		glBegin(GL_POINTS);
		quad1_X++;
		XDescParam += 2 * RYSquare;
		
		quad2_X = -quad1_X;
		quad3_X = -quad1_X;
		quad4_X = quad1_X;
		
		if(prevDescParamR1 < 0)
		{
			currDescParamR1 = prevDescParamR1 + (2 * RYSquare * (quad1_X)) + RYSquare;
//			currDescParamR1 = prevDescParamR1 + XDescParam + RYSquare;
		}
		else
		{
			quad1_Y--;
			quad2_Y = quad1_Y;
			quad3_Y = -quad1_Y;
			quad4_Y = -quad1_Y;
			YDescParam -= 2 * RXSquare;
			currDescParamR1 = prevDescParamR1 + (2 * RYSquare * (quad1_X)) + RYSquare - (2 * RXSquare * quad1_Y);
//			currDescParamR1 = prevDescParamR1 + XDescParam + RYSquare - YDescParam;
		}
		
		prevDescParamR1 = currDescParamR1;
		
		currCoords.first = quad1_X + centerX;
		currCoords.second = quad1_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad2_X + centerX;
		currCoords.second = quad2_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad3_X + centerX;
		currCoords.second = quad3_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad4_X + centerX;
		currCoords.second = quad4_Y + centerY;
		Coords.push_back(currCoords);
		
//		cout << "Quad1_X: " << quad1_X << "\tQuad1_Y: " << quad1_Y << endl;
//		cout << "CurrDescParamR1: " << currDescParamR1 << endl << endl;
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
//		glEnd();
//		glFlush();
	}
	
//	cout << "Boundary Hit" << endl;
	prevDescParamR2 = (RYSquare * (quad1_X + 0.5) * (quad1_X + 0.5)) + (RXSquare * (quad1_Y - 1) * (quad1_Y - 1)) - (RXSquare * RYSquare);
	while(quad1_Y >= 0)
	{
//		glBegin(GL_POINTS);
		quad1_Y--;
		YDescParam -= 2 * RXSquare;
		
		quad2_Y = quad1_Y;
		quad3_Y = -quad1_Y;
		quad4_Y = -quad1_Y;

		if(prevDescParamR2 < 0)
		{
			quad1_X++;
			quad2_X = -quad1_X;
			quad3_X = -quad1_X;
			quad4_X = quad1_X;
			XDescParam += 2 * RYSquare;
			currDescParamR2 = prevDescParamR2 + (2 * RYSquare * quad1_X) - (2 * RXSquare * quad1_Y) + RXSquare;
//			currDescParamR2 = prevDescParamR2 + RXSquare + XDescParam - YDescParam;
		}
		else
		{
			currDescParamR2 = prevDescParamR2 - (2 * RXSquare * quad1_Y) + RXSquare;
//			currDescParamR2 = prevDescParamR2 + RXSquare - YDescParam;
		}
		
		prevDescParamR2 = currDescParamR2;
		
		currCoords.first = quad1_X + centerX;
		currCoords.second = quad1_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad2_X + centerX;
		currCoords.second = quad2_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad3_X + centerX;
		currCoords.second = quad3_Y + centerY;
		Coords.push_back(currCoords);
		
		currCoords.first = quad4_X + centerX;
		currCoords.second = quad4_Y + centerY;
		Coords.push_back(currCoords);
		
//		cout << "Quad1_X: " << quad1_X << "\tQuad1_Y: " << quad1_Y << endl;
//		cout << "CurrDescParamR2: " << currDescParamR2 << endl << endl;
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
		
//		glEnd();
//		glFlush();
	}
	
//	glEnd();
//	glFlush();
}

bool MidPoint_Ellipse::selectObject(pair<int, int> clickedCoords)
{
	int result;
	int tempX, tempY;
	tempX = clickedCoords.first - centerX;
	tempY = clickedCoords.second - centerY;
	result = (radiusY * radiusY * tempX * tempX) + (radiusX * radiusX * tempY * tempY) - (radiusX * radiusX * radiusY * radiusY);
//	result = (clickedCoords.first * clickedCoords.first) + (clickedCoords.second * clickedCoords.second) - (radius * radius);
	
	if(result <= 0)
	{
		redrawSelectedObject(Color::RED, thickness);
		return true;
	}
	
//	list< pair<int, int> >::iterator it;
//	for(it = Coords.begin(); it != Coords.end(); it++)
//	{
//		if((*it).first == clickedCoords.first && (*it).second == clickedCoords.second)
//		{
//			redrawSelectedObject(Color::RED, thickness);
//			return true;
//		}
//	}
	return false;
}

void MidPoint_Ellipse::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX += dx;
	centerY += dy;
	radiusX += dx;
	radiusY += dy;
	
	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
	
	redrawAllObjects();
}

void MidPoint_Ellipse::rotate(int rotAngleDeg, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	float PI = 3.14159;
	float sinTheeta;
	float cosTheeta;
	float rotAngleRad = (float)rotAngleDeg * (PI / (float)180);
	float tempX, tempY;
	float pivotX, pivotY;
	
	pivotX = pivot.first;
	pivotY = pivot.second;
	
	sinTheeta = sin(rotAngleRad);
	cosTheeta = cos(rotAngleRad);
	
	tempX = centerX;
	tempY = centerY;
	centerX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	centerY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	tempX = radiusX;
	tempY = radiusY;
	radiusX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	radiusY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	list< pair<int, int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		tempX = (*it).first;
		tempY = (*it).second;
		(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
		(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}

	tempX = selectedCoords.first;
	tempY = selectedCoords.second;
	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	redrawAllObjects();
}

void MidPoint_Ellipse::scale(float scaleFactor, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX = round(((float)centerX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	centerY = round(((float)centerY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	radiusX = round(((float)radiusX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	radiusY = round(((float)radiusY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	Coords.clear();
	draw(centerX, centerY, radiusX, radiusY);
	
	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	redrawAllObjects();
}

void MidPoint_Ellipse::setPattern(string pattern)
{
	this->pattern = pattern;
}

void MidPoint_Ellipse::setThickness(int thickness)
{
	this->thickness = thickness;
}

void MidPoint_Ellipse::setColor(unsigned char *color)
{
	this->color = color;
}

void MidPoint_Ellipse::setFillColor(unsigned char *fillColor)
{
	this->fillColor = fillColor;
}

void MidPoint_Ellipse::erasePreviousObject()
{
	list< pair<int, int> >::iterator it;
	
	glBegin(GL_POINTS);
	
	it = Coords.begin();
	
		glVertex2i((*it).first, (*it).second);
	
	it = Coords.end();
	
		glVertex2i((*it).first, (*it).second);
	glEnd();
	
	glColor3ubv(Color::BACKGROUND_COLOR);
	glBegin(GL_POINTS);
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		glVertex2i((*it).first, (*it).second);
	}
	glEnd();
	glFlush();
}

void MidPoint_Ellipse::redrawSelectedObject(unsigned char* color, int thickness)
{
	glColor3ubv(color);
	glPointSize(thickness);
	
	list< pair<int, int> >::iterator it;
	glBegin(GL_POINTS);
		for(it = Coords.begin(); it != Coords.end(); it++)
		{
			patternIndex %= 4;
			if(pattern[patternIndex] == '1' && !viewport->isClipped((*it).first, (*it).second))
			{
				glVertex2i((*it).first, (*it).second);
			}
			patternIndex++;
		}
	glEnd();
	glFlush();
	
	if(isFilled)
	{
		if(color == this->color)		glColor3ubv(fillColor);
		else	glColor3ub(color[0] - 2, color[1], color[2]);
		glBegin(GL_POINTS);
			cout << "IsFilled: " << isFilled << endl;
			for(it = filledCoords.begin(); it != filledCoords.end(); it++)
			{
				if(!viewport->isClipped((*it).first, (*it).second))
					glVertex2i((*it).first, (*it).second);
			}
		glEnd();
		glFlush();
	}
}

void MidPoint_Ellipse::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
//void MidPoint_Ellipse::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
	if(!(((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
	|| ((int)XYPixelColor[0] == (int)Color::VIEWPORT_COLOR[0] && (int)XYPixelColor[1] == (int)Color::VIEWPORT_COLOR[1] && (int)XYPixelColor[2] == (int)Color::VIEWPORT_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
//		glFlush();

		isFilled = true;
		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		fourFillBoundary(x+1, y, fillColor, selectedObjectColor);
		fourFillBoundary(x-1, y, fillColor, selectedObjectColor);
		glFlush();
		fourFillBoundary(x, y+1, fillColor, selectedObjectColor);
		fourFillBoundary(x, y-1, fillColor, selectedObjectColor);
//		glFlush();
	}
}

void MidPoint_Ellipse::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
	if(!(((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
	|| ((int)XYPixelColor[0] == (int)Color::VIEWPORT_COLOR[0] && (int)XYPixelColor[1] == (int)Color::VIEWPORT_COLOR[1] && (int)XYPixelColor[2] == (int)Color::VIEWPORT_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
		glFlush();

		isFilled = true;
		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		eightFillBoundary(x+1, y, fillColor, selectedObjectColor);
		eightFillBoundary(x-1, y, fillColor, selectedObjectColor);
		glFlush();
		eightFillBoundary(x, y+1, fillColor, selectedObjectColor);
		eightFillBoundary(x, y-1, fillColor, selectedObjectColor);

		eightFillBoundary(x-1, y+1, fillColor, selectedObjectColor);
		eightFillBoundary(x+1, y+1, fillColor, selectedObjectColor);
		eightFillBoundary(x+1, y-1, fillColor, selectedObjectColor);
		eightFillBoundary(x-1, y-1, fillColor, selectedObjectColor);
//		glFlush();
	}

}

void MidPoint_Ellipse::floodFill(int x, int y, unsigned char* fillColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
	if(!(((int)XYPixelColor[0] == (int)Color::BACKGROUND_COLOR[0] && (int)XYPixelColor[1] == (int)Color::BACKGROUND_COLOR[1] && (int)XYPixelColor[2] == (int)Color::BACKGROUND_COLOR[2])))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
//		glFlush();

		isFilled = true;
		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		floodFill(x+1, y, fillColor);
		floodFill(x-1, y, fillColor);
		glFlush();
		floodFill(x, y+1, fillColor);
		floodFill(x, y-1, fillColor);
//		glFlush();
	}

}
