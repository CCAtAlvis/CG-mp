#include <stdio.h>
#include <graphics.h>

typedef struct player {
	unsigned char orentation; // E(ast), W(est), N(orth), S(outh)
	unsigned short x;
	unsigned short y;
	unsigned short bombs;
} p1, p2;

typedef struct tile {
	unsigned char type;
	// B: Blank
	// O: Obastacle
	// D: Destroyable

	unsigned short x;
	unsigned short y;
} tiles[17][17];

unsigned short tileSize = 26;
unsigned short tileSizeHalf = 13;
unsigned short offset = 0;

void setup () {
	unsigned int color;
	unsigned short i, j;
	unsigned short top, bottom, left, right;

	char levelDesign[17][17] = {
		{'O',   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',   'O'},


		{'O',   'B', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'B',   'O'},
		{'O',   'B', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'B',   'O'},

		{'O',   'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D',   'O'},
		{'O',   'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B',   'O'},
		{'O',   'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B',   'O'},
		{'O',   'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B',   'O'},
		{'O',   'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D',   'O'},

		{'O',   'O', 'O', 'O', 'O', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'O', 'O', 'O',   'O'},

		{'O',   'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D',   'O'},
		{'O',   'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B',   'O'},
		{'O',   'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B', 'O', 'D', 'B',   'O'},
		{'O',   'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B',   'O'},
		{'O',   'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D',   'O'},

		{'O',   'B', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'D', 'O', 'B',   'O'},
		{'O',   'B', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'D', 'B', 'B',   'O'},


		{'O',   'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O',   'O'}
	};

	for (i=0; i<17; i++) {
		for (j=0; j<17; j++) {
			// set fill style and boundry color
			if (levelDesign[i][j] == 'O') {
				color = WHITE;
			} else if (levelDesign[i][j] == 'B') {
				color = BLACK;
			} else if (levelDesign[i][j] == 'D') {
				color = DARKGRAY;
			}

			setcolor(color);
			setfillstyle(1, color);

			// lets calc the coords
			top = offset + (i)*tileSize;
			bottom = offset + (i+1)*tileSize;

			left = offset + (j)*tileSize;
			right = offset + (j+1)*tileSize;

			// lets make a rectangle
			rectangle(top, left, bottom, right);
			floodfill(top+1, left+1, color);
		}
	}
}

void movePlayer (unsigned short PlayerIndex, char direction) {
	// TODO:
	// depending upon the orentation of player
	// move player in that direction
	// before moving the player check if there is any obstacle i.e.
	// an obstacle tile, destroyable tile or other player present at that position
	// if not move the player
	// while moving the player, calc its next postion and orentation
	// also make its previous postion a blank tile
}

void main () {
	int gd = DETECT, gm, flag = 0;
	int x=10, y=10;
	char ch;

	clrscr();

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

	// lets setup the level
	setup();

	while (1) {
		//cleardevice();

		if (kbhit()) {
			ch = getch();
			flag = 1;
		} else {
			flag = 0;
		}

		if (ch == 'q' || ch == 'Q')
			break;

		if (flag)
		switch (ch) {
			case 77:
				x += 10;
				break;
			case 'd':
				x += 10;
				break;
		}

		//setcolor(RED);
		//rectangle(x,getmaxy()-20, x+30, getmaxy()-10);
		//delay(10);
	}
	closegraph();
}
