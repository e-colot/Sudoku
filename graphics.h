#pragma once

#include <SDL.h>

struct graphicsController {
	// only contains pointers, small object (no need to manipulate pointers to it)
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct lineNode* lines;
	struct rectangleNode* rectangles;
	int errors;
};

struct graphicsController initGraphics();
void destroyGraphics(struct graphicsController graphicsToDestroy);
void drawLines(struct graphicsController graphics);
void drawRectangles(struct graphicsController graphics);
void updateGraphics(struct graphicsController graphics);
