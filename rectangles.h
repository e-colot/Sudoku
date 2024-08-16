#pragma once
// same as explained in "lines.h", making a chained list is a personnal choice

#include "SDL.h"

struct rectangleNode {
	SDL_Rect rectangle;
	int color;  // value between 0 and 255 so (R, G, B) = (color, color, color)
	struct rectangleNode* next;
};

struct rectangleNode* addRectanglesToGraphics();
void freeRectangleNodes(struct rectangleNode* firstNode);
