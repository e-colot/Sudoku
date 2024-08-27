#include <stdio.h>
#include "graphics.h"

struct graphicsController initGraphics() {

    struct graphicsController graphics = { NULL, NULL };
    graphics.display = malloc(sizeof(struct display));
    graphics.elements = malloc(sizeof(struct elementsToDisplay));
    if (NULL == graphics.display || NULL == graphics.elements) {
        perror("Error allocating memory for the graphics");
        goto EXIT0;
    }
    graphics.elements->lines = NULL;
    graphics.elements->rectangles = NULL;
    graphics.elements->textBoxes = NULL;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL : %s\n", SDL_GetError());
        goto EXIT0;
    }

    // Window creation

    SDL_Window* window = SDL_CreateWindow("Sudoku",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    if (NULL == window) {
        fprintf(stderr, "Error creating window : %s\n", SDL_GetError());
        goto EXIT1;
    }
    graphics.display->window = window;

    // Renderer creation

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Error creating renderer : %s\n", SDL_GetError());
        goto EXIT2;
    }
    graphics.display->renderer = renderer;
    graphics.display->font = NULL;
    graphics.display->textColor = (SDL_Color) { 0, 0, 0, 0 };

    return graphics;

    // Handling an error during the function call and closing it properly
    EXIT2:
        SDL_DestroyWindow(graphics.display->window);

    EXIT1:
        SDL_Quit();

    EXIT0:
        free(graphics.elements);
        free(graphics.display);

    exit(-1);
}

void initText(struct graphicsController* graphics, char* fontLocation, int fontSize) {
    // SDL font creation

    if (TTF_Init() == -1) {
        fprintf(stderr, "Error creating font : %s\n", TTF_GetError());
        exit(-1);
    }

    TTF_Font* font = TTF_OpenFont(fontLocation, fontSize);
    if (NULL == font) {
        fprintf(stderr, "Error loading the font : %s\n", TTF_GetError());
        exit(-1);
    }
    graphics->display->font = font;

    SDL_Color textColor = { 0, 0, 0, 255 };
    graphics->display->textColor = textColor;
}

void destroyGraphics(struct graphicsController graphicsToDestroy) {
    // deletes the window and exit SDL properly
    if (NULL != graphicsToDestroy.display->window) {
        SDL_DestroyWindow(graphicsToDestroy.display->window);
    }
    if (NULL != graphicsToDestroy.display->renderer) {
        SDL_DestroyRenderer(graphicsToDestroy.display->renderer);
    }
    if (NULL != graphicsToDestroy.display->font) {
        TTF_CloseFont(graphicsToDestroy.display->font);
    }
    freeLineNodes(graphicsToDestroy.elements->lines);
    freeRectangleNodes(graphicsToDestroy.elements->rectangles);
    freeTextBoxNodes(graphicsToDestroy.elements->textBoxes);

    free(graphicsToDestroy.elements);
    free(graphicsToDestroy.display);

    TTF_Quit();
    SDL_Quit();

}

void drawLines(struct graphicsController graphics) {
    struct lineNode* currentLine = graphics.elements->lines;
    while (NULL != currentLine) {
        SDL_SetRenderDrawColor(graphics.display->renderer, currentLine->colorR, currentLine->colorG, currentLine->colorB, currentLine->colorA);
        SDL_RenderDrawLine(graphics.display->renderer, currentLine->start.x, currentLine->start.y, currentLine->end.x, currentLine->end.y);
        currentLine = currentLine->next;
    }
}

void drawRectangles(struct graphicsController graphics) {
    struct rectangleNode* currentRectangle = graphics.elements->rectangles;
    while (NULL != currentRectangle) {
        SDL_SetRenderDrawColor(graphics.display->renderer, currentRectangle->colorR, currentRectangle->colorG, currentRectangle->colorB, currentRectangle->colorA);
        SDL_RenderFillRect(graphics.display->renderer, &currentRectangle->rectangle);
        currentRectangle = currentRectangle->next;
    }
}

void drawTextBoxes(struct graphicsController graphics) {
    struct textBoxNode* currentTextBox = graphics.elements->textBoxes;
    while (NULL != currentTextBox) {
        SDL_RenderCopy(graphics.display->renderer, currentTextBox->texture, NULL, &(currentTextBox->rectangle));
        currentTextBox = currentTextBox->next;
    }
}

void updateGraphics(struct graphicsController graphics) {

    // Clears the screen
    SDL_SetRenderDrawColor(graphics.display->renderer, 255, 255, 255, 255);
    SDL_RenderClear(graphics.display->renderer);

    // Draws rectangles
    drawRectangles(graphics);

    // Draws lines
    drawLines(graphics);

    // Add text
    drawTextBoxes(graphics);

    // Updates screen
    SDL_RenderPresent(graphics.display->renderer);
}
