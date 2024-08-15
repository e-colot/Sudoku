#include <stdio.h>
#include "graphics.h"

struct graphicsController initGraphics() {

    struct graphicsController graphics = { NULL, NULL };

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        perror("Error initializing SDL");
        destroyGraphics(graphics);
    }

    // Window creation

    SDL_Window* window = SDL_CreateWindow("Sudoku",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        perror("Error creating window");
        destroyGraphics(graphics);
        return graphics;
    }
    else {
        graphics.window = window;
    }

    // Renderer creation

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        perror("Error creating renderer");
        destroyGraphics(graphics);
        return graphics;
    }
    else {
        graphics.renderer = renderer;
    }

    // creation of the graphical grid

    graphics.lines = addGridToGraphics();

    SDL_Delay(3000); // Wait 3 seconds

    return graphics;
}

struct lineNode* addGridToGraphics() {
    // creates a chained list to store all the lines that makes the grid
    struct lineNode* firstLine = malloc(sizeof(struct lineNode));
    if (firstLine == NULL) {
        perror("Error creating the lines of the grid");
        return NULL;
    }
    struct lineNode* lastLine = firstLine;

    // horizontal lines

    for (int i = 15; i <= 465; i += 50) {

        lastLine->start.x = 95;
        lastLine->start.y = i;

        lastLine->end.x = 545;
        lastLine->end.y = i;

        lastLine->next = malloc(sizeof(struct lineNode));
        if (lastLine->next == NULL) {
            perror("Error creating the lines of the grid");
            return NULL;
        }
        else {
            lastLine = lastLine->next;
        }
    }

    // vertical lines

    for (int i = 95; i <= 545; i += 50) {

        lastLine->start.x = 15;
        lastLine->start.y = i;

        lastLine->end.x = 465;
        lastLine->end.y = i;

        lastLine->next = malloc(sizeof(struct lineNode));
        if (lastLine->next == NULL) {
            perror("Error creating the lines of the grid");
            return NULL;
        }
        else {
            lastLine = lastLine->next;
        }
    }

    lastLine->next = NULL;

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

void destroyGraphics(struct graphicsController graphicsToDestroy) {
    // deletes the window and exit SDL properly
    if (graphicsToDestroy.window != NULL) {
        SDL_DestroyWindow(graphicsToDestroy.window);
    }
    if (graphicsToDestroy.renderer != NULL) {
        SDL_DestroyRenderer(graphicsToDestroy.renderer);
    }
    freeLineNodes(graphicsToDestroy.lines);

    SDL_Quit();

}
