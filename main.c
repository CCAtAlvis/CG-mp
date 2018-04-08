#include <stdio.h>
#include <graphics.h>

// lets define the player struct
typedef struct player {
    unsigned char orientation; // E(ast), W(est), N(orth), S(outh)
    unsigned short x;
    unsigned short y;
    unsigned short bombs;
    unsigned short life;
} players[2];

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
unsigned short playerSize = 18;
unsigned short playerSizeHalf = 9;
unsigned short gameState = 0;

// all functions definations
void setup ();
void movePlayer (unsigned short, char);
void placeBomb (unsigned short);
void playerHit (unsigned short);
void gameOver ();
void resultScreen ();

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

        {'O',   'O', 'O', 'O', 'O', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'O', 'O', 'O', 'O',   'O'},

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

    // initialize the bombs array
    for (i=0; i<6; ++i) {
        bombs[i].placed = 0;
    }

    // initialize the players
    players[0].x = 1;
    players[0].y = 1;
    players[1].x = 15;
    players[1].y = 15;

    for (i=0; i<2; ++i) {
        if (0==i)
            color = BLUE;
        else
            color = RED;

        players[i].bombs = 3;
        players[i].life = 3;

        top = (tileSizeHalf - playerSizeHalf) + players[i].x*tileSize;
        left = (tileSizeHalf - playerSizeHalf) + players[i].x*tileSize;
        bottom = (tileSizeHalf + playerSizeHalf) + players[i].x*tileSize;
        right = (tileSizeHalf + playerSizeHalf) + players[i].x*tileSize;

        setcolor(color);
        rectangle(top, left, bottom , right);
        setfillstyle(1, color);
        floodfill(top+1, left+1, color);
    }
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
    unsigned short xCord = players[PlayerIndex];
    unsigned short yCord = players[PlayerIndex];
    unsigned short xActual = tileSizeHalf + xCord*tileSize;
    unsigned short yActual = tileSizeHalf + yCord*tileSize;
    unsigned short xTop,yTop,xBottom,yBottom;
    unsigned int color;
    setfillstyle(1,BLACK);
    floodfill(xActual,yActual,BLACK);

    switch(direction)
    {
    case 'N':
        if(tiles[xCord-1][yCord]=='B')
            xCord--;
        break;
    case 'E' :
        if(tiles[xCord][yCord+1]=='B')
            yCord++;
        break;
    case 'W' :
        if(tiles[xCord][yCord-1]=='B')
            yCord--;
        break;
    case 'S' :
        if(tiles[xCord++][yCord]=='B')
            xCord++;
        break;
    }

    if(PlayerIndex==0)
        color = BLUE;
    else
        color = RED;

    xTop = (tileSizeHalf - playerSizeHalf) + xCord*tileSize;
    yTop = (tileSizeHalf - playerSizeHalf) + yCord*tileSize;
    xBottom = (tileSizeHalf + playerSizeHalf) + xCord*tileSize;
    yBottom = (tileSizeHalf + playerSizeHalf) + yCord*tileSize;

    setcolor(color);
    rectangle(xTop,yTop,xBottom,yBottom);
    setfillstyle(1,color);
    floodfill(xTop+1,yTop+1,color);

    players[PlayerIndex].x = xCord;
    players[PlayerIndex].y = yCord;
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
    unsigned short xCord = players[PlayerIndex];
    unsigned short yCord = players[PlayerIndex];
    unsigned short xCenter = tileSizeHalf + xCord*tileSize;
    unsigned short yCenter = tileSizeHalf + yCord*tileSize;
}

void playerHit(unsigned short PlayerIndex) {
    if (--players[PlayerIndex].life <= 0) {
        gameOver();
    }
}

void gameOver() {
    // game is now over
    // walk on home boy!
    // and do something useful to actually make game over
    // or simply make games state = 0
    gameState = 0;
}

void resultScreen () {
    if (players[0].life == players[1].life) {
        printf("THE GAME IS DRAW");
    } else if(players[0].life > 0) {
        printf("PLAYER 0 WINS!");
    } else {
        printf("PLAYER 1 WINS!");
    }
}

void main () {
    int gd=DETECT, gm, flag=0;
    unsigned short player;
    // int x=10, y=10;
    char ch, dir;
    float time;

    //clrscr();

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // lets setup the level
    setup();
    gameState = 1;

    while (gameState) {
        //cleardevice();

        if (kbhit()) {
            ch = getch();
            flag = 1;
        }

        if (ch == 'q' || ch == 'Q')
            break;

        if (flag) {
		printf("%d",ch);
            switch (ch) {
                // cases for player 1:
                // using wasd keys
                // and SPACE BAR for placing bomb
                case 'w':
                    player = 0;
                    dir = "N";
                    break;
                case 'd':
                    player = 0;
                    dir = "E";
                    break;
                case 'a':
                    player = 0;
                    dir = "W";
                    break;
                case 'S':
                    player = 0;
                    dir = "S";
                    break;
                case ' ':
                    player = 0;
                    dir = "B";

                // cases for player 2:
                // using arrow keys
                // and 0 for placing bomb
                case 72: // up key
                    player = 1;
                    dir = "N";
                    break;
                case 77: // right key
                    player = 1;
                    dir = "E";
                    break;
                case 75: // left key
                    player = 1;
                    dir = "W";
                    break;
                case 74: // down key
                    player = 1;
                    dir = "S";
                    break;
                case 48: // for zero
                    player = 1;
                    dir = "B";
                    break;

            }
            movePlayer(player, dir);
        }

        // reset flags etc.
        flag = 0;
    }

    // a thank you screen if you want!

    closegraph();
}
