#include <math.h>
#include "mid_pointlda.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void mask(unsigned char*, int x, int y);
extern void redrawAllObjects();

Mid_PointLDA::Mid_PointLDA(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 4;
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

int Mid_PointLDA::getShapeID()
{
	return shapeID;
}

void Mid_PointLDA::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	pair<int, int> currCoords;
	int dx, dy;
	int x, y, steps;
	
	startCoords.first = XCoord1;
	startCoords.second = YCoord1;
	endCoords.first = XCoord2;
	endCoords.second = YCoord2;
	
	x = XCoord1;
	y = YCoord1;
	dx = abs(XCoord2 - XCoord1);
	dy = abs(YCoord2 - YCoord1);
	
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
		slopeLT1(XCoord1, YCoord1, XCoord2, YCoord2, steps, x, y, dx, dy);
	}
	else
	{
		slopeGT1(XCoord1, YCoord1, XCoord2, YCoord2, steps, x, y, dx, dy);
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
	
	startCoords.first += dx;
	startCoords.second += dy;
	endCoords.first += dx;
	endCoords.second += dy;
	
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

void Mid_PointLDA::rotate(int rotAngleDeg, pair<int, int> pivot)
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

void Mid_PointLDA::scale(float scaleFactor, pair<int, int> pivot)
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
	
	redrawAllObjects();
//	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
//	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
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
//				mask(color, (*it).first, (*it).second);
			}
			patternIndex++;
			if((*it).first == end.first && (*it).second == end.second)	break;
			if((*it).first - end.first >= -1 && (*it).first - end.first <= 1 && (*it).second - end.second >= -1 && (*it).second - end.second <= 1)	break;
		}
	glEnd();
	glFlush();
}

void Mid_PointLDA::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void Mid_PointLDA::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void Mid_PointLDA::fourFloodFill(int x, int y, unsigned char* fillColor)
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
		
		fourFloodFill(x+1, y, fillColor);	// Right Pixel
		fourFloodFill(x-1, y, fillColor);	// Left Pixel
		glFlush();
		fourFloodFill(x, y+1, fillColor);	// Upper Pixel
		fourFloodFill(x, y-1, fillColor);	// Lower Pixel
//		glFlush();
	}

}

void Mid_PointLDA::eightFloodFill(int x, int y, unsigned char* fillColor)
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

		eightFloodFill(x+1, y, fillColor);	// Right Pixel
		eightFloodFill(x-1, y, fillColor);	// Left Pixel
		eightFloodFill(x, y+1, fillColor);	// Upper Pixel
		eightFloodFill(x, y-1, fillColor);	// Lower Pixel
		glFlush();
		eightFloodFill(x-1, y+1, fillColor);	// Upper Left Pixel
		eightFloodFill(x+1, y+1, fillColor);	// Upper Right Pixel
		eightFloodFill(x+1, y-1, fillColor);	// Lower Right Pixel
		eightFloodFill(x-1, y-1, fillColor);	// Lower Left Pixel
//		glFlush();
	}

}
