#include <bits/stdc++.h>
#include <gl/glut.h>
#include "axis.h"
#include "color.h"
#include "thickness.h"
#include "pattern.h"
#include "symmetricdda.h"
#include "simpledda.h"
#include "bresenhamlda.h"
#include "mid_pointlda.h"
#include "circle.h"
#include "ellipse.h"
#include "viewport.h"
using namespace std;

bool ScreenCleared = true;
int ScreenSizeX = 900, ScreenSizeY = 700;
int Choice = 0;
int transformation = 0;
int mouseClickCount = 0;
int currThickness = Thickness::THICKNESS_1;
unsigned char* currColor = Color::BLACK;
string currPattern = Pattern::HEX_F;
int XCoord1, YCoord1, XCoord2, YCoord2;
bool ViewportPresent = false;
bool menuUsageFlag = false;
bool isObjectSelected = false;
int rotAngleDeg = 0;

int menu1 = -10, menu2 = -10;

list<Object*> objectList;
pair<int, int> selectedCoords, seed;
pair<int, int> pivotCoords = pair<int, int>(0, 0);
Object* selectedObject;
Viewport* viewport;

void display();

void initVariables()
{
	viewport = new Viewport(-ScreenSizeX/2, -ScreenSizeY/2, ScreenSizeX/2, ScreenSizeY/2);
}

void init()
{
	glClearColor(255, 255, 255, 1);
	glViewport(0, 0, ScreenSizeX, ScreenSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-ScreenSizeX/2, ScreenSizeX/2, -ScreenSizeY/2, ScreenSizeY/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void redrawAllObjects()
{
	cout << "Redrawing " << objectList.size() << " Objects..." << endl;
	list<Object*>::iterator it;
	for(it = objectList.begin(); it != objectList.end(); it++)
	{
		(*it)->redrawSelectedObject((*it)->color, (*it)->thickness);
	}
	cout << objectList.size() << " Objects Redrawn." << endl;
}

void plotPoint(int x, int y)
{
	viewport->printCoords();
	cout << "X: " << x << "\tY: " << y << endl;
	if(!viewport->isClipped(x, y))
	{
		cout << "Inside IF..." << endl;
		glColor3ubv(Color::BLACK);
		glPointSize(3);
		glBegin(GL_POINTS);
			glVertex2i(x, y);
		glEnd();
		glFlush();
		glPointSize(1);
	}
}

void redraw()
{
//	if(ScreenCleared)	return;

		cout << "\nRedraw:\n\tChoice: " << Choice << endl;
		switch(Choice)
		{
			case -2:
			{
				cout << endl << endl << "Drawing Viewport..." << endl;
//				viewport = new Viewport(XCoord1, YCoord1, XCoord2, YCoord2);
				viewport->setViewport(XCoord1, YCoord1, XCoord2, YCoord2);
				display();
				viewport->drawViewport();
				viewport->printCoords();
				ViewportPresent = true;
				Choice = 0;
				glutChangeToMenuEntry(2, "Remove Viewport", -3);
				cout << endl << endl << "Viewport Drawn." << endl;
				break;
			}
			case -5:
				glutSetWindowTitle("Fill Object");
				cout << "Object Color: R: " << (int)Color::RED[0] << "\tG: " << (int)Color::RED[1] << "\tB: " << (int)Color::RED[2] << endl;
				cout << "Fill Color: R: " << (int)Color::PURPLE[0] << "\tG: " << (int)Color::PURPLE[1] << "\tB: " << (int)Color::PURPLE[2] << endl;
				cout << "X: " << seed.first << "\tY: " << seed.second << endl;
				selectedObject->fillBoundary(seed.first, seed.second, Color::PURPLE, Color::RED);	
				glFlush();
//				selectedObject->fillBoundary(seed, Color::PURPLE, Color::RED);
				break;
			case -11:
				glutSetWindowTitle("Translate Object");
				cout << "Selected Coords:" << endl;
				cout << "\tX: " << selectedCoords.first << "\tY: " << selectedCoords.second << endl;
				cout << "Pivot Coords:" << endl;
				cout << "\tX: " << pivotCoords.first << "\tY: " << pivotCoords.second << endl;
				selectedObject->translate(pivotCoords.first - selectedCoords.first, pivotCoords.second - selectedCoords.second);
				break;
			case -12:
				glutSetWindowTitle("Rotate Object");
				cout << "Selected Coords:" << endl;
				cout << "\tX: " << selectedCoords.first << "\tY: " << selectedCoords.second << endl;
				cout << "Pivot Coords:" << endl;
				cout << "\tX: " << pivotCoords.first << "\tY: " << pivotCoords.second << endl;
				selectedObject->rotate(rotAngleDeg, pivotCoords);
				break;
			case -13:
				glutSetWindowTitle("Scale Object");
				cout << "Selected Coords:" << endl;
				cout << "\tX: " << selectedCoords.first << "\tY: " << selectedCoords.second << endl;
				cout << "Pivot Coords:" << endl;
				cout << "\tX: " << pivotCoords.first << "\tY: " << pivotCoords.second << endl;
				selectedObject->scale(1, 1, pivotCoords);
				break;
			case 1:
				cout << "Plotting Point..." << endl;
				plotPoint(XCoord1, YCoord1);
				cout << "Point Plotted..." << endl;
				break;
			case 2:
			{
				cout << endl << endl << "Drawing Symmetric Line..." << endl;
				SymmetricDDA *symmetricLine = new SymmetricDDA(currColor, currThickness, currPattern);
				glutSetWindowTitle(symmetricLine->objectName);
				symmetricLine->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(symmetricLine);
				cout << "Symmertic Line Drawn." << endl;
				break;
			}
			case 3:
			{
				cout << endl << endl << "Drawing Simple Line..." << endl;
				SimpleDDA *simpleLine = new SimpleDDA(currColor, currThickness, currPattern);
				glutSetWindowTitle(simpleLine->objectName);
				simpleLine->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(simpleLine);
				cout << "Simple Line Drawn." << endl;
				break;
			}
			case 4:
			{
				cout << endl << endl << "Drawing Bresenham Line..." << endl;
				BresenhamLDA *bresenhamLine = new BresenhamLDA(currColor, currThickness, currPattern);
				glutSetWindowTitle(bresenhamLine->objectName);
				bresenhamLine->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(bresenhamLine);
				cout << "Bresenham Line Drawn." << endl;
				break;
			}
			case 5:
			{
				cout << endl << endl << "Drawing Mid-Point Line..." << endl;
				Mid_PointLDA *midpointLine = new Mid_PointLDA(currColor, currThickness, currPattern);
				glutSetWindowTitle(midpointLine->objectName);
				midpointLine->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(midpointLine);
				cout << "Mid-Point Line Drawn." << endl;
				break;
			}
			case 6:
			{
				cout << endl << endl << "Drawing Circle..." << endl;
				MidPoint_Circle *circle = new MidPoint_Circle(currColor, currThickness, currPattern);
				glutSetWindowTitle(circle->objectName);
				circle->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(circle);
				cout << "Circle Drawn." << endl;
				break;
			}
			case 7:
			{
				cout << endl << endl << "Drawing Ellipse..." << endl;
				MidPoint_Ellipse *ellipse = new MidPoint_Ellipse(currColor, currThickness, currPattern);
				glutSetWindowTitle(ellipse->objectName);
				ellipse->draw(XCoord1, YCoord1, XCoord2, YCoord2);
				objectList.push_back(ellipse);
				cout << "Ellipse Drawn." << endl;
				break;
			}
//			case 9:
//				cout << "Polygon" << endl;
//				if(WeilerAtherton())
//					PolygonGeneration();
//				break;
//			case 70:
//				cout << "Filling Code Executing..." << endl;
//				Filling();
//				break;
		}
//	glEnd();
//	glFlush();
	
//	if(Choice > 2 && Choice != 9)	plotEndPoints();
	
	ScreenCleared = false;
}

void display()
{
	cout << "Inside Display..." << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	Axis::drawAxis();
	viewport->drawViewport();
	viewport->printCoords();
	redrawAllObjects();
}

void mouseEvent(int button, int state, int x, int y)
{
	if(Choice == 0)	return;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(Choice == -5)
		{
			seed.first = x;
			seed.second = y;
			cout << "Seed X: " << seed.first << "\tY: " << seed.second << endl;
			redraw();
			return;
		}
		
		x = x - ScreenSizeX/2;
		y = ScreenSizeY/2 - y;
	
		glColor3ubv(Color::BLACK);	
		
		if(Choice == 1)
		{
			XCoord1 = x;
			YCoord1 = y;
			redraw();
			return;
		}
		
		// For transfomation
		if(Choice >= -13 && Choice <= -11)
		{
			cout << "Transformation Coordinates Set." << endl;
			pivotCoords.first = x;
			pivotCoords.second = y;
			redraw();
//			Choice = 0;
			return;
		}
		
		if(Choice == -4)
		{
			bool result;
			cout << "Selecting Object..." << endl;
			selectedCoords.first = x;
			selectedCoords.second = y;
			
			list< Object* >::iterator it;
			for(it = objectList.begin(); it != objectList.end(); it++)
			{
				result = (*it)->selectObject(selectedCoords);
				if(result)
				{
					selectedObject = *it;
					isObjectSelected = true;
					cout << "Object Selected..." << endl;
//					glutSetMenu(menu2);
//					glutAttachMenu(GLUT_RIGHT_BUTTON);
//					return;
				}
			}
			return;
		}

		mouseClickCount++;
		if(mouseClickCount == 1)
		{
			XCoord1 = x;
			YCoord1 = y;
			glPointSize(3);
			glColor3ubv(Color::GRAY);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			glFlush();
			glPointSize(1);
		}
		else
		{
			XCoord2 = x;
			YCoord2 = y;
			cout << "\tX1: " << XCoord1 << "\tY1: " << YCoord1 << "\tX2: " << XCoord2 << "\tY2: " << YCoord2 << endl;
			mouseClickCount = 0;
			glPointSize(3);
			glColor3ubv(Color::GRAY);
			glBegin(GL_POINTS);
				glVertex2i(x, y);
			glEnd();
			glFlush();
			glPointSize(1);
			redraw();
		}

	}
}

void menuStatus(int status, int x, int y)
{
	if(status == GLUT_MENU_IN_USE)	menuUsageFlag = true;
	else	menuUsageFlag = false;
}

void keyboardEvent(unsigned char key, int x, int y)
{
	if(menuUsageFlag)	return;
	
	cout << "Key Pressed..." << endl;
	
	switch(key)
	{
		case '0':
			currPattern = Pattern::HEX_0;
			break;
		case '1':
			currPattern = Pattern::HEX_1;
			break;
		case '2':
			currPattern = Pattern::HEX_2;
			break;
		case '3':
			currPattern = Pattern::HEX_3;
			break;
		case '4':
			currPattern = Pattern::HEX_4;
			break;
		case '5':
			currPattern = Pattern::HEX_5;
			break;
		case '6':
			currPattern = Pattern::HEX_6;
			break;
		case '7':
			currPattern = Pattern::HEX_7;
			break;
		case '8':
			currPattern = Pattern::HEX_8;
			break;
		case '9':
			currPattern = Pattern::HEX_9;
			break;
		case 'A':
		case 'a':
			currPattern = Pattern::HEX_A;
			break;
		case 'B':
		case 'b':
			currPattern = Pattern::HEX_B;
			break;
		case 'C':
		case 'c':
			currPattern = Pattern::HEX_C;
			break;
		case 'D':
		case 'd':
			currPattern = Pattern::HEX_D;
			break;
		case 'E':
		case 'e':
			currPattern = Pattern::HEX_E;
			break;
		case 'F':
		case 'f':
			currPattern = Pattern::HEX_F;
			break;
	}
}

void lineColorSubmenu(int id)
{
	if(selectedObject == NULL)	return;
	
//	cout << "ID: " << id << endl;
	switch(id)
	{
		case 11:
			currColor = Color::BLACK;
			break;
		case 12:
			currColor = Color::RED;
			break;
		case 13:
			currColor = Color::BLUE;
			break;
		case 14:
			currColor = Color::GREEN;
			break;
		case 15:
			currColor = Color::GRAY;
			break;
		case 16:
			currColor = Color::CYAN;
			break;
		case 17:
			currColor = Color::YELLOW;
			break;
		case 18:
			currColor = Color::PURPLE;
			break;
		case 19:
			currColor = Color::MAGENTA;
			break;
	}
	selectedObject->setColor(currColor);
	redrawAllObjects();
//	selectedObject->redrawSelectedObject(selectedObject->color, selectedObject->thickness);
}

void lineThicknessSubmenu(int id)
{
	if(selectedObject == NULL)	return;
	
	switch(id)
	{
		case 21:
			currThickness = Thickness::THICKNESS_1;
			break;
		case 22:
			currThickness = Thickness::THICKNESS_2;
			break;
		case 23:
			currThickness = Thickness::THICKNESS_3;
			break;
		case 24:
			currThickness = Thickness::THICKNESS_4;
			break;
		case 25:
			currThickness = Thickness::THICKNESS_5;
			break;
		case 26:
			currThickness = Thickness::THICKNESS_6;
			break;
		case 27:
			currThickness = Thickness::THICKNESS_7;
			break;
	}
	selectedObject->setThickness(currThickness);
	redrawAllObjects();
//	selectedObject->redrawSelectedObject(selectedObject->color, selectedObject->thickness);
}

void rotAngleMenu(int id)
{
	if(selectedObject == NULL)
	{
		cout << "No Object Selected..." << endl;
		return;
	}
	
	Choice = -12;
	switch(id)
	{
		case 31:
			rotAngleDeg = 30;
			break;
		case 32:
			rotAngleDeg = 60;
			break;
		case 33:
			rotAngleDeg = 90;
			break;
		case 34:
			rotAngleDeg = 120;
			break;
		case 35:
			rotAngleDeg = 150;
			break;
		case 36:
			rotAngleDeg = 210;
			break;
		case 37:
			rotAngleDeg = 240;
			break;
		case 38:
			rotAngleDeg = 270;
			break;
		case 39:
			rotAngleDeg = 300;
			break;
		case 40:
			rotAngleDeg = 330;
			break;
	}
}

void mainMenu(int id)
{
	cout << "Inside Menu..." << endl;
	if(id > 0 && id <= 10)
	{
		selectedCoords.first = 0;
		selectedCoords.second = 0;
		selectedObject = NULL;
		cout << "Selected Coords:\n\tX: " << selectedCoords.first << "\tY: " << selectedCoords.second << endl;
//		return;
	}
	if((id == -11 || id == -13) && (selectedObject == NULL))
	{
		cout << "No Object Selected..." << endl;
		return;
	}
	if(id == -1)
	{
		ScreenCleared = true;
		objectList.clear();
		mouseClickCount = 0;
		Choice = 0;
		display();
		return;
	}
	if(id == -2)
	{
		ScreenCleared = false;
		objectList.clear();
		mouseClickCount = 0;
		Choice = 0;
		display();
	}
	if(id == -3)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		ScreenCleared = false;
		mouseClickCount = 0;
		viewport->removeViewport();
		display();
		redrawAllObjects();
		glutChangeToMenuEntry(2, "Draw Viewport", -2);
		ViewportPresent = false;
		return;
	}
	mouseClickCount = 0;
	cout << "ID: " << id << endl;
	Choice = id;
	cout << "ID: " << id << endl;
}

void createMenu()
{
	int viewportSubmenuID = -10, shapeSubmenuID = -10, transformSubmenuID = -10, rotationSubmenuID = -10, fillingSubmenuID = -10, lineColorSubmenuID = -10, thicknessSubmenuID = -10;
	int shapeEntryID = 0, lineColorEntryID = 10, lineThicknessEntryID = 20, rotationEntryID = 30;//, XYColorEntryID = 30, fillingEntryID = 40;

//	viewportSubmenuID = glutCreateMenu(NULL);
//	glutAddMenuEntry("Liang Barsky", );

	shapeSubmenuID = glutCreateMenu(mainMenu);
	glutAddMenuEntry("Point", ++shapeEntryID);
	glutAddMenuEntry("Symmetric DDA", ++shapeEntryID);
	glutAddMenuEntry("Simple DDA", ++shapeEntryID);
	glutAddMenuEntry("Bresenham LDA", ++shapeEntryID);
	glutAddMenuEntry("Mid-Point LDA", ++shapeEntryID);
	glutAddMenuEntry("Circle", ++shapeEntryID);
	glutAddMenuEntry("Ellipse", ++shapeEntryID);
//	glutAddMenuEntry("Polygon", ++shapeEntryID);

	rotationSubmenuID = glutCreateMenu(rotAngleMenu);
	glutAddMenuEntry("30", ++rotationEntryID);
	glutAddMenuEntry("60", ++rotationEntryID);
	glutAddMenuEntry("90", ++rotationEntryID);
	glutAddMenuEntry("120", ++rotationEntryID);
	glutAddMenuEntry("150", ++rotationEntryID);
	glutAddMenuEntry("210", ++rotationEntryID);
	glutAddMenuEntry("240", ++rotationEntryID);
	glutAddMenuEntry("270", ++rotationEntryID);
	glutAddMenuEntry("300", ++rotationEntryID);
	glutAddMenuEntry("330", ++rotationEntryID);

	transformSubmenuID = glutCreateMenu(mainMenu);
	glutAddMenuEntry("Translate", -11);
	glutAddSubMenu("Rotate", rotationSubmenuID);
	glutAddMenuEntry("Scale", -13);

//	fillingSubmenuID = glutCreateMenu();
//	glutAddMenuEntry("4-Fill Seed Algorithm", ++fillingEntryID);
//	glutAddMenuEntry("8-Fill Seed Algorithm", ++fillingEntryID);
//	glutAddMenuEntry("Flood Fill Algorithm", ++fillingEntryID);

	lineColorSubmenuID = glutCreateMenu(lineColorSubmenu);
	glutAddMenuEntry("Black", ++lineColorEntryID);
	glutAddMenuEntry("Red", ++lineColorEntryID);
	glutAddMenuEntry("Blue", ++lineColorEntryID);
	glutAddMenuEntry("Green", ++lineColorEntryID);
	glutAddMenuEntry("Gray", ++lineColorEntryID);
	glutAddMenuEntry("Cyan", ++lineColorEntryID);
	glutAddMenuEntry("Yellow", ++lineColorEntryID);
	glutAddMenuEntry("Purple", ++lineColorEntryID);
	glutAddMenuEntry("Magenta", ++lineColorEntryID);

	thicknessSubmenuID = glutCreateMenu(lineThicknessSubmenu);
	glutAddMenuEntry("1", ++lineThicknessEntryID);
	glutAddMenuEntry("2", ++lineThicknessEntryID);
	glutAddMenuEntry("3", ++lineThicknessEntryID);
	glutAddMenuEntry("4", ++lineThicknessEntryID);
	glutAddMenuEntry("5", ++lineThicknessEntryID);
	glutAddMenuEntry("6", ++lineThicknessEntryID);
	glutAddMenuEntry("7", ++lineThicknessEntryID);
	
//	menu2 = glutCreateMenu(mainMenu);
//	glutAddSubMenu("Transformations", transformSubmenuID);
////	glutAddSubMenu("Filling", fillingSubmenuID);
//	glutAddSubMenu("Color", lineColorSubmenuID);
//	glutAddSubMenu("Thickness", thicknessSubmenuID);
	
	menu1 = glutCreateMenu(mainMenu);
	glutAddMenuEntry("Clear Screen", -1);
	glutAddMenuEntry("Draw Viewport", -2);
//	glutAddMenuEntry("Remove Viewport", -3);
	glutAddMenuEntry("Select Object", -4);
	glutAddSubMenu("Shapes", shapeSubmenuID);
	glutAddSubMenu("Transformations", transformSubmenuID);
	glutAddMenuEntry("Filling", -5);
	glutAddSubMenu("Color", lineColorSubmenuID);
	glutAddSubMenu("Thickness", thicknessSubmenuID);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void resizeHandler(int width, int height)
{
	ScreenSizeX = width;
	ScreenSizeY = height;
	init();
	Choice = 0;
	mouseClickCount = 0;
	if(!ViewportPresent)	viewport->setViewport(-ScreenSizeX/2, -ScreenSizeY/2, ScreenSizeX/2, ScreenSizeY/2);
}

void glut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(ScreenSizeX, ScreenSizeY);
	glutCreateWindow("OpenGL Window: Canvas");

	init();
	createMenu();
	glutMouseFunc(mouseEvent);
	glutKeyboardFunc(keyboardEvent);
	glutReshapeFunc(resizeHandler);
	glutDisplayFunc(display);
	glutMainLoop();
}

int main(int argc, char** argv)
{
	initVariables();
	glut(argc, argv);
}
