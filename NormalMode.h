#pragma once
#include "Check1.h"
#include <conio.h>
#include <time.h>
#include "ConsoleSetting.h"
#include "Unity.h"

void initBoard(CELL_1**);
void renderBoard(CELL_1**);
void deleteBoard(CELL_1**);
void move(CELL_1**, position&, int&, player&, position[], int&);
void normalMode(player&);