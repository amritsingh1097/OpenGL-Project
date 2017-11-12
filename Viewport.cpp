#include "viewport.h"
#include "color.h"
using namespace std;

extern int ScreenSizeX, ScreenSizeY;

Viewport::Viewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	setViewport(XCoord1, YCoord1, XCoord2, YCoord2);
//	this->XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
//	this->YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
//	this->XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
//	this->YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
}

void Viewport::printCoords()
{
//	cout << "XMIN: " << XMin << "\tYMIN: " << YMin << "\tXMAX: " << XMax << "\tYMAX: " << YMax << endl;
}

void Viewport::setViewport(int XCoord1, int YCoord1, int XCoord2, int YCoord2)
{
	this->XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
	this->YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
	this->XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
	this->YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
}

void Viewport::drawViewport(/*int XCoord1, int YCoord1, int XCoord2, int YCoord2*/)
{
//	XMin = (XCoord1 > XCoord2) ? XCoord2 : XCoord1;
//	YMin = (YCoord1 > YCoord2) ? YCoord2 : YCoord1;
//	XMax = (XCoord1 > XCoord2) ? XCoord1 : XCoord2;
//	YMax = (YCoord1 > YCoord2) ? YCoord1 : YCoord2;
	
	glColor3ubv(Color::VIEWPORT_COLOR);
	glBegin(GL_LINES);
		glVertex2i(XMin, YMin);
		glVertex2i(XMax, YMin);
		glVertex2i(XMin, YMin);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMin);
		glVertex2i(XMax, YMax);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMax);
	glEnd();
	glFlush();
}

void Viewport::removeViewport()
{
	
	XMin = -ScreenSizeX/2;
	YMin = -ScreenSizeY/2;
	XMax = ScreenSizeX/2;
	YMax = ScreenSizeY/2;
	
	glColor3ubv(Color::VIEWPORT_COLOR);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2i(XMin, YMin);
		glVertex2i(XMax, YMin);
		glVertex2i(XMin, YMin);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMin);
		glVertex2i(XMax, YMax);
		glVertex2i(XMin, YMax);
		glVertex2i(XMax, YMax);
	glEnd();
	glFlush();
	glLineWidth(2);
}

bool Viewport::isClipped(int XCoord, int YCoord)
{
//	cout << "XMIN: " << XMin << "\tYMIN: " << YMin << "\tXMAX: " << XMax << "\tYMAX: " << YMax << endl;
	if((XCoord > XMin && XCoord < XMax) && (YCoord > YMin && YCoord < YMax))	return false;
	return true;
}

// Line Clipping Code Goes Here...
bool Viewport::clipLine(pair<int, int>* start, pair<int, int>* end)
{
	int dx, dy;
	int P1, P2, P3, P4, Q1, Q2, Q3, Q4;
	float R1, R2, R3, R4, U1, U2;
	float temp;
	int x1, y1, x2, y2;
	
	cout << "\n\nXMin: " << XMin << "\tYMin: " << YMin << "\tXMax: " << XMax << "\tYMax: " << YMax << endl;
	
	x1 = start->first;
	y1 = start->second;
	x2 = end->first;
	y2 = end->second;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	P1 = -dx;
	P2 = dx;
	P3 = -dy;
	P4 = dy;
	
	Q1 = x1 - XMin;
	Q2 = XMax - x1;
	Q3 = y1 - YMin;
	Q4 = YMax - y1;
	
	cout << "P1: " << P1 << "\tP2: " << P2 << "\tP3: " << P3 << "\tP4: " << P4 << endl;
	cout << "Q1: " << Q1 << "\tQ2: " << Q2 << "\tQ3: " << Q3 << "\tQ4: " << Q4 << endl;
	
	// Vertical line
	if(P1 == 0 && P2 == 0 && (Q1 < 0 || Q2 < 0))
	{
		cout << "P1-P2 Case" << endl;
		cout << "Full Line Clipped" << endl;
		return false;
	}
	
	// Horizontal Line
	if(P3 == 0 && P4 == 0 && (Q3 < 0 || Q4 < 0))
	{
		cout << "P3-P4 Case" << endl;
		cout << "Full Line Clipped" << endl;
		return false;
	}
	
	// Calculating values of R
	if(P1 < 0 && P3 < 0)
	{
		cout << "IF: (P1 - P3)" << endl;
		R1 = (float)Q1 / (float)P1;
		R2 = (float)Q3 / (float)P3;
		
		cout << "R1: " << R1 << "\tR2: " << R2 << endl;
		
		// Minimum of R values
		temp = (R1 > R2) ? R1 : R2;
		U1 = (temp > 0) ? temp : 0;
		cout << "U1: " << U1 << endl;
	}
	else if(P1 >= 0 && P3 >= 0)
	{
		cout << "ELSE: (P1 - P3)" << endl;
		R3 = (float)Q1 / (float)P1;
		R4 = (float)Q3 / (float)P3;
		
		cout << "R3: " << R3 << "\tR4: " << R4 << endl;
		
		// Minimum of R values
		temp = (R3 > R4) ? R4 : R3;
		U2 = (temp > 1) ? 1 : temp;
		cout << "U2: " << U2 << endl;
	}
	
	// Calculating values of R
	if(P2 < 0 && P4 < 0)
	{
		cout << "IF: (P2 - P4)" << endl;
		R1 = (float)Q2 / (float)P2;
		R2 = (float)Q4 / (float)P4;
		
		cout << "R1: " << R1 << "\tR2: " << R2 << endl;
		
		// Minimum of R values
		temp = (R1 > R2) ? R1 : R2;
		U1 = (temp > 0) ? temp : 0;
		cout << "U1: " << U1 << endl;
	}
	else if(P2 >= 0 && P4 >= 0)
	{
		cout << "ELSE: (P2 - P4)" << endl;
		R3 = (float)Q2 / (float)P2;
		R4 = (float)Q4 / (float)P4;
		
		cout << "R3: " << R3 << "\tR4: " << R4 << endl;
		
		// Minimum of R values
		temp = (R3 > R4) ? R4 : R3;
		U2 = (temp > 1) ? 1 : temp;
		cout << "U2: " << U2 << endl;
	}
	
	// Calculating values of R
	if(P1 < 0 && P4 < 0)
	{
		cout << "IF: (P1 - P4)" << endl;
		R1 = (float)Q1 / (float)P1;
		R2 = (float)Q4 / (float)P4;
		
		cout << "R1: " << R1 << "\tR2: " << R2 << endl;
		
		// Minimum of R values
		temp = (R1 > R2) ? R1 : R2;
		U1 = (temp > 0) ? temp : 0;
		cout << "U1: " << U1 << endl;
	}
	else if(P1 >= 0 && P4 >= 0)
	{
		cout << "ELSE: (P1 - P4)" << endl;
		R3 = (float)Q1 / (float)P1;
		R4 = (float)Q4 / (float)P4;
		
		cout << "R3: " << R3 << "\tR4: " << R4 << endl;
		
		// Minimum of R values
		temp = (R3 > R4) ? R4 : R3;
		U2 = (temp > 1) ? 1 : temp;
		cout << "U2: " << U2 << endl;
	}
	
	// Calculating values of R
	if(P2 < 0 && P3 < 0)
	{
		cout << "IF: (P2 - P3)" << endl;
		R1 = (float)Q2 / (float)P2;
		R2 = (float)Q3 / (float)P3;
		
		cout << "R1: " << R1 << "\tR2: " << R2 << endl;
		
		// Minimum of R values
		temp = (R1 > R2) ? R1 : R2;
		U1 = (temp > 0) ? temp : 0;
		cout << "U1: " << U1 << endl;
	}
	else if(P2 >= 0 && P3 >= 0)
	{
		cout << "ELSE: (P2 - P3)" << endl;
		R3 = (float)Q2 / (float)P2;
		R4 = (float)Q3 / (float)P3;
		
		cout << "R3: " << R3 << "\tR4: " << R4 << endl;
		
		// Minimum of R values
		temp = (R3 > R4) ? R4 : R3;
		U2 = (temp > 1) ? 1 : temp;
		cout << "U2: " << U2 << endl;
	}
	
	if(U1 > U2)
	{
//		cout << "U Case." << endl;
		return false;
	}
	
	if(U1 > 0)
	{
		start->first = (float)x1 + ((float)U1 * (float)dx);
		start->second = (float)y1 + ((float)U1 * (float)dy);
	}
	if(U2 < 1)
	{
		end->first = (float)x1 + ((float)U2 * (float)dx);
		end->second = (float)y1 + ((float)U2 * (float)dy);
	}
	
//	cout << "X1: " << XCoord1 << "\tY1: " << YCoord1 << "\tX2: " << XCoord2 << "\tY2: " << YCoord2 << endl;
	
	return true;
}
