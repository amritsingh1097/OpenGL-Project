#include <math.h>
#include "b_spline.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

B_Spline::B_Spline(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 6;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->numKnotCoords = 0;
	this->numCurveCoords = 1000;
	this->isDrawn = false;
	this->objectName = (char*)"B_Spline Curve";
}

void B_Spline::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int B_Spline::getShapeID()
{
	return shapeID;
}

int B_Spline::computeBlendingFunc(float u, int k, int degree)
{
	float blendingFunc;
	int i;
	list< pair<int, int> >::iterator it;
	it = knotVector.begin();
	
	knotArrayX = new int[knotVector.size()];
	knotArrayY = new int[knotVector.size()];
	
	i = 0;
	for(it = knotVector.begin(); it != knotVector.end(); it++, i++)
	{
		knotArrayX[i] = (*it).first;
		knotArrayY[i] = (*it).second;
	}
	
	if((knotArrayX[k] < u && u <= knotArrayX[k+1]) || (knotArrayX[k] < u && u <= knotArrayX[k+1]))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	blendingFunc = (((u - knotArrayX[k]) / (knotArrayX[k+degree-1] - knotArrayX[k])) * computeBlendingFunc(u, k, degree-1))
				 + (((knotArrayX[k+degree] - u) / (knotArrayX[k+degree] - knotArrayX[k+1])) * computeBlendingFunc(u, k+1, degree-1));
				 
	cout << "Blending Function: " << blendingFunc << endl;
	return blendingFunc;
}

void B_Spline::computeCurveCoords(float u)
{
	float blendingFunc;
	int x, y;
	list< pair<int, int> >::iterator knotCoordsIt;
	knotCoordsIt = knotVector.begin();
	
//	cout << "Calaulating Bezier Curve Points..." << endl;
	x = y = 0;
	for(int k=0; k < numKnotCoords; k++)
	{
		blendingFunc = computeBlendingFunc(u, k, degree);
//		cout << "Blending Function: " << blendingFunc << endl;
		x += round((*knotCoordsIt).first * blendingFunc);
		y += round((*knotCoordsIt).second * blendingFunc);
//		cout << "X: " << x << "\tY: " << y << endl;
		knotCoordsIt++;
	}
	if(Coords.back().first != x && Coords.back().second != y)
	{
//		glBegin(GL_POINTS);
//		glVertex2i(x, y);
//		glEnd();
//		glFlush();
		cout << "X: " << x << "\tY: " << y << endl;
		Coords.push_back(make_pair(x, y));
	}
}

void B_Spline::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
//	pair<int, int> currCoords;
//	int x, y;
	
//	startCoords.first = XCoord1;
//	startCoords.second = YCoord1;
//	endCoords.first = XCoord2;
//	endCoords.second = YCoord2;
	
//	x = XCoord1;
//	y = YCoord1;
	
	
	glColor3ubv(Color::BLACK);
//	glBegin(GL_POINTS);
//	glVertex2i(x, y);
//	
//	currCoords.first = x;
//	currCoords.second = y;
//	Coords.push_back(currCoords);
	
//	glEnd();
//	glFlush();

	cout << "Going in for loop..." << endl;
//	cout << "Curve Coords: " << numCurveCoords << endl;
	for(float k = 0.0; k <= 1.0; k+=0.0001)
	{
//		u = (float)k / (float)numCurveCoords;
		computeCurveCoords(k);
	}
	
	cout << "Out of for loop..." << endl;


	
//	if(viewport->ViewportPresent)	redrawAllObjects();
}

void B_Spline::addKnotCoords(pair<int, int> knotCoord)
{
	numKnotCoords++;
	degree = numKnotCoords - 1;
	if(knotVector.size() >= 2)
	{
		pair<int, int> tempCoord;
		tempCoord = knotVector.back();
		knotVector.pop_back();
		knotVector.push_back(knotCoord);
		knotVector.push_back(tempCoord);
		cout << "Front: (" << knotVector.front().first << ", " << knotVector.front().second << ")" << endl;
		cout << "Back: (" << knotVector.back().first << ", " << knotVector.back().second << ")" << endl;
	}
	if(knotVector.size() == 0)
	{
		startCoords = knotCoord;
		knotVector.push_back(startCoords);
		cout << "Start: (" << startCoords.first << ", " << startCoords.second << ")" << endl;
		return;
	}
	if(knotVector.size() == 1)
	{
		endCoords = knotCoord;
		knotVector.push_back(endCoords);
		cout << "End: (" << endCoords.first << ", " << endCoords.second << ")" << endl;
//		return;
	}
//	printCoords();
	Coords.clear();
	draw(this->startCoords.first, this->startCoords.second, this->endCoords.first, this->endCoords.second);
	redrawAllObjects();
}

bool B_Spline::selectObject(pair<int, int> clickedCoords)
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

void B_Spline::translate(int dx, int dy)
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
	
	selectedCoords.first += dx;
	selectedCoords.second += dy;
	
	redrawAllObjects();
}

void B_Spline::rotate(int rotAngleDeg, pair<int, int> pivot)
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
	
	Coords.clear();
	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);

	tempX = selectedCoords.first;
	tempY = selectedCoords.second;
	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
	
	redrawAllObjects();
}

void B_Spline::scale(float scaleFactor, pair<int, int> pivot)
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
	
	cout << "Clearing Coords..." << endl;
	Coords.clear();
	cout << "Calling Draw..." << endl;
	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);
	cout << "Exited Draw..." << endl;
//	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
//	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
	
	redrawAllObjects();
}

void B_Spline::setPattern(string pattern)
{
	this->pattern = pattern;
}

void B_Spline::setThickness(int thickness)
{
	this->thickness = thickness;
}

void B_Spline::setColor(unsigned char *color)
{
	this->color = color;
}

void B_Spline::erasePreviousObject()
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

void B_Spline::redrawSelectedObject(unsigned char* color, int thickness)
{
	glColor3ubv(color);
	glPointSize(thickness);
	
	bool clipped = false;
	pair<int, int> start, end;
	list< pair<int, int> >::iterator it;
	it = Coords.begin();
	
	start = startCoords;
	end = endCoords;
	
//	cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
	if(viewport->ViewportPresent)
	{
		clipped = viewport->clipLine(&start, &end);
//		cout << "Fully Clipped: " << !clipped << endl;
		if(!clipped)	return;
	
//		cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
		while(true)
		{
			if((*it).first == start.first && (*it).second == start.second)	break;
			if((*it).first - start.first >= -1 && (*it).first - start.first <= 1 && (*it).second - start.second >= -1 && (*it).second - start.second <= 1)	break;
			it++;
		}
		it++;
	}
	
//	cout << "Starting From X: " << (*it).first << "\tY: " << (*it).second << endl;
//	cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
	
	glBegin(GL_POINTS);
		for(it; it != Coords.end(); it++)
		{
//			cout << "Points X: " << (*it).first << "\tY: " << (*it).second << endl;
//			if((*it).first != start.first && (*it).second != start.second && flag)	continue;
			patternIndex %= 4;
			if(pattern[patternIndex] == '1')
			{
				glVertex2i((*it).first, (*it).second);
			}
			patternIndex++;
			if((*it).first == end.first && (*it).second == end.second)	break;
			if((*it).first - end.first >= -1 && (*it).first - end.first <= 1 && (*it).second - end.second >= -1 && (*it).second - end.second <= 1)	break;
		}
	glEnd();
	glFlush();
}

void B_Spline::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void B_Spline::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void B_Spline::floodFill(int x, int y, unsigned char* fillColor)
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
