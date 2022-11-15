#include "user.h"
#include "function.h"

//getopt要用到的
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;
int getopt(int argc, char * const *argv, const char *optstring);

//#define ROW 9
//#define COL 9

int i, j;
user *chess_board;
char neworload[25];
user *userme;
user *useryou;
FILE *fptr;



//讓各方皆可下250手並記錄
user usermee[250];
user useryouu[250];

user chess_boardd;

int *rearone, *reartwo;
int front1 = 0, rear11 = 0, front2 = 0, rear22 = 0;
//front1 尾巴 0代表未動過的棋盤
//rear1 頭頭 1代表第一手 先動再放資料

char forb;//往下或往上
int counter=1;//%2 = 1為user1
//user loadchess_board[500];//復盤用
int loadfront=1, loadrear=0;


int breaking =0;

int c;//getopt要用的
int mode = 0;//模式選項 1等於開新局 2等於讀檔


int main(int argc, char ** argv)
{
    //宣告一些位置
    chess_board = &chess_boardd;
    userme =  &usermee[0];   
    useryou = &useryouu[0];
    rearone = &rear11;
    reartwo = &rear22;
    
    //開始getopt
    opterr = 0;
    while((c = getopt(argc, argv, "ns:l:")) != -1)
    {
        switch(c)
        {
            case 'n':
                //printf("-n被印出");
                mode = 1;
                break;

            case 's':
                //printf("-s被印出 %s", optarg);
                if((fptr = fopen(optarg, "w")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 1;
                break;

            case 'l':
                //printf("-l被印出 %s", optarg);
                if((fptr = fopen(optarg, "r")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 2;
                break;

                

        }

    }

    //chess_board = &chess_boardd;
    //initgame(chess_board);

    /*userme =  &usermee[0];   
    useryou = &useryouu[0];
    rearone = &rear11;
    reartwo = &rear22;*/
    
    //開始遊戲
    if(mode == 1)
    {
        initgame(chess_board);
        game(rearone, reartwo);

        while((front1 != rear11+1) && (front2 != rear22+1))
        {
            front1 +=1;
            fprintf(fptr, "%d %d %d %d\n", usermee[front1].orignrow, usermee[front1].origncol, usermee[front1].afterrow, usermee[front1].aftercol);
            front2 +=1;
            fprintf(fptr, "%d %d %d %d\n", useryouu[front2].orignrow, useryouu[front2].origncol, useryouu[front2].afterrow, useryouu[front2].aftercol);
        }



    }

    if(mode == 2)
    {
        initgame(chess_board);
        load();
    }
    //initgame(chess_board);
    //game(rearone, reartwo);



    /*printf("輸入s儲存剛剛那盤局:");
    scanf("%c",);*/
    /*if((fptr = fopen("record.txt","w")) == NULL)
    {
        printf("已有此資料名");
    }
    else
    {
        while((front1 != rear11+1) && (front2 != rear22+1))
        {
            front1 +=1;
            fprintf(fptr, "%d %d %d %d\n", usermee[front1].orignrow, usermee[front1].origncol, usermee[front1].afterrow, usermee[front1].aftercol);
            front2 +=1;
            fprintf(fptr, "%d %d %d %d\n", useryouu[front2].orignrow, useryouu[front2].origncol, useryouu[front2].afterrow, useryouu[front2].aftercol);
        }
        fclose(fptr);

        
    }*/
    /*if((fptr = fopen("record.txt","r")) == NULL)
    {
        printf("File could not be open.\n");
    }
    else
    {
        initgame(chess_board);
        load();
    }*/

    fclose(fptr);
    //load();

    


    return 0;
}


//初始化棋盤
void initgame (user * chessboard)
{
    for (i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        chessboard->userchess_board[i][j] = ' ';
    }
    
}

//開始遊戲
void game(int * rear1, int * rear2)
{
    //初始化雙方
    creat_user1(userme);//usermee[0] = 原始棋盤
    creat_user2(useryou);//useryouu[0] = 原始棋盤
    printchess(userme, useryou, chess_board);

    //開始下棋
    //user1輸入
    *rear1 += 1;
    usermee[*rear1] = usermee[*rear1-1];
    userme = &usermee[*rear1];
    printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    scanf("%d%d%d%d", &usermee[*rear1].orignrow, &usermee[*rear1].origncol, &usermee[*rear1].afterrow, &usermee[*rear1].aftercol);
    user1move(userme, useryou);
    printchess(userme, useryou, chess_board);
    //第二手開始進入迴圈
    while(1)
    {
        *rear2 += 1;
        useryouu[*rear2] = useryouu [*rear2-1];
        useryou = &useryouu[*rear2];
        printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
        scanf("%d%d%d%d", &useryouu[*rear2].orignrow, &useryouu[*rear2].origncol, &useryouu[*rear2].afterrow, &useryouu[*rear2].aftercol);
        while(1)
        {
            if((useryouu[*rear2].orignrow == 0) || (useryouu[*rear2].origncol == 0) || (useryouu[*rear2].afterrow == 0) || (useryouu[*rear2].aftercol == 0))
            {
                //user2輸入為0代表user1悔棋
                *rear1 = *rear1 - 1;
                if(*rear1 == (-1))
                {

                    printf("\n輸入不正確，請重新輸入\n");
                    *rear1 +=1;
                    break;
                }
                userme = &usermee[*rear1];
                *rear2 = *rear2 - 1;
                if(*rear2 == (-1))
                {
                    *rear2 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((useryouu[*rear2].tmprow != (-1)) && (useryouu[*rear2].tmpcol != (-1)))
                {
                    useryouu[*rear2].userchess_board[useryouu[*rear2].tmprow][useryouu[*rear2].tmpcol] = useryouu[*rear2].tmp;
                    useryouu[*rear2].tmprow = (-1);
                    useryouu[*rear2].tmpcol = (-1);
                }
                useryou = &useryouu[*rear2];
                printchess(userme, useryou, chess_board);
                *rear1 += 1;
                usermee[*rear1] = usermee[*rear1-1];
                userme = &usermee[*rear1];
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &usermee[*rear1].orignrow, &usermee[*rear1].origncol, &usermee[*rear1].afterrow, &usermee[*rear1].aftercol);
                
                //user1輸入0代表user2悔棋
                if((usermee[*rear1].orignrow == 0) || (usermee[*rear1].origncol == 0) || (usermee[*rear1].afterrow == 0) || (usermee[*rear1].aftercol == 0))
                {
                    *rear2 -= 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    useryou = &useryouu[*rear2];
                    *rear1 -= 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 += 1;
                        break;
                    }
                    if((usermee[*rear1].tmprow != (-1)) && (usermee[*rear1].tmpcol != (-1)))
                    {
                        usermee[*rear1].userchess_board[usermee[*rear1].tmprow][usermee[*rear1].tmpcol] = usermee[*rear1].tmp;
                        usermee[*rear1].tmprow = (-1);
                        usermee[*rear1].tmpcol = (-1);
                    }
                    userme = &usermee[*rear1];
                    printchess(userme, useryou, chess_board);
                }
                else
                {
                    user1move(userme, useryou);
                    user1eatuser2(userme,useryou);
                    printchess(userme, useryou, chess_board);
                    //判斷勝利
                    if(whowins(chess_board) == 1)
                    {
                        breaking += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(chess_board) == 2)
                    {
                        breaking +=1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                *rear2 += 1;
                useryouu[*rear2] = useryouu [*rear2-1];
                useryou = &useryouu[*rear2];
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &useryouu[*rear2].orignrow, &useryouu[*rear2].origncol, &useryouu[*rear2].afterrow, &useryouu[*rear2].aftercol);
            }
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        //rear2大於0才有辦法移動
        if(*rear2>0)
        {
            user2move(useryou, userme);
            user2eatuser1(useryou,userme);
        }
        printchess(userme, useryou, chess_board);
        //判斷勝利
        if(whowins(chess_board) == 1)
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }

        *rear1 += 1;
        usermee[*rear1] = usermee[*rear1-1];
        userme = &usermee[*rear1];
        printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
        scanf("%d%d%d%d", &usermee[*rear1].orignrow, &usermee[*rear1].origncol, &usermee[*rear1].afterrow, &usermee[*rear1].aftercol);
        while(1)
        {
            if((usermee[*rear1].orignrow == 0) || (usermee[*rear1].origncol == 0) || (usermee[*rear1].afterrow == 0) || (usermee[*rear1].aftercol == 0))
            {
                //user1輸入為0代表user2悔棋
                *rear2 -= 1;
                if(*rear2 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    *rear2 +=1;
                    break;
                }
                useryou = &useryouu[*rear2];
                *rear1 -= 1;
                if(*rear1 == (-1))
                {
                    *rear1 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                if((usermee[*rear1].tmprow != (-1)) && (usermee[*rear1].tmpcol != (-1)))
                {
                    usermee[*rear1].userchess_board[usermee[*rear1].tmprow][usermee[*rear1].tmpcol] = usermee[*rear1].tmp;
                    usermee[*rear1].tmprow = (-1);
                    usermee[*rear1].tmpcol = (-1);
                }
                userme = &usermee[*rear1];
                printchess(userme, useryou, chess_board);
                *rear2 += 1;
                useryouu[*rear2] = useryouu[*rear2-1];
                useryou = &useryouu[*rear2];
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &useryouu[*rear2].orignrow, &useryouu[*rear2].origncol, &useryouu[*rear2].afterrow, &useryouu[*rear2].aftercol);
                
                
                //user2輸入0代表user1悔棋
                if((useryouu[*rear2].orignrow == 0) || (useryouu[*rear2].origncol == 0) || (useryouu[*rear2].afterrow == 0) || (useryouu[*rear2].aftercol == 0))
                {
                    *rear1 = *rear1 - 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 +=1;
                        break;
                    }
                    userme = &usermee[*rear1];
                    *rear2 = *rear2 - 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    if((useryouu[*rear2].tmprow != (-1)) && (useryouu[*rear2].tmpcol != (-1)))
                    {
                        useryouu[*rear2].userchess_board[useryouu[*rear2].tmprow][useryouu[*rear2].tmpcol] = useryouu[*rear2].tmp;
                        useryouu[*rear2].tmprow = (-1);
                        useryouu[*rear2].tmpcol = (-1);
                    }
                    useryou = &useryouu[*rear2];
                    printchess(userme, useryou, chess_board);
                }
                else
                {
                    user2move(useryou, userme);
                    user2eatuser1(useryou,userme);
                    printchess(userme, useryou, chess_board);
                    if(whowins(chess_board) == 1)
                    {
                        breaking += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(chess_board) == 2)
                    {
                        breaking += 1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                *rear1 += 1;
                usermee[*rear1] = usermee [*rear1-1];
                userme = &usermee[*rear1];
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &usermee[*rear1].orignrow, &usermee[*rear1].origncol, &usermee[*rear1].afterrow, &usermee[*rear1].aftercol);
            }
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        if(*rear1 >0)
        {
            user1move(userme, useryou);
            user1eatuser2(userme,useryou);
        }
        printchess(userme, useryou, chess_board);
        if(whowins(chess_board) == 1)//判斷誰贏
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }
    }
}

//載入棋譜
void load()
{
    creat_user1(userme);
    creat_user2(useryou);

    //讀取資料
    rear11 += 1;
    fscanf(fptr,"%d%d%d%d", &usermee[rear11].orignrow, &usermee[rear11].origncol, &usermee[rear11].afterrow, &usermee[rear11].aftercol);
    while(1)
    {
        if((usermee[rear11].orignrow==0) && (usermee[rear11].origncol==0) && (usermee[rear11].afterrow==0) &&(usermee[rear11].aftercol==0))
        {
            usermee[rear11].orignrow = -1;
            usermee[rear11].origncol = -1;
            usermee[rear11].afterrow = -1;
            usermee[rear11].aftercol = -1;
            break;
        }
        else
        {
            rear22 += 1;
            fscanf(fptr,"%d%d%d%d", &useryouu[rear22].orignrow, &useryouu[rear22].origncol, &useryouu[rear22].afterrow, &useryouu[rear22].aftercol);
        }
        
        if((useryouu[rear22].orignrow==0) && (useryouu[rear22].origncol==0) && (useryouu[rear22].afterrow==0) &&(useryouu[rear22].aftercol==0))
        {
            useryouu[rear22].orignrow = -1;
            useryouu[rear22].origncol = -1;
            useryouu[rear22].afterrow = -1;
            useryouu[rear22].aftercol = -1;
            break;
        }
        else
        {
            rear11 += 1;
            fscanf(fptr,"%d%d%d%d", &usermee[rear11].orignrow, &usermee[rear11].origncol, &usermee[rear11].afterrow, &usermee[rear11].aftercol);
        }
    }

    //判斷迴圈數
    if(useryouu[rear22].orignrow = -1)
    {
        loadrear = rear11 + rear22 -1;
    }
    else
    {
        loadrear = rear11 + rear22;
    }

    //看資料對否 之後註解
    /*printf("%d %d\n", rear11, rear22);
    while((front1 != rear11) && (front2 != rear22))
    {
        front1 += 1;
        printf("front1 = %d %d  ", front1, front2);
        printf("%d %d %d %d\n", usermee[front1].orignrow, usermee[front1].origncol, usermee[front1].afterrow, usermee[front1].aftercol);
        front2 += 1;
        printf("front2 = %d %d  ", front1, front2);
        printf("%d %d %d %d\n", useryouu[front2].orignrow, useryouu[front2].origncol, useryouu[front2].afterrow, useryouu[front2].aftercol);
    }*/

    //寫進棋盤
    front1 = 0;
    front2 = 0;
    front1 += 1;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COL;j++)
        {
            usermee[front1].userchess_board[i][j] = usermee[front1-1].userchess_board[i][j];
        }
    }
    userme = &usermee[front1];
    user1move(userme, useryou);
    while((front1 != rear11) && (front2 != rear22))
    {
        if(useryouu[front2].orignrow != -1)
        {
            front2 += 1;
            for(i=0;i<ROW;i++)
            {
                for(j=0;j<COL;j++)
                {
                    useryouu[front2].userchess_board[i][j] = useryouu[front2-1].userchess_board[i][j];
                }
            }
            //user1eatuser2(userme,useryou);
            useryou = &useryouu[front2];
            user2move(useryou, userme);
            user2eatuser1(useryou,userme);
            
        }
        else
        {
            break;
        }

        if(usermee[front1].orignrow != -1)
        {
            front1 += 1;
            for(i=0;i<ROW;i++)
            {
                for(j=0;j<COL;j++)
                {
                    usermee[front1].userchess_board[i][j] = usermee[front1-1].userchess_board[i][j];
                }
            }
            //user2eatuser1(useryou,userme);
            userme = &usermee[front1];
            user1move(userme, useryou);
            user1eatuser2(userme,useryou);
            
        }
        else
        {
            break;
        }
    }    


    front1 =0;
    front2 = 0;
    userme = &usermee[front1];
    useryou = &useryouu[front2];
    
    printchess(userme, useryou, chess_board);

    printf("輸入f代表下一步,輸入b代表上一步：");
    scanf("%1s", &forb);
    printf("\n");
    while(loadfront <= loadrear)
    {
        if((counter %2)==1)
        {
            if(forb == 'f')
            {
                front1 += 1;
                userme = &usermee[front1];
                //printf("\n%d %d %d %d",usermee[front1].orignrow, usermee[front1].origncol, usermee[front1].afterrow, usermee[front1].aftercol);
                //printf("\n'%c' %d %d\n",useryouu[front2].tmp, useryouu[front2].tmprow, useryouu[front2].tmpcol);
                printchess(userme, useryou, chess_board);
                counter += 1;
                loadfront += 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &forb);
            }
            else if(forb == 'b')
            {
                front2 -= 1;
                if(front2 < 0)
                {
                    front2 = 0;
                    counter -= 1;
                }
                useryou = &useryouu[front2];
                printchess(userme, useryou, chess_board);
                counter += 1;
                loadfront -= 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &forb);

            }
        }

        else if((counter % 2)==0)
        {
            if(forb == 'f')
            {
                front2 += 1;
                useryou = &useryouu[front2];
                //printf("\n%d %d %d %d", useryouu[front2].orignrow, useryouu[front2].origncol, useryouu[front2].afterrow, useryouu[front2].aftercol);
                //printf("\n'%c' %d %d\n",usermee[front1].tmp, usermee[front1].tmprow, usermee[front1].tmpcol);
                printchess(userme, useryou, chess_board);
                counter += 1;
                loadfront += 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &forb);
            }
            else if(forb == 'b')
            {
                front1 -= 1;
                if(front1 < 0)
                {
                    front1 = 0;
                    counter -= 1;
                }
                userme = &usermee[front1];
                printchess(userme, useryou, chess_board);
                counter += 1;
                loadfront -= 1;
                printf("輸入f代表下一步,輸入b代表上一步：");
                scanf("%1s", &forb);
            }
        }

        if(loadfront == (loadrear+1))
        {
            if(forb == 'b')
            {
                loadfront -= 1;
            }
            else if(forb == 'f')
            {
                break;
            }
        }

       
    }
    printf("\n復盤結束!\n");
            

}


//將兩個分別的棋盤變成一個大棋盤再印出棋盤
void printchess(user const * user1, user const * user2,  user * chessboard)
{
    printf("  1   2   3   4   5   6   7   8   9 \n");
    printf("|---|---|---|---|---|---|---|---|---|\n");
    for(i = 0;i < ROW; i++)
    {
        for(j = 0;j < COL; j++)
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

void user1move(user * user11, user * user22)
{
    //移動棋子
    while(1)
    {
        if((user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)] != ' ') && (user11->userchess_board[(user11->afterrow -1)][(user11->aftercol -1)]) == ' ')
        {
            if(user1chessandmove(user11, user22) == 1)
            {
                user11->userchess_board[(user11->afterrow -1)][(user11->aftercol -1)] = user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)];
                user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)] = ' ';
                break;
            }
            else
            {
                printf("\n輸入不正確 請重新輸入\n");
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &user11->orignrow, &user11->origncol, &user11->afterrow, &user11->aftercol);
            }
        }
        else
        {
            printf("\n輸入不正確 請重新輸入\n");
            printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
            scanf("%d%d%d%d", &user11->orignrow, &user11->origncol, &user11->afterrow, &user11->aftercol);
        }
    }
}

void user2move(user * user22, user * user11)
{
    //移動棋子
    while(1)
    {
        if((user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)] != ' ') && (user22->userchess_board[(user22->afterrow -1)][(user22->aftercol -1)]) == ' ')
        {
            if(user2chessandmove(user22, user11) == 1)
            {
                user22->userchess_board[(user22->afterrow -1)][(user22->aftercol -1)] = user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)];
                user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)] = ' ';
                break;
            }
            else
            {
                printf("\n輸入不正確 請重新輸入\n");
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
                scanf("%d%d%d%d", &user22->orignrow, &user22->origncol, &user22->afterrow, &user22->aftercol);
            }
        }
        else
        {
            printf("\n輸入不正確 請重新輸入\n");
            printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:");
            scanf("%d%d%d%d", &user22->orignrow, &user22->origncol, &user22->afterrow, &user22->aftercol);
        }
    }
}

//user1吃掉user2的子
void user1eatuser2(user * user1, user * user2)
{
    if(user2->userchess_board[user1->afterrow -1][user1->aftercol -1] != ' ')
    {
        //暫存user2被吃掉的棋
        user2->tmp = user2->userchess_board[user1->afterrow -1][user1->aftercol -1];
        user2->tmprow = user1->afterrow -1;
        user2->tmpcol = user1->aftercol -1;
        user2->userchess_board[user1->afterrow -1][user1->aftercol -1] = ' ';
    }
}

//user2吃掉user1的子
void user2eatuser1(user * user2, user * user1)
{
    if(user1->userchess_board[user2->afterrow -1][user2->aftercol -1] != ' ')
    {
        //暫存user1被吃掉的棋
        user1->tmp = user1->userchess_board[user2->afterrow -1][user2->aftercol -1];
        user1->tmprow = user2->afterrow - 1;
        user1->tmpcol = user2->aftercol - 1;
        user1->userchess_board[user2->afterrow -1][user2->aftercol -1] = ' ';
    }
}

//user1贏回傳1 user2贏回傳2 沒人贏回傳0
int whowins(user * chessboard)
{
    int tmp1=0;
    int tmp2=0;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(chessboard->userchess_board[i][j] =='U')
            {
                tmp1 = 1;
            }
            else if(chessboard->userchess_board[i][j] =='w')
            {
                tmp2 =1;
            }
        }
    }

    if((tmp1 == 1)&&(tmp2 == 0))
    {
        return 1;
    }
    else if((tmp1 == 0)&&(tmp2 == 1))
    {
        return 2;
    }
    else
    {
        return 0;
    }

}


