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
	struct lineNode* next;
}; 

struct lineNode* addLineToGraphics(struct lineNode* previousLine, int startX, int startY, int endX, int endY);
void freeLineNodes(struct lineNode* firstNode);
