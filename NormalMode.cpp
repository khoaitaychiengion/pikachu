#include "NormalMode.h"
#include<iostream>
using namespace std;

char bg[20][41];

void initBoard(CELL_1** board) {

    // gan vi tri cho tung o mot
    for (int i = 0; i < BOARDHEIGTH; i++) {
        board[i] = new CELL_1[BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].j = j;
            board[i][j].i = i;
        }
    }

    int flagNum = (BOARDWIDTH * BOARDHEIGTH) / 2;

    // gan ky tu cho tung o mot
    while (flagNum) { 
        int index, time = 2;
        char c = 65 + rand() % 26;

        // gan 1 ky tu cho 2 o
        while (time) { 
            index = rand() % 40;
            if (board[index / 8][index % 8].c == ' ') {
                board[index / 8][index % 8].c = c;
                time--;
            }
        }
        flagNum--;
    }
}

void deleteBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGTH; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if (board[i][j].isValid) {
                board[i][j].deleteBox();
                if (j < 4) displayBackground(bg, j, i);
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < BOARDHEIGTH; i++) {
        delete[]board[i];
    }
    delete[]board;
}

void renderBoard(CELL_1** board) {
    for (int i = 0; i < BOARDHEIGTH; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            board[i][j].drawBox(112);
        }
    }
}

// di chuyen
void move(CELL_1** board, position& pos, int& status, player& p, position selectedPos[], int& couple) {

    int temp, key;
    temp = _getch();

    // neu ko phai dau mui ten
    if (temp && temp != 224) {

        // neu la ESC
        if (temp == ESC_KEY) {
            status = 2;
        }

        // neu la Enter
        else if (temp == ENTER_KEY) {

            // neu chon cung 1 o
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {

                // to mau do
                board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                Sleep(500);

                // tra ve luc chua o nao duoc chon
                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                goToXY(70, 0);
                cout << "Life: " << p.life;
            } 
            
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                // neu da chon 1 cap
                if (couple == 0) { 

                    // neu ki tu 2 o nay giong nhau
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {

                        // neu 2 o co the noi voi nhau
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {

                            // cong diem
                            p.point += 20;
                            goToXY(40, 0);
                            cout << "Point: " << p.point;

                            // to mau xanh cho 2 o
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(40);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(40);
                            Sleep(500);

                            // xoa o thu nhat
                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deleteBox();
                            if (selectedPos[0].x < 4) displayBackground(bg, selectedPos[0].x, selectedPos[0].y);

                            // xoa o thu hai
                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deleteBox();
                            if (selectedPos[1].x < 4) displayBackground(bg, selectedPos[1].x, selectedPos[1].y);
                        }

                        // neu khong noi duoc
                        else {
                            // to mau do cho 2 o
                            board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                            board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                            Sleep(500);

                            p.life--;
                            goToXY(70, 0);
                            cout << "Life: " << p.life;
                        }
                    }

                    // neu 2 ki tu khac nhau
                    else {
                        // to mau do cho 2 o
                        board[selectedPos[0].y][selectedPos[0].x].drawBox(70);
                        board[selectedPos[1].y][selectedPos[1].x].drawBox(70);
                        Sleep(500);

                        p.life--;
                        goToXY(70, 0);
                        cout << "Life: " << p.life;
                    }

                    // tra ve cac chi so luc chua o nao duoc chon
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    // dua con tro toi o hop le
                    // uu tien ve ben phai, neu khong co thi xuong duoi
                    for (int i = pos.y; i < BOARDHEIGTH; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    } // neu khong co o hop le ben phai va phia duoi

                    // dua con tro ve dau bang tu trai qua phai tu tren xuong duoi
                    for (int i = 0; i <= pos.y; i++) {
                        for (int j = 0; j <= pos.x; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    //neu la dau mui ten
    else {  

        // neu o nay chua duoc chon
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x))
            board[pos.y][pos.x].isSelected = 0;

        switch (key = _getch()) {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = BOARDHEIGTH - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGTH - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;

        case KEY_DOWN:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y + 1; j < BOARDHEIGTH; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGTH; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;

        case KEY_LEFT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;

        case KEY_RIGHT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

        default:
            break;
        }
    }
}

void normalMode(player& p) {

    srand(time(0));
    getBackground(bg);

    CELL_1** board = new CELL_1 * [BOARDHEIGTH];
    initBoard(board);

    goToXY(10, 0);
    cout << "Name: " << p.name;
    goToXY(40, 0);
    cout << "Point: " << p.point;
    goToXY(70, 0);
    cout << "Life: " << p.life;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    goToXY(100, 12);
    cout << "Press ARROW key to MOVE";
    goToXY(100, 13);
    cout << "Press ENTER to CHOOSE";
    goToXY(100, 14);
    cout << "Press ESC to QUIT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition = { 0, 0 };
    int status = 0; // 0. dang choi game
                    // 1. het game
                    // 2. nguoi choi chon thoat

    while (!status && p.life) {
        board[curPosition.y][curPosition.x].isSelected = 1;

        renderBoard(board);

        move(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs(board))) 
            status = 1;
    }

    renderBoard(board);
    deleteBoard(board);
    Sleep(500);
    system("cls");

    if (p.life && status == 1) {
        displayStatus(1);
        goToXY(50, 17);
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') normalMode(p);
        else writeLeaderBoard(p);
    }

    else if (p.life == 0) {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(2000);
    }

    system("cls");
}