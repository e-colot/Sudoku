#pragma once

#include <stdbool.h>  // for booleans

char** initGrid();
void freeGrid(char** gridToFree);
bool setValue(char value, char row, char column, char** grid);

struct lineNode* addLinesToGraphics();
