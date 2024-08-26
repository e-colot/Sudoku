#pragma once
// there is no point of making it a chained list as the size of it is known
// however, I wanted to try making a chained list so I used it

struct point {
	int x;
	int y;
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

struct lineNode* addLineToGraphics(struct lineNode* previousLine, 
	int startX, int startY, int endX, int endY,
	int red, int green, int blue, int alpha);
void freeLineNodes(struct lineNode* firstNode);
