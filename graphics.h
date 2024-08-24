#pragma once

#include <SDL.h>
#include "SDL_ttf.h"
#include "lines.h"
#include "rectangles.h"
#include "textBoxes.h"

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

struct graphicsController initGraphics();
void destroyGraphics(struct graphicsController graphicsToDestroy);
void drawLines(struct graphicsController graphics);
void drawRectangles(struct graphicsController graphics);
void drawTextBoxes(struct graphicsController graphics);
void updateGraphics(struct graphicsController graphics);
