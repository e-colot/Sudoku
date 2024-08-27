#pragma once

#include <SDL.h>
#include "SDL_ttf.h"
#include "lines.h"
#include "rectangles.h"
#include "textBoxes.h"

struct graphicsController initGraphics();
void initText(struct graphicsController* graphics, char* fontLocation, int fontSize);
void destroyGraphics(struct graphicsController graphicsToDestroy);
void drawLines(struct graphicsController graphics);
void drawRectangles(struct graphicsController graphics);
void drawTextBoxes(struct graphicsController graphics);
void updateGraphics(struct graphicsController graphics);
