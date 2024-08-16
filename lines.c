#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "lines.h"

struct lineNode* addLinesToGraphics() {
    // creates a chained list to store all the lines that makes the grid
    struct lineNode* firstLine = malloc(sizeof(struct lineNode));
    if (firstLine == NULL) {
        perror("Error creating the lines of the grid");
        return NULL;
    }
    struct lineNode* currentLine = firstLine;

    // horizontal lines

    for (int i = 15; i <= 465; i += 50) {

        currentLine->start.x = 95;
        currentLine->start.y = i;

        currentLine->end.x = 545;
        currentLine->end.y = i;

        currentLine->next = malloc(sizeof(struct lineNode));
        if (currentLine->next == NULL) {
            perror("Error creating the lines of the grid");
            return NULL;
        }
        else {
            currentLine = currentLine->next;
        }
    }

    // vertical lines

    for (int i = 95; i <= 545; i += 50) {

        currentLine->start.x = i;
        currentLine->start.y = 15;

        currentLine->end.x = i;
        currentLine->end.y = 465;

        currentLine->next = malloc(sizeof(struct lineNode));
        if (currentLine->next == NULL) {
            perror("Error creating the lines of the grid");
            return NULL;
        }
        else {
            currentLine = currentLine->next;
        }
    }

    currentLine->next = NULL;

    return firstLine;

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

