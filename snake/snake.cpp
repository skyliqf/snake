
#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define H 22
#define W 22
using namespace std;

class SnakeBoard
{
public:
    char board[H][W];
    int i, j, x1, y1;
    SnakeBoard();
    void food();
    void prt(int grade, int score, int gamespeed);
};
//创建游戏区域
SnakeBoard::SnakeBoard()
{
    for (i = 1; i <= H - 2; i++)
        for (j = 1; j <= W - 2; j++)
            board[i][j] = ' ';
    for (i = 0; i <= H - 1; i++)
        board[0][i] = board[H - 1][i] = '#';
    for (i = 1; i <= H - 2; i++)
        board[i][0] = board[i][W - 1] = '#';
    food();
}
//在区域范围你生成随机数
void SnakeBoard::food()
{
    srand(time(0));
    do
    {
        x1 = rand() % W - 2 + 1; //随机数为0呢
        y1 = rand() % H - 2 + 1;
    } while (board[x1][y1] != ' ');
    board[x1][y1] = '$';
}
//打印区域
void SnakeBoard::prt(int grade, int score, int gamespeed)
{
    system("cls");
    cout << endl;
    for (int i = 0; i < H; i++)
    {
        cout << "\t";
        for (j = 0; j < W; j++)
            cout << board[i][j] << ' ';
        if (i == 0) cout << "\tGrade:" << grade;
        if (i == 2) cout << "\tScore:" << score;
        if (i == 4) cout << "\tAutomatic forward";
        if (i == 6) cout << "\ttime interval:" << gamespeed << "ms";
        if (i == 12) cout << "\tBy skyliqf";
        if (i == 14) cout << "\t2020.01.04";
        cout << endl;
    }
}

class Snake :public SnakeBoard
{
public:
    int snake[2][100];
    long start;
    int head, tail, grade, score, gamespeed, length, timeover, x, y;
    char direction;
    Snake();
    void move();
};
Snake::Snake()
{
    cout << "\n\n\t\tThe game is about to start!" << endl;
    for (int i = 3; i >= 0; i--)
    {
        start = clock();
        while (clock() - start <= 1000); //计时1S
        system("cls");  //清屏函数
        if (i == 3)
            cout << "\n\n\t\tthree" << endl;
        if (i == 2)
            cout << "\n\n\t\ttwo" << endl;
        if (i == 1)
            cout << "\n\n\t\tone" << endl;
        if (i == 0)
            cout << "\n\n\t\tgo " << endl;
    }

    for (i = 1; i <= 3; i++)
        board[1][i] = '*';
    board[1][4] = '@';
    for (i = 0; i < 4; i++)
    {
        snake[0][i] = 1;
        snake[1][i] = i + 1;
    }
}
void Snake::move()
{
    score = 0;
    head = 3, tail = 0;
    grade = 1, length = 4;
    gamespeed = 400;
    direction = 77;
    while (1)
    {
        timeover = 1;
        start = clock();
        while ((timeover = (clock() - start <= gamespeed)) && !_kbhit());//wait for the key to be pressed
        if (timeover)
        {
            _getch();
            direction = _getch();
        }
        switch (direction)
        {
        case 72: x = snake[0][head] - 1; y = snake[1][head]; break; //上
        case 80: x = snake[0][head] + 1; y = snake[1][head]; break; //下
        case 75: x = snake[0][head]; y = snake[1][head] - 1; break; //左
        case 77: x = snake[0][head]; y = snake[1][head] + 1; break; //右
        }
        if (x == 0 || x == H || y == 0 || y == W)  //判断是否接触墙壁
        {
            cout << "\tGame over!" << endl; break;
        }
        if (board[x][y] != ' ' && !(x == x1 && y == y1))
        {
            cout << "\tGame over!" << endl; break;
        }
        if (x == x1 && y == y1)
        {
            length++;
            score = score + 100;
            if (length >= 8)
            {
                length -= 8;
                grade++;
                if (gamespeed >= 200)
                    gamespeed = 550 - grade * 50;
            }
            board[x][y] = '@';
            board[snake[0][head]][snake[1][head]] = '*';
            head = (head + 1) % 100;
            snake[0][head] = x;
            snake[1][head] = y;
            food();//产生食物
            prt(grade, score, gamespeed);
        }
        else
        {
            board[snake[0][tail]][snake[1][tail]] = ' ';
            tail = (tail + 1) % 100;
            board[snake[0][head]][snake[1][head]] = '*';
            head = (head + 1) % 100;
            snake[0][head] = x;
            snake[1][head] = y;
            board[snake[0][head]][snake[1][head]] = '@';
            prt(grade, score, gamespeed);
        }
    }
}
int main()
{
    Snake s;
    s.move();
}
