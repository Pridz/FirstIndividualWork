#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <cstdlib>
#include "conio2.h"
#include <stdio.h>

int readInteger()
{
	char* str = readString();
	int value = atoi(str);
	delete[] str;
	return value;
}

char* readString()
{
	char* bufor = new char[80];
	char c = getch();

	int i = 0;
	while (c != ASCII_ENTER)
	{
		if(c == ASCII_BACKSPACE)
		{
			gotoxy(wherex() - 1, wherey());
			putch(' ');
			gotoxy(wherex() - 1, wherey());
			if(i > 0)
				i--;
		}
		else
		{
			bufor[i] = c;
			i++;
			putch(c);
		}
		c = getch();
	}
	putch('\n');
	bufor[i] = NULL;
	return bufor;
}

int** allocateMemory(int width, int height)
{
	int** result = new int*[height];
	for (int i = 0; i < height; i++)
		result[i] = new int[width];

	return result;
}

void freeMemory(int** source, int height)
{
	for (int i = 0; i < height; i++)
		delete[] source[i];
	delete[] source;
}

void showPicture(Picture picture)
{
	for (int i = 0; i < picture.height; i++)
	{
		for (int j = 0; j < picture.width; j++)
		{
			textbackground(picture.colors[i][j]);
			gotoxy(j+PICTURE_X, i+PICTURE_Y);
			putch(' ');
		}
	}
	textbackground(BLACK);

}

int readIntegerFromFile(FILE* file)
{
	char c = fgetc(file);
	char bufor[11];
	int i = 0;
	while (c != '\n')
	{
		bufor[i] = c;
		i++;
		c = fgetc(file);
	}

	bufor[i] = NULL;

	int value = atoi(bufor);
	return value;
}

Picture openPicture(const char* name)
{
	FILE* file = fopen(name, "r");
	Picture picture;

	picture.height = readIntegerFromFile(file);
	picture.width = readIntegerFromFile(file);
	
	picture.colors = allocateMemory(picture.width, picture.height);

	for (int i = 0; i < picture.height; i++)
		for (int j = 0; j < picture.width; j++)
			picture.colors[i][j] = readIntegerFromFile(file);


	fclose(file);
	return picture;
}

void drawReactangle(Picture picture, Point from, Point to, int color)
{
	orderPoints(from, to);
	for (int i = from.y - PICTURE_Y; i <= to.y - PICTURE_Y; i++)
		for (int j = from.x - PICTURE_X; j <= to.x - PICTURE_X; j++)
			picture.colors[i][j] = color;
}

void moveCursor(int zn, int& x, int& y)
{
	if (zn == 0x48) 
		y--;
	else if (zn == 0x50) 
		y++;
	else if (zn == 0x4b) 
		x--;
	else if (zn == 0x4d) 
		x++;
	gotoxy(x, y);
}

void savePicture(Picture picture, const char* name)
{
	FILE* file = fopen(name, "w");
	fprintf(file, "%d\n%d\n", picture.height, picture.width);
	for (int i = 0; i < picture.height;i++)
	{
		for (int j = 0; j < picture.width;j++)
		{
			fprintf(file, "%d\n", picture.colors[i][j]);
		}
	}

	fclose(file);

}

Picture createPicture()
{
	cputs("Podaj rozmiary :");

	Picture picture;

	picture.width = readInteger();
	picture.height = readInteger();

	picture.colors = allocateMemory(picture.width, picture.height);

	for (int i = 0; i < picture.height; ++i)
		for (int j = 0; j < picture.width; ++j)
		{
			picture.colors[i][j] = WHITE;
		}
	return picture;
}

void swap(Point& from, Point& to)
{
	Point temp = from;
	from = to;
	to = temp;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void orderPoints(Point& from, Point& to)
{
	if(from.x > to.x && from.y > to.y)
		swap(from, to);
	
	if (from.x > to.x && from.y < to.y)
		swap(from.x, to.x);

	if (from.x<to.x&& from.y>to.y)
		swap(from.y, to.y);
}

void fill(Picture picture, Point from, int color)
{
	int whichColor = picture.colors[from.y][from.x];
	bool fillLeftUp = whichColor == picture.colors[from.y][from.x - 1];
	bool fillRightUp = whichColor == picture.colors[from.y - 1][from.x];
	bool fillLeftDown = whichColor == picture.colors[from.y + 1][from.x-1];

	fillRD(picture, from, color, whichColor);

	if(fillLeftUp)
		fillLU(picture, Point(from.x-1, from.y), color, whichColor);
	if (fillRightUp)
		fillRU(picture, Point(from.x, from.y - 1), color, whichColor);
	if (fillLeftDown)
		fillLD(picture, Point(from.x - 1, from.y + 1), color, whichColor);
}

void fillRD(Picture picture, Point from, int color, int whichColor)
{
	if (picture.colors[from.y][from.x] == picture.colors[from.y][from.x + 1])
		fillRD(picture, Point(from.x + 1, from.y), color, whichColor);

	if (picture.colors[from.y][from.x] == picture.colors[from.y+1][from.x])
		fillRD(picture, Point(from.x, from.y + 1), color, whichColor);
	
	picture.colors[from.y][from.x] = color;
}

void fillLU(Picture picture, Point from, int color, int whichColor)
{
	if (picture.colors[from.y][from.x] == picture.colors[from.y][from.x - 1])
		fillLU(picture, Point(from.x - 1, from.y), color, whichColor);

	if (picture.colors[from.y][from.x] == picture.colors[from.y -1][from.x])
		fillLU(picture, Point(from.x, from.y - 1), color, whichColor);

	picture.colors[from.y][from.x] = color;
}

void fillLD(Picture picture, Point from, int color, int whichColor)
{
	if (picture.colors[from.y][from.x] == picture.colors[from.y][from.x - 1])
		fillLD(picture, Point(from.x - 1, from.y), color, whichColor);

	if (picture.colors[from.y][from.x] == picture.colors[from.y + 1][from.x])
		fillLD(picture, Point(from.x, from.y + 1), color, whichColor);

	picture.colors[from.y][from.x] = color;
}

void fillRU(Picture picture, Point from, int color, int whichColor)
{
	if (picture.colors[from.y][from.x] == picture.colors[from.y][from.x + 1])
		fillRU(picture, Point(from.x + 1, from.y), color, whichColor);

	if (picture.colors[from.y][from.x] == picture.colors[from.y - 1][from.x])
		fillRU(picture, Point(from.x, from.y - 1), color, whichColor);

	picture.colors[from.y][from.x] = color;
}

void drawframe(Picture picture, Point from, Point to, int color)
{
	orderPoints(from, to);

	for (int i = from.y - PICTURE_Y; i <= to.y - PICTURE_Y; i++)
		for (int j = from.x - PICTURE_X; j <= to.x - PICTURE_X; j++)
			if(i==from.y - PICTURE_Y || i==to.y-PICTURE_Y || j==from.x-PICTURE_X ||j==to.x-PICTURE_X)
				picture.colors[i][j] = color;
}