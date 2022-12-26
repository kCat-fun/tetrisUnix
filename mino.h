const int MINO_TYPE[7][4][4] = {
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,0,1,1},
        {0,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,1},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,0,0,1},
        {0,1,1,1},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    },
    {
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,1},
        {0,0,0,0}
    }
};

typedef struct {
    int x, y, id;
    int mino[4][4];
} TetroMino;

void colorMino(int n) {
    switch(n) {
    case 1:
        printf("\x1b[31m#\x1b[0m");
        break;
    case 2:
        printf("\x1b[32m#\x1b[0m");
        break;
    case 3:
        printf("\x1b[34m#\x1b[0m");
        break;
    case 4:
        printf("\x1b[37m#\x1b[0m");
        break;
    case 5:
        printf("\x1b[36m#\x1b[0m");
        break;
    case 6:
        printf("\x1b[33m#\x1b[0m");
        break;
    case 7:
        printf("\x1b[35m#\x1b[0m");
        break;
    }
}

void draw_field(TetroMino *tetroMino, TetroMino *nextMino) {
    int x=tetroMino->x, y=tetroMino->y;
    for(int i=0; i<20; i++) {
        printf("X");
        for(int j=0; j<10; j++) {
            if(field[i][j] > 0) {
                colorMino(field[i][j]);
            }
            else if( 0<=i-y && i-y<4 && 0<=j-x && j-x<4) {
                if(tetroMino->mino[i-y][j-x] == 1) {
                    colorMino(tetroMino->id);
                }
                else {
                    printf(" ");
                }
            }
            else {
                printf(" ");
            }
        }
        if(3<=i&&i<7) {
            printf("XX");
            for(int j=0; j<4; j++) {
                if(nextMino->mino[i-3][j] > 0) {
                    printf("O");
                }
                else {
                    printf(" ");
                }
            }
            printf("X\n");
        }
        else {
            printf("XXXXXXX\n");
        }
    }
    for(int i=0; i<18; i++) {
        printf("X");
    }
    printf("\n");
}

void randMino(TetroMino *tetroMino) {
    int n = rand() % 7;
    tetroMino->id = n+1;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            tetroMino->mino[i][j] = MINO_TYPE[n][i][j];
        }
    }
    tetroMino->x = 3;
    tetroMino->y = -3;
}

void deleteMino() {
    bool flag;
    for(int i=0; i<20; i++) {
        flag = true;
        for(int j=0; j<10; j++) {
            if(field[i][j] == 0) {
                flag = false;
                break;
            }
        }
        if(flag == false) continue;
        for(int n=i; n>0; n--) {
            for(int j=0; j<10; j++) {
                field[n][j] = field[n-1][j];
            }
        }
        for(int j=0; j<10; j++) {
            field[0][j] = 0;
        }
        i--;
    }        
}

void minoPosition(TetroMino *tetroMino, int *arr) {
    int w=0, h=0, left=-1, top=-1;
    int pos[4];

    for(int i=0; i<4; i++) {
        bool flag = false, flag2 = false;
        for(int j=0; j<4; j++) {
            if(tetroMino->mino[j][i] == 1 && flag2 == false) {
                w++;
                flag2 = true;
            }
            if(tetroMino->mino[i][j] == 1) {               
                if(flag == false) {
                    h++;
                    flag = true;
                }
                if(left == -1 || left > j) {
                    left = j;
                }
                if(top == -1) {
                    top = i;
                }
            }
        }
    }

    pos[0] = top;
    pos[1] = left;
    pos[2] = h;
    pos[3] = w;
    // printf("t:%d l:%d h:%d w:%d", pos[0], pos[1], pos[2], pos[3]);
    
    for(int i=0; i<4; i++) {
        arr[i] = pos[i];
    }
}

bool checkGround(TetroMino *tetroMino, int dy) {
    int x=tetroMino->x, y=tetroMino->y+dy;
    int bottom=0;
    int pos[4];

    minoPosition(tetroMino, pos);
    bottom = y+pos[0]+pos[2]-1;

    if(bottom >= 20)
        return true;
    return false;
}

bool checkBottom(TetroMino *tetroMino, int dy) {
    int x=tetroMino->x, y=tetroMino->y+dy;
    for(int i=0; i<4;i++) {
        for(int j=0; j<4; j++) {
            if(tetroMino->mino[i][j] > 0) {
                if(field[y+i][x+j] > 0) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool checkOver(TetroMino *tetroMino) {
    bool flag = false;
    if(tetroMino->y < 0) {
        return true;
    }
    return false;
}

void fixMino(TetroMino *tetroMino) {
    int x=tetroMino->x, y=tetroMino->y;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(tetroMino->mino[i][j] == 1) {
                field[y+i][x+j] = tetroMino->id;
            }
        }
    }
    deleteMino();
    if(checkOver(tetroMino) == true) {
        printf("Game Over\n");
        exit(0);
    }
}


bool moveCheck(TetroMino *tetroMino, int dx, int dy) {
    int x=tetroMino->x+dx, y=tetroMino->y+dy;
    int right=0, bottom=0, left=0, top=0;
    int pos[4];

    minoPosition(tetroMino, pos);
    top = pos[0];
    left = pos[1];
    bottom = pos[2]+top-1;
    right = pos[3]+left-1;

    if(x+left < 0 || 10 < x + right + 1 || checkGround(tetroMino, dy)) {
        return false;
    }
    
    for(int i=0; i<20; i++) {
        for(int j=0; j<10; j++) {
            if( 0<=i-y && i-y<4 && 0<=j-x && j-x<4) {
                if(tetroMino->mino[i-y][j-x] == 1 && field[i][j] == 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

// direction: 1->right, -1->left
void rotateMino(TetroMino *tetroMino, int direction) {
    int temp[4][4];
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            temp[i][j] = tetroMino->mino[i][j];
        }
    }
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            // right
            if(direction > 0) {
                tetroMino->mino[i][j] = temp[3-j][i];
            }
            // left
            else if(direction < 0) {
                tetroMino->mino[i][j] = temp[j][3-i];
            }
        }
    }
    
}
