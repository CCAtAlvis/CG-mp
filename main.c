#include <graphics.h>
#include <stdio.h>

void main () {
	int gd = DETECT, gm, flag = 0;
	int x=10, y=10;
	char ch;

	clrscr();
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	while (1) {
		cleardevice();
		if (kbhit()) {
			ch = getch();
			//printf("%d", ch);
			flag = 1;
		} else {
			flag = 0;
			//printf(".");
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
		setcolor(RED);
		rectangle(x,getmaxy()-20, x+30, getmaxy()-10);
		//delay(10);
	}
	closegraph();
}
