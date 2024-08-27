#pragma once
// there is no point of making it a chained list as the size of it is known
// however, I wanted to try making a chained list so I used it

#include "structures.h"

struct lineNode* addLineToGraphics(struct lineNode* previousLine, 
	int startX, int startY, int endX, int endY,
	int red, int green, int blue, int alpha);
void freeLineNodes(struct lineNode* firstNode);
