#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "rectangles.h"

struct rectangleNode* addRectanglesToGraphics() {
	// creates a chained list to store all the rectangles that makes the grid
	struct rectangleNode* firstRectangle = malloc(sizeof(struct rectangleNode));
	if (firstRectangle == NULL) {
		perror("Error creating the rectangles of the grid");
		return NULL;
	}
	struct rectangleNode* currentRectangle = firstRectangle;
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
				currentRectangle = currentRectangle->next;
			}
		}
	}
	currentRectangle->next = NULL;

	return firstRectangle;
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
