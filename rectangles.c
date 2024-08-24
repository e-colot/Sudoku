#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "rectangles.h"

struct rectangleNode* addRectanglesToGraphics() {

	// has to move to "grid.c"

	// creates a chained list to store all the rectangles that makes the grid
	struct rectangleNode* firstRectangle = malloc(sizeof(struct rectangleNode));
	if (firstRectangle == NULL) {
		perror("Error creating the rectangles of the grid");
		return NULL;
	}

	struct rectangleNode* currentRectangle = firstRectangle;
	struct rectangleNode* previousRectangle;  // used to remove the last node
	int color = 220;

	for (int i = 95; i <= 395; i += 150) {
		for (int j = 15; j <= 315; j += 150) {

			currentRectangle->rectangle.x = i;
			currentRectangle->rectangle.y = j;
			currentRectangle->rectangle.h = 150;
			currentRectangle->rectangle.w = 150;

			// alternates color between white and grey
			currentRectangle->color = color;
			color = (color == 255) ? 220 : 255;

			// allocates memory for the next rectangle
			currentRectangle->next = malloc(sizeof(struct rectangleNode));
			if (currentRectangle->next == NULL) {
				perror("Error creating the rectangles of the grid");
				return NULL;
			}
			else {
				previousRectangle = currentRectangle;
				currentRectangle = currentRectangle->next;
			}
		}
	}
	
	free(previousRectangle->next);
	previousRectangle->next = NULL;

	return firstRectangle;
}

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
