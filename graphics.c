#include <stdio.h>
#include "graphics.h"
#include "lines.h"
#include "rectangles.h"

struct graphicsController initGraphics() {

    struct graphicsController graphics = { NULL, NULL, NULL, NULL, 0 };

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        perror("Error initializing SDL");
        graphics.errors = 1;
        return graphics;
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

    graphics.lines = addLinesToGraphics();
    graphics.rectangles = addRectanglesToGraphics();

    if (graphics.lines == NULL || graphics.rectangles == NULL) {
        graphics.errors = 1;
    }

    return graphics;
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

void drawLines(struct graphicsController graphics) {
    struct lineNode* currentLine = graphics.lines;
    while (currentLine != NULL) {
        SDL_RenderDrawLine(graphics.renderer, currentLine->start.x, currentLine->start.y, currentLine->end.x, currentLine->end.y);
        currentLine = currentLine->next;
    }
}

void drawRectangles(struct graphicsController graphics) {
    struct rectangleNode* currentRectangle = graphics.rectangles;
    while (currentRectangle != NULL) {
        SDL_SetRenderDrawColor(graphics.renderer, currentRectangle->color, currentRectangle->color, currentRectangle->color, 255);
        SDL_RenderFillRect(graphics.renderer, &currentRectangle->rectangle);
        currentRectangle = currentRectangle->next;
    }
}

void updateGraphics(struct graphicsController graphics) {

    // Clears the screen
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);
    SDL_RenderClear(graphics.renderer);

    // Draws rectangles
    drawRectangles(graphics);

    // Draws lines
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
    drawLines(graphics);

    // Updates screen
    SDL_RenderPresent(graphics.renderer);
}
