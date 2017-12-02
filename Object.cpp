#include <bits/stdc++.h>
#include <math.h>
#include "circle.h"
#include "color.h"
#include "axis.h"
#include "thickness.h"
#include "viewport.h"

void Object::translate(int dx, int dy)
{
	erasePreviousObject();
	Axis::drawAxis();

	if(this->shapeID >= 1 && this->shapeID <= 4)
	{
		startCoords.first += dx;
		startCoords.second += dy;
		endCoords.first += dx;
		endCoords.second += dy;
	}
//	else if(this->shapeID == 5 || this->shapeID == 6)
	else if(this->shapeID == 7 || this->shapeID == 8)
	{
		centerX += dx;
		centerY += dy;
		clickedRadiusX += dx;
		clickedRadiusY += dy;
	}
	
	if((Circle*)this->isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			(*it).first += dx;
			(*it).second += dy;
		}
	}

	if((Circle*)this->isFilled)
	{
		for(list< pair<int, int> >::iterator it = filledCoords.begin(); it != filledCoords.end(); it++)
		{
			(*it).first += dx;
			(*it).second += dy;
		}
	}

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

void Object::rotate(int rotAngleDeg, pair<int, int> pivot)
{
	
}

void Object::scale(float scaleFactor, pair<int, int> pivot)
{
	
}
