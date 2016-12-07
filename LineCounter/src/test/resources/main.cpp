#include<stdlib.h>
#include<stdio.h>
#include"conio2.h"
#include "functions.h"





int main() 
{
	
	//char* fileName = readString();
	//savePicture(pic, fileName);
	//delete[] fileName;
	Picture picture;
	

	int zn = 0, x = 40, y = 12, back = 0, zero = 0;
	char txt[32] = "kod klawisza: 0x";
	settitle("Amadeusz Chmielowski 165398");
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);
		gotoxy(BEGIN_X, BEGIN_Y);
		cputs("ESC = wyjscie");
		gotoxy(BEGIN_X, BEGIN_Y + 1);
		cputs("strzalki = poruszanie");
		gotoxy(BEGIN_X, BEGIN_Y + 2);
		cputs("spacja = zmiana koloru");
		gotoxy(BEGIN_X, BEGIN_Y + 3);
		cputs("enter = zmiana koloru tla");
		gotoxy(BEGIN_X, BEGIN_Y + 4);
		cputs("k = tworzenie nowego obrazka");
		gotoxy(BEGIN_X + 1, BEGIN_Y + 5);
		textbackground(BLACK);
		cputs("1");
		gotoxy(BEGIN_X + 2, BEGIN_Y + 5);
		textbackground(BLUE);
		cputs("2");
		gotoxy(BEGIN_X + 3, BEGIN_Y + 5);
		textbackground(GREEN);
		cputs("3");
		gotoxy(BEGIN_X + 4, BEGIN_Y + 5);
		textbackground(CYAN);
		cputs("4");
		gotoxy(BEGIN_X + 5, BEGIN_Y + 5);
		textbackground(RED);
		cputs("5");
		gotoxy(BEGIN_X + 6, BEGIN_Y + 5);
		textbackground(MAGENTA);
		cputs("6");
		gotoxy(BEGIN_X + 7, BEGIN_Y + 5);
		textbackground(BROWN);
		cputs("7");
		gotoxy(BEGIN_X + 8, BEGIN_Y + 5);
		textbackground(LIGHTGRAY);
		cputs("8");
		gotoxy(BEGIN_X + 9, BEGIN_Y + 5);
		textbackground(DARKGRAY);
		cputs("9");
		gotoxy(BEGIN_X + 10, BEGIN_Y + 5);
		textbackground(LIGHTBLUE);
		cputs("0");
		gotoxy(BEGIN_X + 11, BEGIN_Y + 5);
		textbackground(LIGHTGRAY);
		cputs("q");
		gotoxy(BEGIN_X + 12, BEGIN_Y + 5);
		textbackground(LIGHTCYAN);
		cputs("w");
		gotoxy(BEGIN_X + 13, BEGIN_Y + 5);
		textbackground(LIGHTRED);
		cputs("e");
		gotoxy(BEGIN_X + 14, BEGIN_Y + 5);
		textbackground(LIGHTMAGENTA);
		cputs("r");
		gotoxy(BEGIN_X + 15, BEGIN_Y + 5);
		textbackground(YELLOW);
		cputs("t");
		gotoxy(BEGIN_X + 16, BEGIN_Y + 5);
		textbackground(WHITE);
		cputs("y");
		textbackground(BLACK);
		textbackground(back);
		showPicture(picture);



		if (zero) {
			txt[16] = '0';
			txt[17] = '0';
			txt[18] = ' ';
			txt[19] = '0';
			txt[20] = 'x';
			_itoa(zn, txt + 21, 16);
		}
		else {
			_itoa(zn, txt + 16, 16);
		}
		gotoxy(BEGIN_X, BEGIN_Y + 6);
		cputs(txt);
		gotoxy(x, y);
		textbackground(back);
		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;
			zn = getch();
			moveCursor(zn, x, y);
		}
		else if (zn == 0x6b) {
			gotoxy(BEGIN_X, BEGIN_Y + 20);
			picture = createPicture();

		}
		else if (zn == 'f') {
			Point from(x, y);

			char c = getch();
			while (c != ASCII_ESCAPE)
			{
				if (c == 0)
				{
					c = getch();
					moveCursor(c, x, y);
				}
				else if (c == 'f')
				{
					Point to(x, y);
					drawframe(picture, from, to, back);
					break;
				}
				c = getch();
			}
		}
		else if (zn == '1')
			back = BLACK;
		else if (zn == '2')
			back = BLUE;
		else if (zn == '3')
			back = GREEN;
		else if (zn == '4')
			back = CYAN;
		else if (zn == '5')
			back = RED;
		else if (zn == '6')
			back = MAGENTA;
		else if (zn == '7')
			back = BROWN;
		else if (zn == '8')
			back = LIGHTGRAY;
		else if (zn == '9')
			back = DARKGRAY;
		else if (zn == '0')
			back = LIGHTBLUE;
		else if (zn == 'q' || zn == 'Q')
			back = LIGHTGREEN;
		else if (zn == 'w' || zn == 'W')
			back = LIGHTCYAN;
		else if (zn == 'e' || zn == 'E')
			back = LIGHTRED;
		else if (zn == 'r' || zn == 'R')
			back = LIGHTMAGENTA;
		else if (zn == 't' || zn == 'T')
			back = YELLOW;
		else if (zn == 'y' || zn == 'Y')
			back = WHITE;
		else if (zn == 'l' || zn == 'L')
			picture.colors[y - PICTURE_Y][x - PICTURE_X] = back;
		else if (zn == 'z' || zn == 'Z')
			fill(picture, Point(x - PICTURE_X, y - PICTURE_Y), back);
			
	} while (zn != 0x1b);

	
	return 0;
}