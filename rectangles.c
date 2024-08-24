#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "rectangles.h"

struct rectangleNode* addRectangleToGraphics(struct rectangleNode* previousNode,
	int topLeftX, int topLeftY, int sizeX, int sizeY,
	int red, int green, int blue, int alpha) {

	// allocate memory for the new element
	struct rectangleNode* newNode = malloc(sizeof(struct rectangleNode));
	if (NULL == newNode) {
		perror("Error while allocating memory for a rectangle");
		return NULL;
	}

	newNode->rectangle.x = topLeftX;
	newNode->rectangle.y = topLeftY;
	newNode->rectangle.w = sizeX;
	newNode->rectangle.h = sizeY;
	newNode->colorR = red;
	newNode->colorG = green;
	newNode->colorB = blue;
	newNode->colorA = alpha;
	newNode->next = NULL;

	if (NULL != previousNode) {
		while (NULL != previousNode->next) {
			previousNode = previousNode->next;
		}
		// here we are sure that previousNode is at the end of the chained list
		previousNode->next = newNode;
	}

	return newNode;
}

void freeRectangleNodes(struct rectangleNode* firstNode) {
	// deallocates the memory used to store the rectangles
	if (firstNode == NULL) {
		return;
	}

	struct rectangleNode* currentNode = firstNode;
	struct rectangleNode* nextNode = currentNode->next;

	while (nextNode != NULL) {
		free(currentNode);
		currentNode = nextNode;
		nextNode = currentNode->next;
	}
	free(currentNode);
}
