#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


#include <process.h>
#include <pthread.h>
using namespace std;





// ---------- ȫ�ֶ��� ----------
int changdi[30][27];
int x = 22, y = 13, fangx = 0, nextfx = -1;
int fenshu = 0, beichi = 0, douzi = 0;
int stopped = 0, dali = 0;
int fxfx[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
int ghostX = 14, ghostY = 13;
int ghostDir = 0;
int speedBoost = 0;
int frameCounter = 0;
int ghostMoveCounter = 0;  // ���֡������
int ghostMoveDelay = 3;    // ÿ����֡���ƶ�һ�ι�����Խ��Խ��


// ---------- ��ͼ ----------
int changdi1[30][27] = { 

    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,2,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,2,0,2,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,2,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,2,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,1,1,1,1,1,0,2,0,0,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,2,0,1,1,1,1,1,0,2,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,0,0,2,0,1,1,1,1,4,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,2,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    
 }; 
int changdi2[30][27] = {

    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,2,2,0,2,2,2,2,3,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,1,1,1,0,1,1,1,2,0,0,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,2,1,1,1,0,1,1,1,2,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,0,0,2,1,1,1,0,1,1,1,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,0,0,2,0,0,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    
}; 
int changdi3[30][27] = { 

    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,2,2,2,2,2,2,2,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,2,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    
 }; 

void loadMap(int lv) {
    int (*src)[27];
    if (lv == 1) src = changdi1;
    else if (lv == 2) src = changdi2;
    else src = changdi3;

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 27; j++) {
            changdi[i][j] = src[i][j];
        }
    }
}

// ---------- ���� & UI ----------
void gotoxy(int x, int y) {
    COORD pos; pos.X = 2 * y; pos.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void color(int a) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void showStartMenu() {
    system("cls");
    color(11); printf("\n    �� Welcome to the multi-level Pac-Man game! ��\n\n");
    color(7);
    printf("  1. Start game\n");
    printf("  2. Game description\n");
    printf("  3. Producer\n");
    printf("  4. Quit the game\n");
    printf("\n  Please enter a number to select��");
}

void showHelpMenu() {
    system("cls");
    color(10); printf("\n��Game description��\n\n");
    color(7);
    printf("  �� Use the arrow keys to control Pac-Man movement\n");
    printf("  �� Eat all the beans on the map to pass the level\n");
    printf("  �� �� is Pac-Man, �� is Monster, and will be eaten if touched (unless you eat Dali Pills $)\n");
    printf("  �� Eating items # can increase Pac-Man speed\n");
    printf("  �� Space bar pauses\n"); 
    printf("\n  Press any key to return to the menu...\n");
    getch();
}

void showCredits() {
    system("cls");
    color(13); printf("\n��Producer��\n\n");
    color(7);
    printf("  �� Programming implementation��LiuXiaoci\n");
    printf("  �� Inspiration: A source of inspiration for the classic Pac-Man game\n");
    printf("  �� The current version supports 3 difficulty levels with monster AI.\n");
    printf("\n  Press any key to return to the menu...\n");
    getch();
}

void showLevelResult(bool win, int lv) {
    system("cls");
    if (win) {
        color(10);  // ��ɫ
        printf("\n\n");
        printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("�U            Win!             �U\n", lv);
        printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n\n");
    } else {
        color(12);  // ��ɫ
        printf("\n\n");
        printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("�U            Game over��      �U\n", lv);
        printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n\n");
    }

    color(7);
    printf("  Current score��%d\n", fenshu);
    printf("  Number of times eaten��%d\n", beichi);
    printf("\n  Press any key to return to the menu...\n");
    getch();
}



void showGameOver(bool win, int score, int deaths) {
    system("cls");
    color(win ? 10 : 12);
    if (win) {
        printf("\n\n All levels have ended��\n\n");
    } 
    color(7);
    printf("  Final Score��%d\n", score);
    printf("  Final number of eats��%d\n", deaths);
    printf("\n  Press any key to exit the game...\n");
    getch();
}

// ---------- ��Ϸ�߼� ----------
void drawMap() {
    douzi = 0;  // ÿ�λ��Ƶ�ͼǰ�����ö��Ӽ�����

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 27; j++) {
            gotoxy(i, j);

            switch (changdi[i][j]) {
                case 0:
                    color(1); printf("��"); // ǽ��
                    break;
                case 1:
                    color(7); printf("��"); // ��ͨ����
                    douzi++;  // ����ʣ�ඹ����
                    break;
                case 2:
                    color(8); printf(" "); // �յ�
                    break;
                case 3:
                    color(13); printf("$");
                    douzi++; 
                    break;
                case 4:
                    color(6); printf("#"); // ���ٵ���
                    douzi++;  
                    break;
            }
        }
    }

    // ��ʾ���
    gotoxy(x, y);
    color(14);
    printf("��");

    // ��ʾ��
    gotoxy(ghostX, ghostY);
    color(4);
    printf("��");

}


void handleInput() {
    if (!_kbhit()) return;
    char ch = _getch();
    if (ch == 75) nextfx = 0;
    else if (ch == 80) nextfx = 1;
    else if (ch == 77) nextfx = 2;
    else if (ch == 72) nextfx = 3;
    else if (ch == ' ') stopped = !stopped;
}

void movePlayer() {
    if (nextfx != -1) {
        int nx = x + fxfx[nextfx][0];
        int ny = y + fxfx[nextfx][1];
        if (nx >= 0 && nx < 30 && ny >= 0 && ny < 27 && changdi[nx][ny] != 0) {
            gotoxy(x, y); printf(" ");
            if (changdi[nx][ny] == 1) { fenshu++; }
            else if (changdi[nx][ny] == 3) { fenshu++; dali = 1; }
            else if (changdi[nx][ny] == 4) { fenshu++; speedBoost = 1; }
            changdi[nx][ny] = 2;
            x = nx; y = ny;
            gotoxy(x, y); color(14); printf("��"); color(7);
            nextfx = -1; // �ƶ�һ��
        }
    }
}

//AI�ƶ��㷨 
void moveGhost() {
    int oppositeDir[4] = {2, 3, 0, 1}; // ��-��, ��-��, ��-��, ��-��
    int bestDir = -1;
    int minDist = 9999;

    // Ѱ�����ŷ��򣨲���ͷ��
    for (int d = 0; d < 4; d++) {
        if (d == oppositeDir[ghostDir]) continue; // �������ͷ
        int nx = ghostX + fxfx[d][0];
        int ny = ghostY + fxfx[d][1];
        if (nx >= 0 && nx < 30 && ny >= 0 && ny < 27 && changdi[nx][ny]) {
            int dx = nx - x, dy = ny - y;
            int dist = dx * dx + dy * dy;
            if (dist < minDist) {
                minDist = dist;
                bestDir = d;
            }
        }
    }

    // ���û�и���ѡ��ά��ԭ����
    if (bestDir == -1) bestDir = ghostDir;
    ghostDir = bestDir;

    // �ƶ�ǰ����ԭ����
    gotoxy(ghostX, ghostY);
    switch (changdi[ghostX][ghostY]) {
        case 1: color(7); printf("��"); break;
        case 2: color(8); printf(" "); break;
        case 3: color(13); printf("$"); break;
        case 4: color(14); printf("#"); break;
        default: printf(" ");
    }

    // �ƶ���
    ghostX += fxfx[ghostDir][0];
    ghostY += fxfx[ghostDir][1];

    // ��ʾ��
    gotoxy(ghostX, ghostY); color(4); printf("��"); color(7);

    // ��ײ���
    if (ghostX == x && ghostY == y && !dali) {
        beichi++;
    }
}

DWORD WINAPI thread_name(LPVOID lpParam) {
    printf("�߳���������׼����������...\n");
    MCIERROR err;
    char buffer[128];

    err = mciSendString("open \"D:\\pacmangame\\holiday.mp3\" alias bgm", NULL, 0, NULL);
    if (err != 0) {
        mciGetErrorString(err, buffer, 128);
        MessageBox(NULL, buffer, "���ִ�ʧ��", MB_OK);
        return 0;
    }

    mciSendString("play bgm repeat", NULL, 0, NULL);
    return 0;
}

// ---------- ��������� ----------

int main() {				 
	
	CreateThread(NULL, 0, thread_name, NULL, 0, NULL);

    // ---------- ��Ϸ���˵� ----------
    int choice, level = 1;
    do {
        showStartMenu();
        choice = getch() - '0';
        if (choice == 2) showHelpMenu();
        else if (choice == 3) showCredits();
        else if (choice == 4) {
            return 0;
        }
    } while (choice != 1);

    fenshu = 0; beichi = 0;
    bool win = false;

    while (level <= 3) {
        loadMap(level);
        fenshu = 0;         // ����
        speedBoost = 0;     // �����һ���ٶ�Ч��
        beichi = 0;         // ÿ�سԵ�����������

        x = 22; y = 13; fangx = 0; nextfx = 0;
        ghostX = 14; ghostY = 13; ghostDir = -1;

        system("cls");
        gotoxy(5, 5); printf("Start the %d level...", level);
        Sleep(1000);
        system("cls");
        drawMap();

        int ghostDelay = 400;
        int playerCounter = 0, ghostCounter = 0;

while (fenshu < douzi && !(ghostX == x && ghostY == y && !dali)) {
    handleInput();
    if (!stopped) {
        int playerDelay = speedBoost ? 50 : 150;

        playerCounter += 50;
        ghostCounter += 50;

        if (playerCounter >= playerDelay) {
            movePlayer();
            playerCounter = 0;
        }

        if (ghostCounter >= ghostDelay) {
            moveGhost();
            ghostCounter = 0;
        }
    }

    gotoxy(0, 30);
    printf("Score��%d  Eaten��%d  leftover beans��%d", fenshu, beichi, douzi - fenshu);
    Sleep(50);  // �̶����ƶ�֡��
}


        bool levelWin = (fenshu >= douzi);
    showLevelResult(levelWin, level);
    level++;
    if (level > 3) win = true;
    }

    showGameOver(win, fenshu, beichi);
    mciSendString("close bgm", NULL, 0, NULL); // ֹͣ���ֲ���


    return 0;
}
