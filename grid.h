#pragma once

#include <stdbool.h>  // for booleans
#include "graphics.h"

char** initGrid();
void freeGrid(char** gridToFree);
bool setValue(char value, char row, char column, char** grid);

struct lineNode* addLinesToGraphics();
struct rectangleNode* addRectanglesToGraphics();
struct textBoxNode* addTextBoxesToGraphics(char** grid, struct display* display);
void addGridToGraphics(struct graphicsController* graphics, char** grid);
