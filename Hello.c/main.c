#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

typedef struct cord {
    int x;
    int y;
} cord;

void move(cord s[], int a, int b, int n);
int chekgg(cord s[], int n);
cord geng(int s[][16], int n);

int main()
{
    int i = 0, j = 0, k = 0, len = 1, f = 1, level = 0;
    int scr[16][16] = { 0 };
    cord snake[226] = { {1,1} }, goal = { 0,0 };
    char key;
    scr[1][1] = 1;
    srand(time(NULL));
    goal = geng(scr, len);
    printf("난이도를 선택해주세요!\n");
    printf("1. Easy\n");
    printf("2. Normal\n");
    printf("3. Hard\n");
    printf("그 외: 거북이");
    key = _getch();
    switch (key) {
    case '1':
        level = 1000000;
        break;
    case '2':
        level = 500000;
        break;
    case '3':
        level = 0;
        break;
    default:
        level = 3000000;
    }
    while (len < 225) {
        for (k = len; k >= 0; k--) {
            j = snake[k].x;
            i = snake[k].y;
            if (k == 0) scr[i][j] = 2;
            else if (k != len) scr[i][j] = 1;
            else scr[i][j] = 0;
        }
        system("cls");
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 16; j++) {
                if (scr[i][j] == 2) printf("●");
                else if (scr[i][j]) printf("■");
                else if (goal.y == i && goal.x == j) printf("★");
                else if (i == 0 || j == 0) printf("□");
                else printf("  ");
            }
            printf("\n");
        }
        for (i = 0; i < level; i++) {
            printf("");
        }
        if (_kbhit()) key = _getch();

        switch (key) {
        case 'w': case'W':
            move(snake, 0, -1, len);
            break;
        case 'a': case'A':
            move(snake, -1, 0, len);
            break;
        case 's': case'S':
            move(snake, 0, 1, len);
            break;
        case 'd': case'D':
            move(snake, 1, 0, len);
            break;
        default:
            continue;
        }
        scr[snake[0].y][snake[0].x] = 1;
        if (chekgg(snake, len)) {
            f = 0;
            break;
        }
        if (snake[0].x == goal.x && snake[0].y == goal.y) {
            len++;
            goal = geng(scr, len);
        }

    }
    if (f) printf("CLEAR 수고하셨습니다.\n");
    else printf("GG\n");


    return 0;
}
void move(cord s[], int a, int b, int n)
{
    int i = 0;
    for (i = n - 1; i >= 0; i--) {
        s[i + 1] = s[i];
    }
    s[0].x += a;
    s[0].y += b;
}
int chekgg(cord s[], int n)
{
    int i;
    if (s[0].x < 1 || s[0].y < 1 || s[0].x > 15 || s[0].y > 15) return 1;
    for (i = 1; i < n; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y) return 1;
    }
    return 0;

}
cord geng(int s[][16], int n)
{
    int i = -1, cnt = 0, r = 0;
    cord ngoal = { 0,0 };
    if (n == 225) return ngoal;
    r = rand() % (225 - n) + 1;
    while (cnt < r) {
        i++;
        if (s[i / 15 + 1][i % 15 + 1] == 0) cnt++;
    }
    if (cnt == r) {
        ngoal.y = i / 15 + 1;
        ngoal.x = i % 15 + 1;
    }
    return ngoal;
}