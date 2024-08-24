#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "lines.h"

struct lineNode* addLineToGraphics(struct lineNode* previousNode, int startX, int startY, int endX, int endY) {

    // allocate memory for the new element
    struct lineNode* newNode = malloc(sizeof(struct lineNode));
    if (NULL == newNode) {
        perror("Error allocating memory for a line");
        exit(-1);
    }

    newNode->start.x = startX;
    newNode->start.y = startY;
    newNode->end.x = endX;
    newNode->end.y = endY;
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

void freeLineNodes(struct lineNode* firstNode) {
    // deallocates the memory used to  store the lines
    if (firstNode == NULL) {
        return;
    }
    struct lineNode* currentNode = firstNode;
    struct lineNode* nextNode = currentNode->next;

    while (nextNode != NULL) {
        free(currentNode);
        currentNode = nextNode;
        nextNode = currentNode->next;
    }
    free(currentNode);
}

