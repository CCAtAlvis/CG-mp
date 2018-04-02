#include <stdio.h>
#include <graphics.h>

// lets define the player struct
typedef struct player {
    unsigned char orientation; // E(ast), W(est), N(orth), S(outh)
    unsigned short x;
    unsigned short y;
    unsigned short bombs;
    unsigned short life;
} p1, p2;

// defination for tiles
typedef struct tile {
    unsigned char type;
    // B: Blank
    // O: Obastacle
    // D: Destroyable

    unsigned short top;
    unsigned short left;
} tiles[17][17];

// defination for bombs
typedef struct bomb {
    unsigned short x;
    unsigned short y;
    float timeToExplode;
    unsigned short placedBy;
} bombs[6];

// some global variable declaration
unsigned short tileSize = 26;
unsigned short tileSizeHalf = 13;
unsigned short offset = 0;

// run this function to initilize variable and load the level
void setup () {
    unsigned int color;
    unsigned short i, j;
    unsigned short top, bottom, left, right;

    // setup the level design
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

    // initialize the level
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

    // TODO:
    // initialize the players
    // initialize the bombs array
}

// move player identified by PlayerIndex in the given direction
void movePlayer (unsigned short PlayerIndex, char direction) {
    // TODO:
    // depending upon the orientation of player
    // move player in that direction
    // before moving the player check if there is any obstacle i.e.
    // an obstacle tile, destroyable tile or other player present at that position
    // if not move the player
    // while moving the player, calc its next postion and orientation
    // also make its previous postion a blank tile
}

// place the bomb!!! its that simple
void placeBomb (unsigned short PlayerIndex) {
    // TODO:
    // 1)
    // place the bomb in front of the player
    // if we are doing that we will have to calc
    // next coodrs from its orientation etc, like in movePlayer
    // 2)
    // if we place the bomb at the player location,
    // it would be a lot easy to calc everything
    // as we are not taking the orientation into consideraion
    // moving and redrawing the player will also become a lot simpler 
}

// to manage the input and take action accordingly
// also to keep main() clean
void manageInput () {
    // TODO:
    // make this function work!
    // basicaly shift appropriate content
    // and also add return type (if any)
}

// this is the main game event function
// called on every frame refresh
void loop () {
    // TODO:
    // make this function work!
    // and also the game
}

void main () {
    int gd=DETECT, gm, flag=0;
    // int x=10, y=10;
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
        }

        if (ch == 'q' || ch == 'Q')
            break;

        if (flag) {
            switch (ch) {
                // cases for player 1:
                // using wasd keys
                // and SPACE BAR for placing bomb
                case 'd':
                    // x += 10;
                    break;

                // cases for player 2:
                // using arrow keys
                // and 0 for placing bomb
                case 77:
                    // x += 10;
                    break;
            }

            // move the player 1 or 2 accordingly
            // movePlayer(parameters goes here);
        }

        // reset flags etc.
        flag = 0;
    }

    // a thank you screen if you want!

    closegraph();
}
