#include <stdio.h>
#include "graphics.h"

struct graphicsController initGraphics() {

    struct graphicsController graphics = { NULL, NULL };
    graphics.display = malloc(sizeof(struct display));
    if (NULL == graphics.display) {
        perror("Error allocating memory for the display");
        exit(-1);
    }
    graphics.elements = malloc(sizeof(struct elementsToDisplay));
    if (NULL == graphics.elements) {
        perror("Error allocating memory for the elements to display");
        exit(-1);
    }
    graphics.elements->lines = NULL;
    graphics.elements->rectangles = NULL;
    graphics.elements->textBoxes = NULL;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        perror("Error initializing SDL");
        exit(-1);
    }

    // Window creation

    SDL_Window* window = SDL_CreateWindow("Sudoku",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        perror("Error creating window");
        exit(-1);
    }
    graphics.display->window = window;

    // Renderer creation

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        perror("Error creating renderer");
        exit(-1);
    }
    graphics.display->renderer = renderer;

    // SDL font creation

    if (TTF_Init() == -1) {
        perror("Error creating font");
        exit(-1);
    }

    TTF_Font* font = TTF_OpenFont("./fonts/BebasNeue-Regular.ttf", 24);
    if (font == NULL) {
        perror("Error loading the font");
        exit(-1);
    }
    graphics.display->font = font;

    SDL_Color textColor = { 0, 0, 0, 255 };
    graphics.display->textColor = textColor;

    return graphics;
}

void destroyGraphics(struct graphicsController graphicsToDestroy) {
    // deletes the window and exit SDL properly
    if (graphicsToDestroy.display->window != NULL) {
        SDL_DestroyWindow(graphicsToDestroy.display->window);
    }
    if (graphicsToDestroy.display->renderer != NULL) {
        SDL_DestroyRenderer(graphicsToDestroy.display->renderer);
    }
    freeLineNodes(graphicsToDestroy.elements->lines);
    freeRectangleNodes(graphicsToDestroy.elements->rectangles);
    freeTextBoxNodes(graphicsToDestroy.elements->textBoxes);

    TTF_Quit();
    SDL_Quit();

}

void drawLines(struct graphicsController graphics) {
    struct lineNode* currentLine = graphics.elements->lines;
    while (currentLine != NULL) {
        SDL_RenderDrawLine(graphics.display->renderer, currentLine->start.x, currentLine->start.y, currentLine->end.x, currentLine->end.y);
        currentLine = currentLine->next;
    }
}

void drawRectangles(struct graphicsController graphics) {
    struct rectangleNode* currentRectangle = graphics.elements->rectangles;
    while (currentRectangle != NULL) {
        SDL_SetRenderDrawColor(graphics.display->renderer, currentRectangle->colorR, currentRectangle->colorG, currentRectangle->colorB, currentRectangle->colorA);
        SDL_RenderFillRect(graphics.display->renderer, &currentRectangle->rectangle);
        currentRectangle = currentRectangle->next;
    }
}

void drawTextBoxes(struct graphicsController graphics) {
    struct textBoxNode* currentTextBox = graphics.elements->textBoxes;
    while (currentTextBox != NULL) {
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
    SDL_SetRenderDrawColor(graphics.display->renderer, 0, 0, 0, 255);
    drawLines(graphics);

    // Add text
    drawTextBoxes(graphics);

    // Updates screen
    SDL_RenderPresent(graphics.display->renderer);
}
