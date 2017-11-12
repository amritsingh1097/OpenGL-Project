<<<<<<< HEAD
#include <bits/stdc++.h>
#include <math.h>
#include "circle.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

list< pair<int, int> > customStack;
list< pair<int, int> >::iterator stackIterator;

MidPoint_Circle::MidPoint_Circle(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 7;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->isFilled = false;
	this->objectName = (char*)"MidPoint_Circle";
}

void MidPoint_Circle::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int MidPoint_Circle::getShapeID()
{
	return shapeID;
}

void MidPoint_Circle::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	pair<int, int> currCoords;
	float prevDescParam, currDescParam;
	int quad1_X, quad1_Y, quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	int doubleX, doubleY;
	
	centerX = XCoord1;
	centerY = YCoord1;
	
	clickedRadiusX = XCoord2;
	clickedRadiusY = YCoord2;

//	centerX = 0;
//	centerY = 0;
	
	radius = sqrt(pow((XCoord2 - XCoord1), 2) + pow((YCoord2 - YCoord1), 2));
	
	quad1_X = 0;
	quad1_Y = radius;
	prevDescParam = 1 - radius;
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	
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
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))		glVertex2i(quad1_X + centerX, quad1_Y + centerY);
	if(!viewport->isClipped(-quad1_Y + centerX, quad1_X + centerY))		glVertex2i(-quad1_Y + centerX, quad1_X + centerY);
	if(!viewport->isClipped(quad1_X + centerX, -quad1_Y + centerY))		glVertex2i(quad1_X + centerX, -quad1_Y + centerY);
	if(!viewport->isClipped(quad1_Y + centerX, quad1_X + centerY))		glVertex2i(quad1_Y + centerX, quad1_X + centerY);

	quad2_Y = quad1_Y;
	quad3_Y = -quad1_Y;
	quad4_Y = -quad1_Y;
	
	do
	{
		quad1_X++;
		quad2_X = -quad1_X;
		quad3_X = -quad1_X;
		quad4_X = quad1_X;
		
		doubleX = 2 * quad1_X;
		if (prevDescParam < 0)
		{
			currDescParam = prevDescParam + doubleX + 1;
		}
		else
		{
			quad1_Y--;
			quad2_Y = quad1_Y;
			quad3_Y = -quad1_Y;
			quad4_Y = -quad1_Y;
			doubleY = 2 * quad1_Y;
			currDescParam = prevDescParam + doubleX - doubleY + 1;
		}
		
		prevDescParam = currDescParam;
		
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
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
		swapPoints(centerX, centerY, quad1_X, quad1_Y);
		
	} while (quad1_X <= quad1_Y);

	glEnd();
	glFlush();
}

void MidPoint_Circle::swapPoints(int centerX, int centerY, int quad1_X, int quad1_Y)
{
	pair<int, int> currCoords;
	int temp;
	int quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	
	// Swapping to get arc beyound (to the right) 45 degree line
	temp = quad1_X;
	quad1_X = quad1_Y;
	quad1_Y = temp;
	
	quad2_X = -quad1_X;
	quad3_X = -quad1_X;
	quad4_X = quad1_X;
	
	quad2_Y = quad1_Y;
	quad3_Y = -quad1_Y;
	quad4_Y = -quad1_Y;
	
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
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
	if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
	if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
	if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
}

bool MidPoint_Circle::selectObject(pair<int, int> clickedCoords)
{
	int result;
	int tempX, tempY;
	tempX = clickedCoords.first - centerX;
	tempY = clickedCoords.second - centerY;
	result = (tempX * tempX) + (tempY * tempY) - (radius * radius);
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

void MidPoint_Circle::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX += dx;
	centerY += dy;
	clickedRadiusX += dx;
	clickedRadiusY += dy;
	
	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
	if(isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			(*it).first += dx;
			(*it).second += dy;
		}
	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
	
	redrawAllObjects();
}

void MidPoint_Circle::rotate(int rotAngleDeg, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	const float PI = 3.14159;
	float sinTheeta;
	float cosTheeta;
	float rotAngleRad = (float)rotAngleDeg * (PI / (float)180);
//	int tempSin, tempCos;
	float tempX, tempY;
	float pivotX, pivotY;
	
	pivotX = pivot.first;
	pivotY = pivot.second;
	
	sinTheeta = sin(rotAngleRad);
	cosTheeta = cos(rotAngleRad);
//	redrawSelectedObject(color, thickness);
	
	tempX = centerX;
	tempY = centerY;
	centerX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	centerY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));

	tempX = clickedRadiusX;
	tempY = clickedRadiusY;
	clickedRadiusX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	clickedRadiusY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	if(isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			tempX = (*it).first;
			tempY = (*it).second;
			(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
			(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
		}
	}
	
	Coords.clear();
//	draw(centerX, centerY, 0, radius);
	draw(centerX, centerY, clickedRadiusX, clickedRadiusY);
	
	tempX = selectedCoords.first;
	tempY = selectedCoords.second;
	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	redrawAllObjects();
	
//	sinTheeta = sinTheeta * 100;
//	cosTheeta = cosTheeta * 100;
//	
//	tempSin = sinTheeta;
//	tempCos = cosTheeta;
//	
//	sinTheeta = (float)tempSin/100;
//	cosTheeta = (float)tempCos/100;
	
//	list< pair<int, int> >::iterator it;
//	for(it = Coords.begin(); it != Coords.end(); it++)
//	{
//		tempX = (*it).first;
//		tempY = (*it).second;
//		(*it).first = round((tempX * cosTheeta) - (tempY * sinTheeta));
//		(*it).second = round((tempX * sinTheeta) + (tempY * cosTheeta));
//		cout << "Coord1: " << ((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta);
//		cout << "\tCoord2: " << ((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta) << endl;
//		(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
//		(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
//	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
}

void MidPoint_Circle::scale(float scaleFactor, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX = round(((float)centerX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	centerY = round(((float)centerY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	clickedRadiusX = round(((float)clickedRadiusX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	clickedRadiusY = round(((float)clickedRadiusY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	Coords.clear();
	draw(centerX, centerY, clickedRadiusX, clickedRadiusY);
	
	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	redrawAllObjects();
}

void MidPoint_Circle::setPattern(string pattern)
{
	this->pattern = pattern;
}

void MidPoint_Circle::setThickness(int thickness)
{
	this->thickness = thickness;
}

void MidPoint_Circle::setColor(unsigned char *color)
{
	this->color = color;
}

void MidPoint_Circle::setFillColor(unsigned char *fillColor)
{
	this->fillColor = fillColor;
}

void MidPoint_Circle::erasePreviousObject()
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

void MidPoint_Circle::redrawSelectedObject(unsigned char* color, int thickness)
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

void MidPoint_Circle::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
//	if(filledCoords.size() > 0)	return;
//	if(isFilled)	return;
	
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
		
		fourFillBoundary(x+1, y, fillColor, selectedObjectColor);	// Right Pixel
		fourFillBoundary(x-1, y, fillColor, selectedObjectColor);	// Left Pixel
		glFlush();
		fourFillBoundary(x, y+1, fillColor, selectedObjectColor);	// Upper Pixel
		fourFillBoundary(x, y-1, fillColor, selectedObjectColor);	// Lower Pixel
//		glFlush();
	}

}

void MidPoint_Circle::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
//	if(!(XYPixelColor == fillColor || XYPixelColor == Color::VIEWPORT_COLOR || XYPixelColor == selectedObjectColor))
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
		
		eightFillBoundary(x+1, y, fillColor, selectedObjectColor);		// Right Pixel
		eightFillBoundary(x-1, y, fillColor, selectedObjectColor);		// Left Pixel
		eightFillBoundary(x, y+1, fillColor, selectedObjectColor);		// Upper Pixel
		eightFillBoundary(x, y-1, fillColor, selectedObjectColor);		// Lower Pixel
		glFlush();
		eightFillBoundary(x-1, y+1, fillColor, selectedObjectColor);	// Upper Left Pixel
		eightFillBoundary(x+1, y+1, fillColor, selectedObjectColor);	// Upper Right Pixel
		eightFillBoundary(x+1, y-1, fillColor, selectedObjectColor);	// Lower Right Pixel
		eightFillBoundary(x-1, y-1, fillColor, selectedObjectColor);	// Lower Left Pixel
//		glFlush();
	}

}

void MidPoint_Circle::fourFloodFill(int x, int y, unsigned char* fillColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
//	cout << "Flood Fill..." << endl;
	
//	cout << "Point RED: " << (int)XYPixelColor[0] << "\tGREEN: " << (int)XYPixelColor[1] << "\tBLUE: " << (int)XYPixelColor[2] << endl;
//	cout << "Background RED: " << (int)Color::BACKGROUND_COLOR[0] << "\tGREEN: " << (int)Color::BACKGROUND_COLOR[1] << "\tBLUE: " << (int)Color::BACKGROUND_COLOR[2] << endl;
	
	if(((int)XYPixelColor[0] == (int)Color::BACKGROUND_COLOR[0] && (int)XYPixelColor[1] == (int)Color::BACKGROUND_COLOR[1] && (int)XYPixelColor[2] == (int)Color::BACKGROUND_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::AXIS_COLOR[0] && (int)XYPixelColor[1] == (int)Color::AXIS_COLOR[1] && (int)XYPixelColor[2] == (int)Color::AXIS_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::GRAY[0] && (int)XYPixelColor[1] == (int)Color::GRAY[1] && (int)XYPixelColor[2] == (int)Color::GRAY[2]))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
		glFlush();

		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		fourFloodFill(x+1, y, fillColor);	// Right Pixel
		fourFloodFill(x-1, y, fillColor);	// Left Pixel
		glFlush();
		fourFloodFill(x, y+1, fillColor);	// Upper Pixel
		fourFloodFill(x, y-1, fillColor);	// Lower Pixel
//		glFlush();
	}

}

void MidPoint_Circle::eightFloodFill(int x, int y, unsigned char* fillColor)
{
	unsigned char XYPixelColor[4];

	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);

//	cout << "Flood Fill..." << endl;

//	cout << "Point RED: " << (int)XYPixelColor[0] << "\tGREEN: " << (int)XYPixelColor[1] << "\tBLUE: " << (int)XYPixelColor[2] << endl;
//	cout << "Background RED: " << (int)Color::BACKGROUND_COLOR[0] << "\tGREEN: " << (int)Color::BACKGROUND_COLOR[1] << "\tBLUE: " << (int)Color::BACKGROUND_COLOR[2] << endl;

	if(((int)XYPixelColor[0] == (int)Color::BACKGROUND_COLOR[0] && (int)XYPixelColor[1] == (int)Color::BACKGROUND_COLOR[1] && (int)XYPixelColor[2] == (int)Color::BACKGROUND_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::AXIS_COLOR[0] && (int)XYPixelColor[1] == (int)Color::AXIS_COLOR[1] && (int)XYPixelColor[2] == (int)Color::AXIS_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::GRAY[0] && (int)XYPixelColor[1] == (int)Color::GRAY[1] && (int)XYPixelColor[2] == (int)Color::GRAY[2]))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
		glFlush();

		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));

		eightFloodFill(x+1, y, fillColor);	// Right Pixel
		eightFloodFill(x-1, y, fillColor);	// Left Pixel
		eightFloodFill(x, y+1, fillColor);	// Upper Pixel
		eightFloodFill(x, y-1, fillColor);	// Lower Pixel
		glFlush();
		eightFloodFill(x-1, y+1, fillColor);	// Upper Left Pixel
		eightFloodFill(x+1, y+1, fillColor);	// Upper Right Pixel
		eightFloodFill(x+1, y-1, fillColor);	// Lower Right Pixel
		eightFloodFill(x-1, y-1, fillColor);	// Lower Left Pixel
	}

}

//void MidPoint_Circle::fillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempCoords;
//	bool flag = false;
//	
//	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
////		cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED---------!!!!!!!!!!!!!!!!!!!!" << endl;
//		return;
//	}
////	if((int)XYPixelColor[0] == (int)Color::VIEWPORT_COLOR[0] && (int)XYPixelColor[1] == (int)Color::VIEWPORT_COLOR[1] && (int)XYPixelColor[2] == (int)Color::VIEWPORT_COLOR[2])
////	{
////		cout << "Viewport Hit..." << endl;
////		return;
////	}
//	if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//	{
////		cout << "Boundary Hit..." << endl;
////		getch();
//		return;
//	}
//	
////	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
////	cout << "Coloring Pixel (" << x << ", " << y << ")" << endl;
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
//	glEnd();
////	glFlush();
//	
////	cout << "Y: " << y << endl;
////	flag = false;
////	glReadPixels(x, ScreenSizeY - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
////	if((int)XYPixelColor[0] != (int)fillColor[0] && (int)XYPixelColor[1] != (int)fillColor[1] && (int)XYPixelColor[2] != (int)fillColor[2])
////	{
//////		for(stackIterator = customStack.begin(); stackIterator != customStack.end(); stackIterator++)
//////		{
////////			cout << "StackIterator: " << &(*stackIterator) << "\t*StackIterator: " << (*stackIterator) << endl;
//////			if((*stackIterator) == y-1)
//////			{
//////				flag = true;
//////				break;
//////			}
//////		}
//////		if(!flag)
//////		{
////			tempCoords.first = x;
////			tempCoords.second = y-1;
////			customStack.push_back(tempCoords);
////			cout << "Pushed (" << x << ", " << y-1 << ")" << endl << endl;
//////		}
////	}
////	
////	flag = false;
////	glReadPixels(x, ScreenSizeY - y + 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
////	if((int)XYPixelColor[0] != (int)fillColor[0] && (int)XYPixelColor[1] != (int)fillColor[1] && (int)XYPixelColor[2] != (int)fillColor[2])
////	{
//////		for(stackIterator = customStack.begin(); stackIterator != customStack.end(); stackIterator++)
//////		{
////////			cout << "StackIterator: " << stackIterator << "*StackIterator: " << (*stackIterator) << endl;
//////			if((*stackIterator) == y+1)
//////			{
//////				flag = true;
//////				break;
//////			}
//////		}
//////		if(!flag)
//////		{
////			tempCoords.first = x;
////			tempCoords.second = y+1;
////			customStack.push_back(tempCoords);
////			cout << "Pushed (" << x << ", " << y+1 << ")" << endl << endl;
//////		}
////	}
//	
//	fillBoundary(x+1, y, fillColor, selectedObjectColor);
////	cout << "Call 1 ended..." << endl;
//	fillBoundary(x-1, y, fillColor, selectedObjectColor);
//	glFlush();
////	cout << "Call 2 ended..." << endl;
//	fillBoundary(x, y+1, fillColor, selectedObjectColor);
//	fillBoundary(x, y-1, fillColor, selectedObjectColor);
//
////	cout << "Stack Front: " << customStack.front() << endl;
////	x = customStack.back().first;
////	y = customStack.back().second;
////	customStack.pop_back();
//////	cout << "Popped" << endl;
////	cout << "Popped (" << x << ", " << y << ")" << endl;
////	fillBoundary(x, y, fillColor, selectedObjectColor);
//	
////	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	
//	while(true)
//	{
//		while(true)
//		{
//			while(true)
//			{
//				glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//				if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//				{
////					cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////					getch();
//					break;
//				}
//				glBegin(GL_POINTS);
//					glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//				glEnd();
//				glFlush();
//				tempSeed.first++;
//			}
//			tempSeed.first = seed.first;
//			while(true)
//			{
//				glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//				if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//				{
////					cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////					getch();
//					break;
//				}
//				glBegin(GL_POINTS);
//					glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//				glEnd();
//				glFlush();
//				tempSeed.first--;
//			}
//			tempSeed.first = seed.first;
//			tempSeed.second++;
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				tempSeed.second = seed.second;
//				break;
//			}
//		}
//		tempSeed.first = seed.first;
//		tempSeed.second--;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
//			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 4---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	
//	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	
//	for(tempSeed.second = seed.second; ; tempSeed.second++)
//	{
//		for(tempSeed.first = seed.first; ; tempSeed.first++)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
////			glFlush();
//		}
//		for(tempSeed.first = seed.first; ; tempSeed.first--)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
//		}
//		glFlush();
//		tempSeed.first = seed.first;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
////			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	for(tempSeed.second = seed.second; ; tempSeed.second--)
//	{
//		for(tempSeed.first = seed.first; ; tempSeed.first++)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
////			glFlush();
//		}
//		for(tempSeed.first = seed.first; ; tempSeed.first--)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
//		}
//		glFlush();
//		tempSeed.first = seed.first;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
////			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	
//	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor_1[4], XYPixelColor_2[4], XYPixelColor_3[4], XYPixelColor_4[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_1);
//	if((int)XYPixelColor_1[0] == (int)fillColor[0] && (int)XYPixelColor_1[1] == (int)fillColor[1] && (int)XYPixelColor_1[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor_1[0] << "\tG: " << (int)XYPixelColor_1[1] << "\tB: " << (int)XYPixelColor_1[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	bool flag1, flag2, flag3, flag4;
//	flag1 = flag2 = flag3 = flag4 = false;
////	for(int y1 = seed.second, y2 = seed.second; ; )
////	for(int y1 = seed.second, y2 = seed.second; ; y1++, y2--)
//	for(int y1 = seed.second; ; y1++)
//	{
//		flag1 = flag2 = false;
//		for(int x1 = seed.first, x2 = seed.first; ; x1++, x2--)
//		{
//			glReadPixels(x1, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_1);
//			glReadPixels(x2, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_2);
//			if((int)XYPixelColor_1[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_1[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_1[2] == (int)selectedObjectColor[2])
//			{
//				flag1 = true;
//			}
//			if((int)XYPixelColor_2[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_2[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_2[2] == (int)selectedObjectColor[2])
//			{
//				flag2 = true;
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
////				break;
//			}
//			if(flag1 && flag2)
//			{
//				break;
//			}
//			if(!flag1)
//			{
//				glBegin(GL_POINTS);
//					glVertex2i(x1 - ScreenSizeX/2, ScreenSizeY/2 - y1);
//				glEnd();
//				glFlush();
//			}
//			if(!flag2)
//			{
//				glBegin(GL_POINTS);
//					glVertex2i(x2 - ScreenSizeX/2, ScreenSizeY/2 - y1);
//				glEnd();
//				glFlush();
//			}
//		}
////		glFlush();
////		tempSeed.first = seed.first;
//		glReadPixels(seed.first, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_3);
//		if((int)XYPixelColor_3[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_3[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_3[2] == (int)selectedObjectColor[2])
//		{
//			break;
//		}
//	}
//	
//	glFlush();
//	
//	cout << "Exiting Filling..." << endl;
//}
=======
#include <bits/stdc++.h>
#include <math.h>
#include "circle.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

list< pair<int, int> > customStack;
list< pair<int, int> >::iterator stackIterator;

MidPoint_Circle::MidPoint_Circle(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 7;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->isFilled = false;
	this->objectName = (char*)"MidPoint_Circle";
}

void MidPoint_Circle::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int MidPoint_Circle::getShapeID()
{
	return shapeID;
}

void MidPoint_Circle::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	pair<int, int> currCoords;
	float prevDescParam, currDescParam;
	int quad1_X, quad1_Y, quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	int doubleX, doubleY;
	
	centerX = XCoord1;
	centerY = YCoord1;
	
	clickedRadiusX = XCoord2;
	clickedRadiusY = YCoord2;

//	centerX = 0;
//	centerY = 0;
	
	radius = sqrt(pow((XCoord2 - XCoord1), 2) + pow((YCoord2 - YCoord1), 2));
	
	quad1_X = 0;
	quad1_Y = radius;
	prevDescParam = 1 - radius;
	
	glColor3ubv(Color::BLACK);
	glBegin(GL_POINTS);
	
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
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))		glVertex2i(quad1_X + centerX, quad1_Y + centerY);
	if(!viewport->isClipped(-quad1_Y + centerX, quad1_X + centerY))		glVertex2i(-quad1_Y + centerX, quad1_X + centerY);
	if(!viewport->isClipped(quad1_X + centerX, -quad1_Y + centerY))		glVertex2i(quad1_X + centerX, -quad1_Y + centerY);
	if(!viewport->isClipped(quad1_Y + centerX, quad1_X + centerY))		glVertex2i(quad1_Y + centerX, quad1_X + centerY);

	quad2_Y = quad1_Y;
	quad3_Y = -quad1_Y;
	quad4_Y = -quad1_Y;
	
	do
	{
		quad1_X++;
		quad2_X = -quad1_X;
		quad3_X = -quad1_X;
		quad4_X = quad1_X;
		
		doubleX = 2 * quad1_X;
		if (prevDescParam < 0)
		{
			currDescParam = prevDescParam + doubleX + 1;
		}
		else
		{
			quad1_Y--;
			quad2_Y = quad1_Y;
			quad3_Y = -quad1_Y;
			quad4_Y = -quad1_Y;
			doubleY = 2 * quad1_Y;
			currDescParam = prevDescParam + doubleX - doubleY + 1;
		}
		
		prevDescParam = currDescParam;
		
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
		
		if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
		if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
		if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
		if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
		
		swapPoints(centerX, centerY, quad1_X, quad1_Y);
		
	} while (quad1_X <= quad1_Y);

	glEnd();
	glFlush();
}

void MidPoint_Circle::swapPoints(int centerX, int centerY, int quad1_X, int quad1_Y)
{
	pair<int, int> currCoords;
	int temp;
	int quad2_X, quad2_Y, quad3_X, quad3_Y, quad4_X, quad4_Y;
	
	// Swapping to get arc beyound (to the right) 45 degree line
	temp = quad1_X;
	quad1_X = quad1_Y;
	quad1_Y = temp;
	
	quad2_X = -quad1_X;
	quad3_X = -quad1_X;
	quad4_X = quad1_X;
	
	quad2_Y = quad1_Y;
	quad3_Y = -quad1_Y;
	quad4_Y = -quad1_Y;
	
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
	
	if(!viewport->isClipped(quad1_X + centerX, quad1_Y + centerY))	glVertex2i(quad1_X + centerX, quad1_Y + centerY);
	if(!viewport->isClipped(quad2_X + centerX, quad2_Y + centerY))	glVertex2i(quad2_X + centerX, quad2_Y + centerY);
	if(!viewport->isClipped(quad3_X + centerX, quad3_Y + centerY))	glVertex2i(quad3_X + centerX, quad3_Y + centerY);
	if(!viewport->isClipped(quad4_X + centerX, quad4_Y + centerY))	glVertex2i(quad4_X + centerX, quad4_Y + centerY);
}

bool MidPoint_Circle::selectObject(pair<int, int> clickedCoords)
{
	int result;
	int tempX, tempY;
	tempX = clickedCoords.first - centerX;
	tempY = clickedCoords.second - centerY;
	result = (tempX * tempX) + (tempY * tempY) - (radius * radius);
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

void MidPoint_Circle::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX += dx;
	centerY += dy;
	clickedRadiusX += dx;
	clickedRadiusY += dy;
	
	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
	if(isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			(*it).first += dx;
			(*it).second += dy;
		}
	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
	
	redrawAllObjects();
}

void MidPoint_Circle::rotate(int rotAngleDeg, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	const float PI = 3.14159;
	float sinTheeta;
	float cosTheeta;
	float rotAngleRad = (float)rotAngleDeg * (PI / (float)180);
//	int tempSin, tempCos;
	float tempX, tempY;
	float pivotX, pivotY;
	
	pivotX = pivot.first;
	pivotY = pivot.second;
	
	sinTheeta = sin(rotAngleRad);
	cosTheeta = cos(rotAngleRad);
//	redrawSelectedObject(color, thickness);
	
	tempX = centerX;
	tempY = centerY;
	centerX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	centerY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));

	tempX = clickedRadiusX;
	tempY = clickedRadiusY;
	clickedRadiusX = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	clickedRadiusY = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	if(isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			tempX = (*it).first;
			tempY = (*it).second;
			(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
			(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
		}
	}
	
	Coords.clear();
//	draw(centerX, centerY, 0, radius);
	draw(centerX, centerY, clickedRadiusX, clickedRadiusY);
	
	tempX = selectedCoords.first;
	tempY = selectedCoords.second;
	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	redrawAllObjects();
	
//	sinTheeta = sinTheeta * 100;
//	cosTheeta = cosTheeta * 100;
//	
//	tempSin = sinTheeta;
//	tempCos = cosTheeta;
//	
//	sinTheeta = (float)tempSin/100;
//	cosTheeta = (float)tempCos/100;
	
//	list< pair<int, int> >::iterator it;
//	for(it = Coords.begin(); it != Coords.end(); it++)
//	{
//		tempX = (*it).first;
//		tempY = (*it).second;
//		(*it).first = round((tempX * cosTheeta) - (tempY * sinTheeta));
//		(*it).second = round((tempX * sinTheeta) + (tempY * cosTheeta));
//		cout << "Coord1: " << ((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta);
//		cout << "\tCoord2: " << ((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta) << endl;
//		(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
//		(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
//	}
	
//	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
//	{
//		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
//	}
}

void MidPoint_Circle::scale(float scaleFactor, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	centerX = round(((float)centerX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	centerY = round(((float)centerY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	clickedRadiusX = round(((float)clickedRadiusX * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	clickedRadiusY = round(((float)clickedRadiusY * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	Coords.clear();
	draw(centerX, centerY, clickedRadiusX, clickedRadiusY);
	
	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	redrawAllObjects();
}

void MidPoint_Circle::setPattern(string pattern)
{
	this->pattern = pattern;
}

void MidPoint_Circle::setThickness(int thickness)
{
	this->thickness = thickness;
}

void MidPoint_Circle::setColor(unsigned char *color)
{
	this->color = color;
}

void MidPoint_Circle::setFillColor(unsigned char *fillColor)
{
	this->fillColor = fillColor;
}

void MidPoint_Circle::erasePreviousObject()
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

void MidPoint_Circle::redrawSelectedObject(unsigned char* color, int thickness)
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

void MidPoint_Circle::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
//	if(filledCoords.size() > 0)	return;
//	if(isFilled)	return;
	
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
		
		fourFillBoundary(x+1, y, fillColor, selectedObjectColor);	// Right Pixel
		fourFillBoundary(x-1, y, fillColor, selectedObjectColor);	// Left Pixel
		glFlush();
		fourFillBoundary(x, y+1, fillColor, selectedObjectColor);	// Upper Pixel
		fourFillBoundary(x, y-1, fillColor, selectedObjectColor);	// Lower Pixel
//		glFlush();
	}

}

void MidPoint_Circle::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
//	if(!(XYPixelColor == fillColor || XYPixelColor == Color::VIEWPORT_COLOR || XYPixelColor == selectedObjectColor))
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
		
		eightFillBoundary(x+1, y, fillColor, selectedObjectColor);		// Right Pixel
		eightFillBoundary(x-1, y, fillColor, selectedObjectColor);		// Left Pixel
		eightFillBoundary(x, y+1, fillColor, selectedObjectColor);		// Upper Pixel
		eightFillBoundary(x, y-1, fillColor, selectedObjectColor);		// Lower Pixel
		glFlush();
		eightFillBoundary(x-1, y+1, fillColor, selectedObjectColor);	// Upper Left Pixel
		eightFillBoundary(x+1, y+1, fillColor, selectedObjectColor);	// Upper Right Pixel
		eightFillBoundary(x+1, y-1, fillColor, selectedObjectColor);	// Lower Right Pixel
		eightFillBoundary(x-1, y-1, fillColor, selectedObjectColor);	// Lower Left Pixel
//		glFlush();
	}

}

void MidPoint_Circle::floodFill(int x, int y, unsigned char* fillColor)
{
	unsigned char XYPixelColor[4];
	
	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
	
//	cout << "Flood Fill..." << endl;
	
//	cout << "Point RED: " << (int)XYPixelColor[0] << "\tGREEN: " << (int)XYPixelColor[1] << "\tBLUE: " << (int)XYPixelColor[2] << endl;
//	cout << "Background RED: " << (int)Color::BACKGROUND_COLOR[0] << "\tGREEN: " << (int)Color::BACKGROUND_COLOR[1] << "\tBLUE: " << (int)Color::BACKGROUND_COLOR[2] << endl;
	
	if(((int)XYPixelColor[0] == (int)Color::BACKGROUND_COLOR[0] && (int)XYPixelColor[1] == (int)Color::BACKGROUND_COLOR[1] && (int)XYPixelColor[2] == (int)Color::BACKGROUND_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::AXIS_COLOR[0] && (int)XYPixelColor[1] == (int)Color::AXIS_COLOR[1] && (int)XYPixelColor[2] == (int)Color::AXIS_COLOR[2])
	|| ((int)XYPixelColor[0] == (int)Color::GRAY[0] && (int)XYPixelColor[1] == (int)Color::GRAY[1] && (int)XYPixelColor[2] == (int)Color::GRAY[2]))
	{
		glColor3ubv(fillColor);
		glBegin(GL_POINTS);
			glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
		glEnd();
		glFlush();

		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		floodFill(x+1, y, fillColor);	// Right Pixel
		floodFill(x-1, y, fillColor);	// Left Pixel
		glFlush();
		floodFill(x, y+1, fillColor);	// Upper Pixel
		floodFill(x, y-1, fillColor);	// Lower Pixel
//		glFlush();
	}

}

//void MidPoint_Circle::fillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempCoords;
//	bool flag = false;
//	
//	glReadPixels(x, ScreenSizeY - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
////		cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED---------!!!!!!!!!!!!!!!!!!!!" << endl;
//		return;
//	}
////	if((int)XYPixelColor[0] == (int)Color::VIEWPORT_COLOR[0] && (int)XYPixelColor[1] == (int)Color::VIEWPORT_COLOR[1] && (int)XYPixelColor[2] == (int)Color::VIEWPORT_COLOR[2])
////	{
////		cout << "Viewport Hit..." << endl;
////		return;
////	}
//	if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//	{
////		cout << "Boundary Hit..." << endl;
////		getch();
//		return;
//	}
//	
////	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
////	cout << "Coloring Pixel (" << x << ", " << y << ")" << endl;
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(x - ScreenSizeX/2, ScreenSizeY/2 - y);
//	glEnd();
////	glFlush();
//	
////	cout << "Y: " << y << endl;
////	flag = false;
////	glReadPixels(x, ScreenSizeY - y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
////	if((int)XYPixelColor[0] != (int)fillColor[0] && (int)XYPixelColor[1] != (int)fillColor[1] && (int)XYPixelColor[2] != (int)fillColor[2])
////	{
//////		for(stackIterator = customStack.begin(); stackIterator != customStack.end(); stackIterator++)
//////		{
////////			cout << "StackIterator: " << &(*stackIterator) << "\t*StackIterator: " << (*stackIterator) << endl;
//////			if((*stackIterator) == y-1)
//////			{
//////				flag = true;
//////				break;
//////			}
//////		}
//////		if(!flag)
//////		{
////			tempCoords.first = x;
////			tempCoords.second = y-1;
////			customStack.push_back(tempCoords);
////			cout << "Pushed (" << x << ", " << y-1 << ")" << endl << endl;
//////		}
////	}
////	
////	flag = false;
////	glReadPixels(x, ScreenSizeY - y + 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
////	if((int)XYPixelColor[0] != (int)fillColor[0] && (int)XYPixelColor[1] != (int)fillColor[1] && (int)XYPixelColor[2] != (int)fillColor[2])
////	{
//////		for(stackIterator = customStack.begin(); stackIterator != customStack.end(); stackIterator++)
//////		{
////////			cout << "StackIterator: " << stackIterator << "*StackIterator: " << (*stackIterator) << endl;
//////			if((*stackIterator) == y+1)
//////			{
//////				flag = true;
//////				break;
//////			}
//////		}
//////		if(!flag)
//////		{
////			tempCoords.first = x;
////			tempCoords.second = y+1;
////			customStack.push_back(tempCoords);
////			cout << "Pushed (" << x << ", " << y+1 << ")" << endl << endl;
//////		}
////	}
//	
//	fillBoundary(x+1, y, fillColor, selectedObjectColor);
////	cout << "Call 1 ended..." << endl;
//	fillBoundary(x-1, y, fillColor, selectedObjectColor);
//	glFlush();
////	cout << "Call 2 ended..." << endl;
//	fillBoundary(x, y+1, fillColor, selectedObjectColor);
//	fillBoundary(x, y-1, fillColor, selectedObjectColor);
//
////	cout << "Stack Front: " << customStack.front() << endl;
////	x = customStack.back().first;
////	y = customStack.back().second;
////	customStack.pop_back();
//////	cout << "Popped" << endl;
////	cout << "Popped (" << x << ", " << y << ")" << endl;
////	fillBoundary(x, y, fillColor, selectedObjectColor);
//	
////	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	
//	while(true)
//	{
//		while(true)
//		{
//			while(true)
//			{
//				glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//				if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//				{
////					cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////					getch();
//					break;
//				}
//				glBegin(GL_POINTS);
//					glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//				glEnd();
//				glFlush();
//				tempSeed.first++;
//			}
//			tempSeed.first = seed.first;
//			while(true)
//			{
//				glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//				if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//				{
////					cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////					getch();
//					break;
//				}
//				glBegin(GL_POINTS);
//					glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//				glEnd();
//				glFlush();
//				tempSeed.first--;
//			}
//			tempSeed.first = seed.first;
//			tempSeed.second++;
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				tempSeed.second = seed.second;
//				break;
//			}
//		}
//		tempSeed.first = seed.first;
//		tempSeed.second--;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
//			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 4---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	
//	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//	if((int)XYPixelColor[0] == (int)fillColor[0] && (int)XYPixelColor[1] == (int)fillColor[1] && (int)XYPixelColor[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor[0] << "\tG: " << (int)XYPixelColor[1] << "\tB: " << (int)XYPixelColor[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	
//	for(tempSeed.second = seed.second; ; tempSeed.second++)
//	{
//		for(tempSeed.first = seed.first; ; tempSeed.first++)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
////			glFlush();
//		}
//		for(tempSeed.first = seed.first; ; tempSeed.first--)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
//		}
//		glFlush();
//		tempSeed.first = seed.first;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
////			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	for(tempSeed.second = seed.second; ; tempSeed.second--)
//	{
//		for(tempSeed.first = seed.first; ; tempSeed.first++)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
////			glFlush();
//		}
//		for(tempSeed.first = seed.first; ; tempSeed.first--)
//		{
//			glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//			if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//			{
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 2---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
//				break;
//			}
//			glBegin(GL_POINTS);
//				glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//			glEnd();
//		}
//		glFlush();
//		tempSeed.first = seed.first;
//		glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor);
//		if((int)XYPixelColor[0] == (int)selectedObjectColor[0] && (int)XYPixelColor[1] == (int)selectedObjectColor[1] && (int)XYPixelColor[2] == (int)selectedObjectColor[2])
//		{
////			cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 3---------!!!!!!!!!!!!!!!!!!!!" << endl;
////			getch();
//			break;
//		}
//	}
//	
//	glFlush();
//}

//void MidPoint_Circle::fillBoundary(pair<int, int> seed, unsigned char* fillColor, unsigned char* selectedObjectColor)
//{
//	unsigned char XYPixelColor_1[4], XYPixelColor_2[4], XYPixelColor_3[4], XYPixelColor_4[4];
//	pair<int, int> tempSeed = seed;
//	
//	glReadPixels(tempSeed.first, ScreenSizeY - tempSeed.second, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_1);
//	if((int)XYPixelColor_1[0] == (int)fillColor[0] && (int)XYPixelColor_1[1] == (int)fillColor[1] && (int)XYPixelColor_1[2] == (int)fillColor[2])
//	{
//		return;
//	}
//	
//	cout << "Read Pixel: R: " << (int)XYPixelColor_1[0] << "\tG: " << (int)XYPixelColor_1[1] << "\tB: " << (int)XYPixelColor_1[2] << endl;
////	getch();
//	glColor3ubv(fillColor);
//	glBegin(GL_POINTS);
//		glVertex2i(tempSeed.first - ScreenSizeX/2, ScreenSizeY/2 - tempSeed.second);
//	glEnd();
//	glFlush();
//	bool flag1, flag2, flag3, flag4;
//	flag1 = flag2 = flag3 = flag4 = false;
////	for(int y1 = seed.second, y2 = seed.second; ; )
////	for(int y1 = seed.second, y2 = seed.second; ; y1++, y2--)
//	for(int y1 = seed.second; ; y1++)
//	{
//		flag1 = flag2 = false;
//		for(int x1 = seed.first, x2 = seed.first; ; x1++, x2--)
//		{
//			glReadPixels(x1, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_1);
//			glReadPixels(x2, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_2);
//			if((int)XYPixelColor_1[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_1[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_1[2] == (int)selectedObjectColor[2])
//			{
//				flag1 = true;
//			}
//			if((int)XYPixelColor_2[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_2[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_2[2] == (int)selectedObjectColor[2])
//			{
//				flag2 = true;
////				cout << "!!!!!!!!!!!!!!!!!!!!---------COLOR MATCHED 1---------!!!!!!!!!!!!!!!!!!!!" << endl;
////				getch();
////				break;
//			}
//			if(flag1 && flag2)
//			{
//				break;
//			}
//			if(!flag1)
//			{
//				glBegin(GL_POINTS);
//					glVertex2i(x1 - ScreenSizeX/2, ScreenSizeY/2 - y1);
//				glEnd();
//				glFlush();
//			}
//			if(!flag2)
//			{
//				glBegin(GL_POINTS);
//					glVertex2i(x2 - ScreenSizeX/2, ScreenSizeY/2 - y1);
//				glEnd();
//				glFlush();
//			}
//		}
////		glFlush();
////		tempSeed.first = seed.first;
//		glReadPixels(seed.first, ScreenSizeY - y1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, XYPixelColor_3);
//		if((int)XYPixelColor_3[0] == (int)selectedObjectColor[0] && (int)XYPixelColor_3[1] == (int)selectedObjectColor[1] && (int)XYPixelColor_3[2] == (int)selectedObjectColor[2])
//		{
//			break;
//		}
//	}
//	
//	glFlush();
//	
//	cout << "Exiting Filling..." << endl;
//}
>>>>>>> 39796d7880b44149153aa64f8eadc9dcf0d63da9
