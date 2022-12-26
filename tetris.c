#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "keybord.h"
#include "init.h"
#include "mino.h"

int main(void) {
    srand((unsigned int)time(NULL));
    TetroMino tetroMino, nextMino;
    int c=0, count = 0, t=0;
    double startTime;
    randMino(&tetroMino);
    randMino(&nextMino);
    do {
        startTime = clock() / CLOCKS_PER_SEC ;
        if (kbhit()) {
            system("clear");
            c = getchar();
            // printf("%d\n", c);
            switch(c) {
            case 65: // up
                if(moveCheck(&tetroMino, 0, -1) == true)
                    tetroMino.y--;
                break;
            case 66: // down
                if(moveCheck(&tetroMino, 0, 1) == true)
                    tetroMino.y++;
                break;
            case 67: // right
                if(moveCheck(&tetroMino, 1, 0) == true)
                    tetroMino.x++;
                break;
            case 68: //left
                if(moveCheck(&tetroMino, -1, 0) == true)
                    tetroMino.x--;
                break;
            case 32: // space
                for(t=1; checkGround(&tetroMino, t) == false && checkBottom(&tetroMino, t) == false; t++);
                tetroMino.y += t-1;
                break;
            case 120: // x: rotate right
                rotateMino(&tetroMino, 1);
                if(moveCheck(&tetroMino, 0, 0)  == false)
                    rotateMino(&tetroMino, -1);
                break;
            case 122: // z: rotate left
                rotateMino(&tetroMino, -1);
                if(moveCheck(&tetroMino, 0, 0) == false)
                    rotateMino(&tetroMino, 1);
                break;
            
            }
            draw_field(&tetroMino, &nextMino);
        }
        if(checkGround(&tetroMino, 1) == true || checkBottom(&tetroMino, 1) == true) {
            fixMino(&tetroMino);
            tetroMino = nextMino;
            randMino(&nextMino);
            system("clear");
            draw_field(&tetroMino, &nextMino);
        }
        if(startTime > count) {
            count++;
            tetroMino.y++;
            system("clear");
            draw_field(&tetroMino, &nextMino);
        }
    } while(c != 113); // q: finish
    system("clear");
    return 0;
}

