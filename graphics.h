#pragma once

#include <SDL.h>

struct graphicsController {
	// only contains pointers, small object (no need to manipulate pointers to it)
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct lineNode* lines;
};

struct point {
	int x;
	int y;
};

struct lineNode {
	struct point start;
	struct point end;
	struct lineNode* next;
};

struct graphicsController initGraphics();
struct lineNode* addGridToGraphics();
void freeLineNodes(struct lineNode* firstNode);
void destroyGraphics(struct graphicsController graphicsToDestroy);
void drawLines(struct graphicsController graphics);
void updateGraphics(struct graphicsController graphics);
