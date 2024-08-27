#pragma once
// same as explained in "lines.h", making a chained list is a personnal choice

#include "structures.h"

struct textBoxNode* addTextBoxToGraphics(struct textBoxNode* previousTextBox, int centerX, int centerY, char* text, int lenOfText, struct display* display);
void freeTextBoxNodes(struct textBoxNode* firstNode);
void updateTextboxes(struct graphicsController graphics);
