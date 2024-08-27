#pragma once

#include <SDL.h>
#include "SDL_ttf.h"

struct display {
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color textColor;
};

struct elementsToDisplay {
	struct lineNode* lines;
	struct rectangleNode* rectangles;
	struct textBoxNode* textBoxes;
};

struct graphicsController {
	struct display* display;
	struct elementsToDisplay* elements;
};

struct point {
	int x;
	int y;
};

struct textBoxNode {
	char* value;
	int len;
	SDL_Rect rectangle;
	SDL_Texture* texture;
	char changeNeeded;  // equals 0 by default, set to another value if the texture must be recreated
	struct textBoxNode* next;
};

struct lineNode {
	struct point start;
	struct point end;
	int colorR;
	int colorG;
	int colorB;
	int colorA;
	struct lineNode* next;
}; 

struct rectangleNode {
	SDL_Rect rectangle;
	int colorR;
	int colorG;
	int colorB;
	int colorA;
	struct rectangleNode* next;
};

