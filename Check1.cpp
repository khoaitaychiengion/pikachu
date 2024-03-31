#include "Check1.h"

bool nextcheck(CELL_1** board, int x1, int y1, int x2, int y2) {
    if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2)) {
        if (board[x1][y1].c == board[x2][y2].c)
            return true;
    }
    if ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2)) {
        if (board[x1][y1].c == board[x2][y2].c)
            return true;
    }
    return false;
}

bool linecheck(CELL_1** board, int x1, int y1, int x2, int y2) {

    if (x1 == x2) {
        int y, x, dem = 0;
        if (y1 > y2) {
            x = y2;
            y = y1;
        }

        else {
            x = y1;
            y = y2;
        }

        for (int i = x; i < y; i++) {
            if (board[x1][i].isValid) {
                dem++;
                if (dem == 2) return false;
            }
        }

        if ((dem == 1) && ((!board[x1][y1].isValid && board[x2][y2].isValid) || (board[x1][y1].isValid && !board[x2][y2].isValid))) {//sai
            return true;
        }

        else if (dem == 0) {
            return true;
        }

        return false;
    }

    if (y1 == y2) {
        int x, y, dem = 0;
        if (x1 > x2) {
            x = x2;
            y = x1;
        }

        else {
            x = x1;
            y = x2;
        }

        for (int i = x; i < y; i++) {
            if (board[i][y1].isValid) {
                dem++;
                if (dem == 2) return false;
            }
        }

        if ((dem == 1) && ((!board[x1][y1].isValid && board[x2][y2].isValid) || (board[x1][y1].isValid && !board[x2][y2].isValid))) {//sai
            return true;
        } 
        
        else if (dem == 0) {
            return true;
        }

        return false;
    }

    return false;
}

bool Icheck_1(CELL_1** board, int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        int y, x, dem = 0;
        if (y1 > y2) {
            x = y2;
            y = y1;
        }
        else {
            x = y1;
            y = y2;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[x1][i].isValid) {
                return false;
            }
        }
        return true;
    }
    if (y1 == y2) {
        int x, y, dem = 0;
        if (x1 > x2) {
            x = x2;
            y = x1;
        }
        else {
            x = x1;
            y = x2;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[i][y1].isValid) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Lcheck(CELL_1** board, int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {
        return false;
    }
    bool c1, c2;
    if (!board[x1][y2].isValid) {
        c1 = linecheck(board, x1, y1, x1, y2);
        c2 = linecheck(board, x2, y2, x1, y2);
        if (c1 && c2) {
            return true;
        }
    }
    if (!board[x2][y1].isValid) {
        c1 = linecheck(board, x1, y1, x2, y1);
        c2 = linecheck(board, x2, y2, x2, y1);
        if (c1 && c2) {
            return true;
        }
    }
    return false;
}

bool Zcheck(CELL_1** board, int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {
        return false;
    }
    bool c1, c2, c3;
    int x, y;
    if (y2 < y1) {
        x = y2;
        y = y1;
    }
    else {
        x = y1;
        y = y2;
    }
    for (int i = x + 1; i < y; i++) {
        c3 = linecheck(board, x1, i, x2, i);
        if (c3) {
            c1 = linecheck(board, x1, y1, x1, i);
            c2 = linecheck(board, x2, y2, x2, i);
            if (c1 && c2)
                return true;
        }
    }
    if (x2 < x1) {
        x = x2;
        y = x1;
    }
    else {
        x = x1;
        y = x2;
    }
    for (int i = x + 1; i < y; i++) {
        c3 = linecheck(board, i, y1, i, y2);
        if (c3) {
            c1 = linecheck(board, x1, y1, i, y1);
            c2 = linecheck(board, x2, y2, i, y2);
            if (c1 && c2)
                return true;
        }
    }
    return false;
}

bool Ucheck(CELL_1** board, int x1, int y1, int x2, int y2) {
    if (((x1 == x2) && (x1 == 0 || x1 == BOARDHEIGTH - 1)) || ((y1 == y2) && (y1 == 0 || y2 == BOARDWIDTH - 1))) {
        return true;
    }
    bool c1, c2, c3;
    int x, y;
    if (y2 < y1) {
        x = y2;
        y = y1;
    }
    else {
        x = y1;
        y = y2;
    }
    for (int i = 0; i < BOARDWIDTH; i++) {
        if (i <= x || i >= y) {
            c3 = linecheck(board, x1, i, x2, i);
            if (c3) {
                c1 = linecheck(board, x1, y1, x1, i);
                c2 = linecheck(board, x2, y2, x2, i);
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDWIDTH - 1)) {
                c1 = linecheck(board, x1, y1, x1, i);
                c2 = linecheck(board, x2, y2, x2, i);
                if ((c1 && c2) || (c1 && y2 == i) || (y1 == i && c2)) {
                    return true;
                }
            }
        }
    }

    if (x2 < x1) {
        x = x2;
        y = x1;
    }
    else {
        x = x1;
        y = x2;
    }
    for (int i = 0; i < BOARDHEIGTH; i++) {
        if (i <= x || i >= y) {
            c3 = linecheck(board, i, y1, i, y2);
            if (c3) {
                c1 = linecheck(board, x1, y1, i, y1);
                c2 = linecheck(board, x2, y2, i, y2);
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDHEIGTH - 1)) {
                c1 = linecheck(board, x1, y1, i, y1);
                c2 = linecheck(board, x2, y2, i, y2);
                if ((c1 && c2) || (c1 && x2 == i) || (x1 == i && c2)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool allcheck(CELL_1** board, int x1, int y1, int x2, int y2) {
    if (nextcheck(board, x1, y1, x2, y2)) {
        return true;
    }
    else if (Icheck_1(board, x1, y1, x2, y2)) {
        return true;
    }
    else if (Lcheck(board, x1, y1, x2, y2)) {
        return true;
    }
    else if (Zcheck(board, x1, y1, x2, y2)) {
        return true;
    }
    else if (Ucheck(board, x1, y1, x2, y2)) {
        return true;
    }
    return false;
}

bool checkValidPairs(CELL_1** board) {
    char check = 'A';
    while (check >= 'A' && check <= 'Z') {
        int cnt = 0;
        int* pos = new int[BOARDHEIGTH * BOARDWIDTH];
        for (int i = 0; i < BOARDHEIGTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].c == check && board[i][j].isValid) {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }

        for (int i = 0; i < cnt - 2; i += 2) {
            for (int j = i + 2; j < cnt; j += 2) {
                if (allcheck(board, pos[i], pos[i + 1], pos[j], pos[j + 1])) {
                    delete[] pos;
                    return true;
                }
            }
        }
        check++;
        delete[] pos;
    }
    return false;
}