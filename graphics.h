#pragma once

#include <SDL.h>

struct graphicsController {
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
void destroyGraphics(struct graphicsController graphicsToDestroy);
