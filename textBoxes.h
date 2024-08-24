#pragma once
// same as explained in "lines.h", making a chained list is a personnal choice

#include "SDL.h"
#include "SDL_ttf.h"

struct textBoxNode {
	char* value;
	int len;
	SDL_Rect rectangle;
	SDL_Texture* texture;
	char changeNeeded;  // equals 0 by default, set to another value if the texture must be recreated
	struct textBoxNode* next;
};

struct textBoxNode* addTextBoxToGraphics(struct textBoxNode* previousTextBox, int xPosition, int yPosition, char* text, int lenOfText, struct display* display);
void freeTextBoxNodes(struct textBoxNode* firstNode);
void updateTextboxes(struct graphicsController graphics);
