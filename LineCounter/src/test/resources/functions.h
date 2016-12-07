#pragma once

#define ASCII_ENTER 13
#define ASCII_BACKSPACE 8
#define ASCII_ESCAPE 27
#define BEGIN_X 1
#define BEGIN_Y 1
#define PICTURE_X 30
#define PICTURE_Y 1


struct Point
{
	int x = 0;
	int y = 0;

	Point() {}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

};

struct Picture
{
	int width = 0;
	int height = 0;
	int** colors = nullptr;

};

int readInteger();
char* readString();
int** allocateMemory(int width, int height);
void freeMemory(int** source, int height);
void showPicture(Picture picture);
Picture openPicture(const char* name);
void drawReactangle(Picture picture, Point from, Point to, int color);
void moveCursor(int zn, int& x, int& y);
void savePicture(Picture picture, const char* name);
Picture createPicture();
void drawframe(Picture picture, Point from, Point to, int color);
void orderPoints(Point& from, Point& to);
void fill(Picture picture, Point from, int color);
void fillRD(Picture picture, Point from, int color, int whichColor);
void fillLU(Picture picture, Point from, int color, int whichColor);
void fillLD(Picture picture, Point from, int color, int whichColor);
void fillRU(Picture picture, Point from, int color, int whichColor);