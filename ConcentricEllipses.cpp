#include <math.h>
#include "concentricellipses.h"
#include "randomcolor.h"
#include "color.h"
#include "axis.h"
#include "ellipse.h"
#include "thickness.h"
#include "pattern.h"
#include "viewport.h"

extern int ScreenSizeX, ScreenSizeY;
extern list<Object*> objectList;
extern Viewport *viewport;
extern pair<int, int> selectedCoords;

extern void redrawAllObjects();

ConcentricEllipses::ConcentricEllipses(unsigned char* color, int thickness, string pattern)
{
	this->shapeID = 9;
	this->color = color;
	this->thickness = thickness;
	this->pattern = pattern;
	this->patternIndex = 0;
	this->numEllipses = 5;
	this->objectName = (char*)"ConcentricEllipses Shape";
}

void ConcentricEllipses::printCoords()
{
	list< pair<int,int> >::iterator it;
	for(it = Coords.begin(); it != Coords.end();it++)
	{
		cout<<"\n\tCoordinates: ("<<(*it).first<<","<<(*it).second<<")"<<endl;
	}
}

int ConcentricEllipses::getShapeID()
{
	return shapeID;
}

void ConcentricEllipses::draw(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	RandomColor *randomColor = new RandomColor();
	randomColor->set_timer_seed();
	for(int i=0; i<numEllipses; i++)
	{
		startCoords.push_back(make_pair(XCoord1, YCoord1));
		endCoords.push_back(make_pair(XCoord2, YCoord2));
		MidPoint_Ellipse *ellipse = new MidPoint_Ellipse(randomColor->draw_random_color(), Thickness::THICKNESS_1, Pattern::HEX_F);
		glutSetWindowTitle(ellipse->objectName);
		ellipse->draw(XCoord1, YCoord1, XCoord2, YCoord2);
		ellipses.push_back(ellipse);
		XCoord2 += 20;
		YCoord2 += 20;
	}
	
	list< MidPoint_Ellipse* >::iterator it;// = ellipses.begin();
//	it++;
	
	for(it = ellipses.begin(); it != ellipses.end(); it++)
	{
		cout << "RadiusY: " << (*it)->endY << endl;
		cout << "New RadiusY: " << ScreenSizeY - (ScreenSizeY/2) - (*it)->endY + 1 << endl;
		fourFloodFill((*it)->centerX + ScreenSizeX/2, (ScreenSizeY/2) - (*it)->endY + 1, randomColor->draw_random_color());
	}
	
}

bool ConcentricEllipses::selectObject(pair<int, int> clickedCoords)
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

void ConcentricEllipses::translate(int dx, int dy)
{
//	erasePreviousObject();
//	Axis::drawAxis();
//
//	startCoords.first += dx;
//	startCoords.second += dy;
//	endCoords.first += dx;
//	endCoords.second += dy;
//
//	for(list< pair<int, int> >::iterator it = Coords.begin(); it != Coords.end(); it++)
//	{
//		(*it).first += dx;
//		(*it).second += dy;
//	}
//
////	for(list<Object*>::iterator it = objectList.begin(); it != objectList.end(); it++)
////	{
////		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
////	}
//
//	selectedCoords.first += dx;
//	selectedCoords.second += dy;
//
//	redrawAllObjects();
}

void ConcentricEllipses::rotate(int rotAngleDeg, pair<int, int> pivot)
{
//	erasePreviousObject();
//	Axis::drawAxis();
//
//	const float PI = 3.14159;
//	float sinTheeta;
//	float cosTheeta;
//	float rotAngleRad = (float)rotAngleDeg * (PI / (float)180);
//	float tempX, tempY;
//	float pivotX, pivotY;
//
//	pivotX = pivot.first;
//	pivotY = pivot.second;
//
//	sinTheeta = sin(rotAngleRad);
//	cosTheeta = cos(rotAngleRad);
//
//	tempX = startCoords.first;
//	tempY = startCoords.second;
//	startCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
//	startCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
//
//	tempX = endCoords.first;
//	tempY = endCoords.second;
//	endCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
//	endCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
//
//	Coords.clear();
//	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);
//
//	tempX = selectedCoords.first;
//	tempY = selectedCoords.second;
//	selectedCoords.first = pivot.first + round(((tempX - pivotX) * cosTheeta) - ((tempY - pivotY) * sinTheeta));
//	selectedCoords.second = pivot.second + round(((tempX - pivotX) * sinTheeta) + ((tempY - pivotY) * cosTheeta));
//
//	redrawAllObjects();
}

void ConcentricEllipses::scale(float scaleFactor, pair<int, int> pivot)
{
//	erasePreviousObject();
//	Axis::drawAxis();
//
//	pivot.first = selectedCoords.first;
//	pivot.second = selectedCoords.second;
//
//	cout << "Scaling Start Coords..." << endl;
//	startCoords.first = round(((float)startCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
//	startCoords.second = round(((float)startCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
//
//	cout << "Scaling End Coords..." << endl;
//	endCoords.first = round(((float)endCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
//	endCoords.second = round(((float)endCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
//
//	cout << "Clearing Coords..." << endl;
//	Coords.clear();
//	cout << "Calling Draw..." << endl;
//	draw(startCoords.first, startCoords.second, endCoords.first, endCoords.second);
//	cout << "Exited Draw..." << endl;
////	selectedCoords.first = round(((float)selectedCoords.first * scaleFactor) + ((float)pivot.first - ((float)pivot.first * scaleFactor)));
////	selectedCoords.second = round(((float)selectedCoords.second * scaleFactor) + ((float)pivot.second - ((float)pivot.second * scaleFactor)));
//
//	redrawAllObjects();
}

void ConcentricEllipses::setPattern(string pattern)
{
	this->pattern = pattern;
}

void ConcentricEllipses::setThickness(int thickness)
{
	this->thickness = thickness;
}

void ConcentricEllipses::setColor(unsigned char *color)
{
	this->color = color;
}

void ConcentricEllipses::erasePreviousObject()
{
//	list< pair<int, int> >::iterator it;
//	glColor3ubv(Color::BACKGROUND_COLOR);
//
//	glPointSize(3);
//	glBegin(GL_POINTS);
//
//	it = Coords.begin();
//
//		glVertex2i((*it).first, (*it).second);
//
//	it = Coords.end();
//	it--;
//
//		glVertex2i((*it).first, (*it).second);
//	glEnd();
//	glPointSize(1);
//
//	glBegin(GL_POINTS);
//	for(it = Coords.begin(); it != Coords.end(); it++)
//	{
//		glVertex2i((*it).first, (*it).second);
//	}
//	glEnd();
//	glFlush();
}

void ConcentricEllipses::redrawSelectedObject(unsigned char* color, int thickness)
{
//	glColor3ubv(color);
//	glPointSize(thickness);
//
//	bool clipped = false;
//	pair<int, int> start, end;
//	list< pair<int, int> >::iterator it;
//	it = Coords.begin();
//
//	start = startCoords;
//	end = endCoords;
//
////	cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
//	if(viewport->ViewportPresent)
//	{
//		clipped = viewport->clipLine(&start, &end);
////		cout << "Fully Clipped: " << !clipped << endl;
//		if(!clipped)	return;
//
////		cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
//		while(true)
//		{
//			if((*it).first == start.first && (*it).second == start.second)	break;
//			if((*it).first - start.first >= -1 && (*it).first - start.first <= 1 && (*it).second - start.second >= -1 && (*it).second - start.second <= 1)	break;
//			it++;
//		}
//		it++;
//	}
//
////	cout << "Starting From X: " << (*it).first << "\tY: " << (*it).second << endl;
////	cout << "StartX: " << start.first << "\tStartY: " << start.second << "\tEndX: " << end.first << "\tEndY: " << end.second << endl;
//
//	glBegin(GL_POINTS);
//		for(it; it != Coords.end(); it++)
//		{
////			cout << "Points X: " << (*it).first << "\tY: " << (*it).second << endl;
////			if((*it).first != start.first && (*it).second != start.second && flag)	continue;
//			patternIndex %= 4;
//			if(pattern[patternIndex] == '1')
//			{
//				glVertex2i((*it).first, (*it).second);
//			}
//			patternIndex++;
//			if((*it).first == end.first && (*it).second == end.second)	break;
//			if((*it).first - end.first >= -1 && (*it).first - end.first <= 1 && (*it).second - end.second >= -1 && (*it).second - end.second <= 1)	break;
//		}
//	glEnd();
//	glFlush();
}

void ConcentricEllipses::fourFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void ConcentricEllipses::eightFillBoundary(int x, int y, unsigned char* fillColor, unsigned char* selectedObjectColor)
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

void ConcentricEllipses::fourFloodFill(int x, int y, unsigned char* fillColor)
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
//		glFlush();

//		filledCoords.push_back(make_pair(x - ScreenSizeX/2, ScreenSizeY/2 - y));

		fourFloodFill(x+1, y, fillColor);	// Right Pixel
		fourFloodFill(x-1, y, fillColor);	// Left Pixel
		glFlush();
		fourFloodFill(x, y+1, fillColor);	// Upper Pixel
		fourFloodFill(x, y-1, fillColor);	// Lower Pixel
//		glFlush();
	}

}

void ConcentricEllipses::eightFloodFill(int x, int y, unsigned char* fillColor)
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
//		glFlush();

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
