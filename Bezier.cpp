#include <math.h>
#include "bezier.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

Bezier::Bezier(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 5;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->numControlCoords = 0;
	this->numCurveCoords = 1000;
	this->isDrawn = false;
	this->objectName = (char*)"Bezier Curve";
}

void Bezier::printCoords()
{
	list< pair<int,int> >::iterator it;
	cout << "Printing Coordinates..." << endl;
	for(it = Coords.begin(); it != Coords.end(); it++)
	{
		cout<<"\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int Bezier::getShapeID()
{
	return shapeID;
}

inline int Bezier::factorial(int num)
{
	int fact = 1;
	for(int i = 1; i <= num; i++)
		fact = fact * i;
		
//	cout << "Factorial of " << num << " is: " << fact << endl;
//	getch();
	return fact;
}

inline void Bezier::computeCoeffs()
{
	for(int k=0; k < numControlCoords; k++)
	{
		Coeffs.push_back(factorial((float)numControlCoords-(float)1) / (factorial((float)k) * factorial((float)numControlCoords-(float)k-(float)1)));
	}
}

void Bezier::computeCurveCoords(float u)
{
	float blendingFunc;
	int x, y;
	list<float>::iterator coeffsIt;
	list< pair<int, int> >::iterator controlCoordsIt;
	coeffsIt = Coeffs.begin();
	controlCoordsIt = controlCoords.begin();
	
//	cout << "Calaulating Bezier Curve Points..." << endl;
	x = y = 0;
	for(int k=0; k < numControlCoords; k++)
	{
//		cout << "Coeff[" << k << "] : " << (*coeffsIt) << endl;
		blendingFunc = (*coeffsIt) * pow(u, k) * pow(1-u, numControlCoords-k-1);
//		cout << "Blending Function: " << blendingFunc << endl;
		x += round((*controlCoordsIt).first * blendingFunc);
		y += round((*controlCoordsIt).second * blendingFunc);
//		cout << "X: " << x << "\tY: " << y << endl;
		coeffsIt++;
		controlCoordsIt++;
	}
	if(Coords.back().first != x && Coords.back().second != y)
	{
//		glBegin(GL_POINTS);
//		glVertex2i(x, y);
//		glEnd();
//		glFlush();
//		cout << "X: " << x << "\tY: " << y << endl;
		Coords.push_back(make_pair(x, y));
	}
}

void Bezier::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	pair<int, int> currCoords;
	int x, y;
	float u;
	int blendingFunc;
	
//	startCoords.first = XCoord1;
//	startCoords.second = YCoord1;
//	endCoords.first = XCoord2;
//	endCoords.second = YCoord2;
	
//	x = XCoord1;
//	y = YCoord1;
	
	
//	controlCoords.push_back(make_pair(startCoords.first, startCoords.second));
//	numControlPoints++;
//	controlCoords.push_back(make_pair(endCoords.first, endCoords.second));
//	numControlPoints++;
	
	glColor3ubv(Color::BLACK);
//	if(!numControlPoints)
//	{
//		glBegin(GL_LINES);
//			glVertex2i(startCoords.first, startCoords.second);
//			glVertex2i(endCoords.first, endCoords.second);
//		glEnd();
//		glFlush();
//		return;
//	}
	
//	glBegin(GL_POINTS);
//	glVertex2i(x, y);
	
//	currCoords.first = x;
//	currCoords.second = y;
//	Coords.push_back(currCoords);
	
	computeCoeffs();
	cout << "Going in for loop..." << endl;
//	cout << "Curve Coords: " << numCurveCoords << endl;
	for(float k = 0.0; k <= 1.0; k+=0.0001)
	{
//		u = (float)k / (float)numCurveCoords;
		computeCurveCoords(k);
	}
	
	cout << "Out of for loop..." << endl;
	
	
	
//	glEnd();
//	glFlush();
	
//	printCoords();
	
//	if(viewport->ViewportPresent)	redrawAllObjects();
}

void Bezier::addControlCoords(pair<int, int> controlCoord)
{
	numControlCoords++;
	if(controlCoords.size() >= 2)
	{
		pair<int, int> tempCoord;
		tempCoord = controlCoords.back();
		controlCoords.pop_back();
		controlCoords.push_back(controlCoord);
		controlCoords.push_back(tempCoord);
		cout << "Front: (" << controlCoords.front().first << ", " << controlCoords.front().second << ")" << endl;
		cout << "Back: (" << controlCoords.back().first << ", " << controlCoords.back().second << ")" << endl;
	}
	if(controlCoords.size() == 0)
	{
		startCoords = controlCoord;
		controlCoords.push_back(startCoords);
		cout << "Start: (" << startCoords.first << ", " << startCoords.second << ")" << endl;
		return;
	}
	if(controlCoords.size() == 1)
	{
		endCoords = controlCoord;
		controlCoords.push_back(endCoords);
		cout << "End: (" << endCoords.first << ", " << endCoords.second << ")" << endl;
//		return;
	}
	printCoords();
	Coeffs.clear();
	Coords.clear();
	draw(this->startCoords.first, this->startCoords.second, this->endCoords.first, this->endCoords.second);
	redrawAllObjects();
}

bool Bezier::selectObject(pair<int, int> clickedCoords)
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

void Bezier::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	startCoords.first += dx;
	startCoords.second += dy;
	endCoords.first += dx;
	endCoords.second += dy;
	
	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
	for(list< pair<int, int> >::iterator it = controlCoords.begin(); it != controlCoords.end(); it++)
	{
		(*it).first += dx;
		(*it).second += dy;
	}
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
	
	redrawAllObjects();
}

void Bezier::rotate(int rotAngleDeg, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	const float PI = 3.14159;
	float sinTheeta;
	float cosTheeta;
	float rotAngleRad = (float)rotAngleDeg * (PI / (float)180);
	float tempX, tempY;
	float pivotX, pivotY;
	
	pivotX = pivot.first;
	pivotY = pivot.second;
	
	sinTheeta = sin(rotAngleRad);
	cosTheeta = cos(rotAngleRad);
	
	tempX = startCoords.first;
	tempY = startCoords.second;
	startCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	startCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));

	tempX = endCoords.first;
	tempY = endCoords.second;
	endCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	endCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	// Scaling Control Coordinates
	for(list< pair<int, int> >::iterator it = controlCoords.begin(); it != controlCoords.end(); it++)
	{
		tempX = (*it).first;
		tempY = (*it).second;
		(*it).first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
		(*it).second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	}
	
	Coords.clear();
	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);

	tempX = selectedCoords.first;
	tempY = selectedCoords.second;
	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	redrawAllObjects();
}

void Bezier::scale(float scaleFactor, pair<int, int> pivot)
{
	erasePreviousObject();
	Axis::drawAxis();
	
	pivot.first = selectedCoords.first;
	pivot.second = selectedCoords.second;
	
	cout << "Scaling Start Coords..." << endl;
	startCoords.first = round(((float)startCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	startCoords.second = round(((float)startCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	cout << "Scaling End Coords..." << endl;
	endCoords.first = round(((float)endCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
	endCoords.second = round(((float)endCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	// Scaling Control Coordinates
	for(list< pair<int, int> >::iterator it = controlCoords.begin(); it != controlCoords.end(); it++)
	{
		(*it).first = round(((float)(*it).first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
		(*it).second = round(((float)(*it).second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	}
	
	cout << "Clearing Coords..." << endl;
	Coords.clear();
	cout << "Calling Draw..." << endl;
	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);
	cout << "Exited Draw..." << endl;
//	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
//	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	redrawAllObjects();
}

void Bezier::setPattern(string pattern)
{
	this->pattern = pattern;
}

void Bezier::setThickness(int thickness)
{
	this->thickness = thickness;
}

void Bezier::setColor(unsigned char *color)
{
	this->color = color;
}

void Bezier::erasePreviousObject()
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

void Bezier::redrawSelectedObject(unsigned char* color, int thickness)
{
	glColor3ubv(color);
//	glPointSize(thickness);
//	glEnable(GL_POINT_SMOOTH);
	
	// Redrawing Control Points -----------------------------
	glPointSize(2);
	glBegin(GL_POINTS);
		for(list< pair<int, int> >::iterator it = controlCoords.begin(); it != controlCoords.end(); it++)
		{
			glVertex2i((*it).first, (*it).second);
		}
	glEnd();
	glPointSize(thickness);
	
	// Control Points Redrawn -------------------------------

//	cout << "Starting From X: " << (*it).first << "\tY: " << (*it).second << endl;
//	cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
	
	
	list< pair<int, int> >::iterator it;
	glBegin(GL_LINES);
		for(it = Coords.begin(); it != Coords.end(); it++)
		{
			patternIndex %= 4;
			if(pattern[patternIndex] == '1' && !viewport->isClipped((*it).first, (*it).second))
			{
				glVertex2i((*it).first, (*it).second);
				it++;
				if(it == Coords.end())	break;
				glVertex2i((*it).first, (*it).second);
				it--;
			}
			patternIndex++;
		}
		
	glEnd();
	glFlush();
//	glDisable(GL_POINT_SMOOTH);
}

void Bezier::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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
//		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		fourFillBoundary(x+1, y, fillColor, selectedObjectColor);	// Right Pixel
		fourFillBoundary(x-1, y, fillColor, selectedObjectColor);	// Left Pixel
		glFlush();
		fourFillBoundary(x, y+1, fillColor, selectedObjectColor);	// Upper Pixel
		fourFillBoundary(x, y-1, fillColor, selectedObjectColor);	// Lower Pixel
//		glFlush();
	}

}

void Bezier::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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
//		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		eightFillBoundary(x+1, y, fillColor, selectedObjectColor);	// Right Pixel
		eightFillBoundary(x-1, y, fillColor, selectedObjectColor);	// Left Pixel
		glFlush();
		eightFillBoundary(x, y+1, fillColor, selectedObjectColor);	// Upper Pixel
		eightFillBoundary(x, y-1, fillColor, selectedObjectColor);	// Lower Pixel

		eightFillBoundary(x-1, y+1, fillColor, selectedObjectColor);	// Upper Left Pixel
		eightFillBoundary(x+1, y+1, fillColor, selectedObjectColor);	// Upper Right Pixel
		eightFillBoundary(x+1, y-1, fillColor, selectedObjectColor);	// Lower Right Pixel
		eightFillBoundary(x-1, y-1, fillColor, selectedObjectColor);	// Lower Left Pixel
//		glFlush();
	}

}

void Bezier::floodFill(int x, int y, unsigned char* fillColor)
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

//		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));
		
		floodFill(x+1, y, fillColor);	// Right Pixel
		floodFill(x-1, y, fillColor);	// Left Pixel
		glFlush();
		floodFill(x, y+1, fillColor);	// Upper Pixel
		floodFill(x, y-1, fillColor);	// Lower Pixel
//		glFlush();
	}

}
