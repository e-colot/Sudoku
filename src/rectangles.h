#pragma once
// same as explained in "lines.h", making a chained list is a personnal choice

#include "SDL.h"

struct rectangleNode {
	SDL_Rect rectangle;
	int colorR;
	int colorG;
	int colorB;
	int colorA;
	struct rectangleNode* next;
};

struct rectangleNode* addRectangleToGraphics(struct rectangleNode* previousRectangle, 
	int topLeftX, int topLeftY, int sizeX, int sizeY, 
	int red, int green, int blue, int alpha);
void freeRectangleNodes(struct rectangleNode* firstNode);
