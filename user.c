//兩個user初始化和印出
#include "user.h"

int a, b;



void creat_user1(user *user1)
{
    //初始化
    for (a = 0; a < ROW; a++)
    {
        for (b = 0; b < COL; b++)
        {
            user1->userchess_board[a][b] = ' ';
        }
    }

    //排列位置
    for(a = 0; a < COL; a++)
    {
        user1->userchess_board[6][a] = 'B';
    }

    user1->userchess_board[7][1] = 'J';
    user1->userchess_board[7][7] = 'F';
    
    user1->userchess_board[8][0] = 'H';
    user1->userchess_board[8][1] = 'G';
    user1->userchess_board[8][2] = 'I';
    user1->userchess_board[8][3] = 'K';
    user1->userchess_board[8][4] = 'U';
    user1->userchess_board[8][5] = 'K';
    user1->userchess_board[8][6] = 'I';
    user1->userchess_board[8][7] = 'G';
    user1->userchess_board[8][8] = 'H';

    //初始化被吃棋
    user1->tmp = ' ';
    user1->tmprow = (-1);
    user1->tmpcol = (-1);
}

void creat_user2(user *user2)
{
    //初始化
    for (a = 0; a < ROW; a++)
    {
        for (b = 0; b < COL; b++)
        {
            user2->userchess_board[a][b] = ' ';
        }
    }

    //排列位置
    for(a = 0; a < COL; a++)
    {
        user2->userchess_board[2][a] = 'b';
    }

    user2->userchess_board[1][7] = 'j';
    user2->userchess_board[1][1] = 'f';
    
    user2->userchess_board[0][0] = 'h';
    user2->userchess_board[0][1] = 'g';
    user2->userchess_board[0][2] = 'i';
    user2->userchess_board[0][3] = 'k';
    user2->userchess_board[0][4] = 'w';
    user2->userchess_board[0][5] = 'k';
    user2->userchess_board[0][6] = 'i';
    user2->userchess_board[0][7] = 'g';
    user2->userchess_board[0][8] = 'h';

    user2->tmp = ' ';
    user2->tmprow = (-1);//初始化-1代表沒東西
    user2->tmpcol = (-1);
}

//轉換成中文字並印出藍色字
void chineseuser1 (char letter)
{
    switch (letter)
    {
        case 'B':
            printf("|\033[34m 步\033[m");
            break;

        case 'J':
            printf("|\033[34m 角\033[m");
            break;

        case 'F':
            printf("|\033[34m 飛\033[m");
            break;

        case 'H':
            printf("|\033[34m 香\033[m");
            break;

        case 'G':
            printf("|\033[34m 桂\033[m");
            break;

        case 'I':
            printf("|\033[34m 銀\033[m");
            break;

        case 'K':
            printf("|\033[34m 金\033[m");
            break;

        default:
           printf("|\033[34m 玉\033[m");
            break; 
    }
}

//轉換成中文字並印出紅色字
void chineseuser2 (char letter)
{
    switch (letter)
    {
        case 'b':
            printf("|\033[31m 步\033[m");
            break;

        case 'j':
            printf("|\033[31m 角\033[m");
            break;

        case 'f':
            printf("|\033[31m 飛\033[m");
            break;

        case 'h':
            printf("|\033[31m 香\033[m");
            break;

        case 'g':
            printf("|\033[31m 桂\033[m");
            break;

        case 'i':
            printf("|\033[31m 銀\033[m");
            break;

        case 'k':
            printf("|\033[31m 金\033[m");
            break;

        default:
           printf("|\033[31m 王\033[m");
            break; 
    }
}

//將兩個分別的棋盤變成一個大棋盤再印出棋盤
void printchess(user const * user1, user const * user2,  user * chessboard)
{
    printf("  1   2   3   4   5   6   7   8   9 \n");
    printf("|---|---|---|---|---|---|---|---|---|\n");
    for(int i = 0;i < ROW; i++)
    {
        for(int j = 0;j < COL; j++)
        {
            if(user1->userchess_board[i][j] != ' ')
            {
                chessboard->userchess_board[i][j] = user1->userchess_board[i][j];
                chineseuser1 (chessboard->userchess_board[i][j]);
            }
            else if(user2->userchess_board[i][j] != ' ')
            {
                chessboard->userchess_board[i][j] = user2->userchess_board[i][j];
                chineseuser2 (chessboard->userchess_board[i][j]);
            }
            else
            {
                chessboard->userchess_board[i][j] = ' ';
                printf("| %c ", chessboard->userchess_board[i][j]);
            }
        }
        if(i < ROW)
        {
            printf("| %d\n|---|---|---|---|---|---|---|---|---|\n",i+1);
        }
    }
    printf("\n\n");
}

//不要的東西
/*rear2 += 1;
    useryouu[rear2] = useryouu [rear2-1];
    useryou = &useryouu[rear2];
    printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    scanf("%d%d%d%d", &useryouu[rear2].orignrow, &useryouu[rear2].origncol, &useryouu[rear2].afterrow, &useryouu[rear2].aftercol);
    while(1)
    {
        if((useryouu[rear2].orignrow == 0) || (useryouu[rear2].origncol == 0) || (useryouu[rear2].afterrow == 0) || (useryouu[rear2].aftercol == 0))
        {
            rear1 -= 1;
            userme = &usermee[rear1];
            rear2 -= 1;
            useryou = &useryouu[rear2];
            printchess(userme, useryou, chess_board);
            printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
            scanf("%d%d%d%d", &usermee[rear1].orignrow, &usermee[rear1].origncol, &usermee[rear1].afterrow, &usermee[rear1].aftercol);
            user1move(userme,useryou);
            printchess(userme, useryou, chess_board);
            rear2 += 1;
            useryouu[rear2] = useryouu [rear2-1];
            useryou = &useryouu[rear2];
            printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
            scanf("%d%d%d%d", &useryouu[rear2].orignrow, &useryouu[rear2].origncol, &useryouu[rear2].afterrow, &useryouu[rear2].aftercol);
        }
        else
        {
            break;
        }
    }
    user2move(useryou, userme);
    printchess(userme, useryou, chess_board);*/

       //rear2 += 1;
                        //useryouu[rear2] = useryouu [rear2-1];
                        //useryou = &useryouu[rear2];
                        //printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                        //scanf("%d%d%d%d", &useryouu[rear2].orignrow, &useryouu[rear2].origncol, &useryouu[rear2].afterrow, &useryouu[rear2].aftercol)