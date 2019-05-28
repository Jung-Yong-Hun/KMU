#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#define N 10
using namespace std;
//#include "sokoban.h"



class Object {
private:
	int xPosition;
	int yPosition;
	unsigned char zn;
	chtype ozn;

public:
	void levList(int*, int*, int*, int, int, int);
	void palette();
	void Level(int);
	void Play(int);


};
Object obj[N] = {};

int wbox = 0;
int lev = 0;

void Object::levList(int* h, int* w, int* array, int y, int x, int n) {
	if (n == 0) {
		*h = 9;
		*w = 7;
		int map0[9][7] = {
		{1, 1, 1, 1, 4, 4, 4},
		{1, 3, 0, 1, 1, 4, 4},
		{1, 3, 5, 0, 1, 4, 4},
		{1, 3, 0, 2, 1, 4, 4},
		{1, 1, 2, 0, 1, 1, 1},
		{4, 1, 0, 2, 0, 0, 1},
		{4, 1, 0, 0, 0, 0, 1},
		{4, 1, 0, 0, 1, 1, 1},
		{4, 1, 1, 1, 1, 4, 4} };

		*array = map0[y][x];
	}
	else if (n == 1) {
		*h = 7;
		*w = 6;
		int map1[7][6] = {
			{1,1,1,1,1,4},
			{1,0,0,0,1,4},
			{1,3,3,3,1,4},
			{1,2,2,2,1,1},
			{1,0,0,0,0,1},
			{1,0,5,0,0,1},
			{1,1,1,1,1,1} };
		*array = map1[y][x];
	}
	else if (n == 2) {
		*h = 6;
		*w = 8;
		int map2[6][8] = {
			{1,1,1,1,1,1,1,1},
			{1,3,0,0,0,0,0,1},
			{1,0,3,2,2,2,5,1},
			{1,3,0,0,0,0,0,1},
			{1,1,1,1,1,0,0,1},
			{4,4,4,4,1,1,1,1} };
		*array = map2[y][x];
	}
	else if (n == 3) {
		*h = 8;
		*w = 7;
		int map3[8][7] = {
			{1,1,1,1,1,1,1},
			{1,0,0,0,0,0,1},
			{1,0,3,2,3,0,1},
			{1,0,2,3,2,0,1},
			{1,0,3,2,3,0,1},
			{1,0,2,3,2,0,1},
			{1,0,0,5,0,0,1},
			{1,1,1,1,1,1,1} };
		*array = map3[y][x];
	}
	else if (n == 4) {
		*h = 8;
		*w = 10;
		int map4[8][10] = {
			{4,1,1,1,1,4,4,4,4,4},
			{4,1,0,0,1,1,1,1,4,4},
			{4,1,0,0,0,0,0,1,1,4},
			{1,1,0,1,1,0,0,0,1,4},
			{1,3,0,3,1,0,5,2,1,1},
			{1,0,0,0,1,0,2,2,0,1},
			{1,0,0,3,1,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1} };
		*array = map4[y][x];
	}
}

void Object::palette() {
	init_color(COLOR_BLACK, 0, 0, 0);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

void Object::Level(int n) {
	clear();
	mvprintw(1, 8, "Level %d", lev);
	mvprintw(2, 1, "Move=keypad, Restart-R, Map-M, Exit-Q.");
	int x = 0, y = 0, h = 1, w = 1, map;
	wbox = 0;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			levList(&h, &w, &map, y, x, n);
			switch (map)
			{
			case 0:mvaddch(y + 4, x + 10, ' ' | COLOR_PAIR(4)); break;
			case 4:mvaddch(y + 4, x + 10, '#' | COLOR_PAIR(1)); break;
			case 1:mvaddch(y + 4, x + 10, '#' | COLOR_PAIR(1)); break;
			case 3:mvaddch(y + 4, x + 10, 'x' | COLOR_PAIR(2)); break;
			case 2:
				mvaddch(y + 4, x + 10, ' ' | COLOR_PAIR(4));
				wbox += 1;
				obj[wbox].ozn = mvinch(y + 4, x + 10);
				obj[wbox].yPosition = y + 4;
				obj[wbox].xPosition = x + 10;
				obj[wbox].zn = '@';
				mvaddch(obj[wbox].yPosition, obj[wbox].xPosition, obj[wbox].zn | COLOR_PAIR(5));
				break;
			case 5:
				mvaddch(y + 4, x + 10, ' ' | COLOR_PAIR(4));
				obj[0].ozn = mvinch(y + 4, x + 10);
				obj[0].yPosition = y + 4;
				obj[0].xPosition = x + 10;
				obj[0].zn = 'P';
				mvaddch(obj[0].yPosition, obj[0].xPosition, obj[0].zn | COLOR_PAIR(3));
				break;
			}
		}
	}
	move(obj[0].yPosition, obj[0].xPosition);
}

void Object::Play(int input)
{
	bool restart = FALSE;

	chtype up, lf, dw, rg, oup, olf, odw, org;
	up = (mvinch(obj[0].yPosition - 1, obj[0].xPosition) & A_CHARTEXT);
	lf = (mvinch(obj[0].yPosition, obj[0].xPosition - 1) & A_CHARTEXT);
	dw = (mvinch(obj[0].yPosition + 1, obj[0].xPosition) & A_CHARTEXT);
	rg = (mvinch(obj[0].yPosition, obj[0].xPosition + 1) & A_CHARTEXT);
	oup = (mvinch(obj[0].yPosition - 2, obj[0].xPosition) & A_CHARTEXT);
	olf = (mvinch(obj[0].yPosition, obj[0].xPosition - 2) & A_CHARTEXT);
	odw = (mvinch(obj[0].yPosition + 2, obj[0].xPosition) & A_CHARTEXT);
	org = (mvinch(obj[0].yPosition, obj[0].xPosition + 2) & A_CHARTEXT);

	for (int o = 0; o <= wbox; o++)
	{
		mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].ozn);
	}
	switch (input)
	{
	case KEY_UP:
		if (up != 35)
		{
			if (up == 64 && (oup == ' ' || oup == 120))
			{
				obj[0].yPosition -= 1;
				for (int o = 1; o <= wbox; o++)
				{
					if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
					{
						obj[o].yPosition -= 1;
					}
				}
			}
			else if (up != 64)
			{
				obj[0].yPosition -= 1;
			}
			break;
		}
	case KEY_DOWN:
		if (dw != 35)
		{
			if (dw == 64 && (odw == ' ' || odw == 120))
			{
				obj[0].yPosition += 1;
				for (int o = 1; o <= wbox; o++)
				{
					if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
					{
						obj[o].yPosition += 1;
					}
				}
			}
			else if (dw != 64)
			{
				obj[0].yPosition += 1;
			}
		}
		break;

	case KEY_LEFT:
		if (lf != 35)
		{
			if (lf == 64 && (olf == ' ' || olf == 120))
			{
				obj[0].xPosition -= 1;
				for (int o = 1; o <= wbox; o++)
				{
					if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
					{
						obj[o].xPosition -= 1;
					}
				}
			}
			else if (lf != 64)
			{
				obj[0].xPosition -= 1;
			}
		}
		break;

	case KEY_RIGHT:
		if (rg != 35) {
			if (rg == 64 && (org == ' ' || org == 120)) {
				obj[0].xPosition += 1;
				for (int o = 1; o <= wbox; o++) {
					if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition)) {
						obj[o].xPosition += 1;
					}
				}
			}
			else if (rg != 64) obj[0].xPosition += 1;
		}
		break;
	case 'm':
	case 'M':
		restart = TRUE;
		if (lev < 4) lev += 1;
		else lev = 0;
		Level(lev);
		break;

	case 'r':
	case 'R':
		restart = TRUE;
		Level(lev);
		break;
	default:
		break;
	}
	if (!restart) {
		for (int o = 0; o <= wbox; o++) {
			obj[o].ozn = mvinch(obj[o].yPosition, obj[o].xPosition);
			mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].zn | ((o == 0) ? COLOR_PAIR(3) : COLOR_PAIR(5)));
		}
		move(obj[0].yPosition, obj[0].xPosition);
	}
	else restart = FALSE;
}
int main() {
	Object a;
	Object obj[N] = {};
	int ch;
	initscr();
	keypad(stdscr, TRUE);
	if (!has_colors()) {
		endwin();
		printf("ERROR INITIALISING COLORS.n");
		exit(1);
	}
	start_color();
	a.palette();
	a.Level(lev);
	while ((ch = getch()) != 'q') {
		a.Play(ch);
	}
	endwin();
	return 0;
}



