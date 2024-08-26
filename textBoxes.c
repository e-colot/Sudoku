#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "textBoxes.h"


struct textBoxNode* addTextBoxToGraphics(struct textBoxNode* previousNode, int centerX, int centerY, char* text, int lenOfText, struct display* display) {

    if (NULL == display->font) {
        // if the font is not set up
        perror("Font not correctly set up");
        exit(-1);
    }

    // allocate memory for the new element
    struct textBoxNode* newNode = malloc(sizeof(struct textBoxNode));
    if (NULL == newNode) {
        perror("Error creating a text box");
        exit(-1);
    }
    newNode->value = text;
    newNode->len = lenOfText;
    newNode->changeNeeded = 0;
    newNode->next = NULL;

    SDL_Surface* textSurface = TTF_RenderText_Solid(display->font, text, display->textColor);
    if (NULL == textSurface) {
        fprintf(stderr, "Error while creating a SDL_Surface: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(display->renderer, textSurface);
    if (NULL == textTexture) {
        SDL_FreeSurface(textSurface);
        perror("Error while creating a SDL_Texture");
        exit(-1);
    }
    newNode->rectangle.w = textSurface->w;
    newNode->rectangle.h = textSurface->h;
    newNode->rectangle.x = centerX - (int) (textSurface->w/2);
    newNode->rectangle.y = centerY - (int) (textSurface->h/2);

    SDL_FreeSurface(textSurface);
    newNode->texture = textTexture;

    // if it is not the first element
    if (NULL != previousNode) {
        while (NULL != previousNode->next) {
            previousNode = previousNode->next;
        }
        // here we are sure that previousNode is at the end of the chained list
        previousNode->next = newNode;
    }

    return newNode;
}

void updateTextboxes(struct graphicsController graphics) {
    struct textBoxNode* currentTextBox = graphics.elements->textBoxes;
    while (NULL != currentTextBox) {
        if (0 == currentTextBox->changeNeeded) {
            currentTextBox->rectangle.x += 2 * currentTextBox->rectangle.w;
            currentTextBox->rectangle.y += 2 * currentTextBox->rectangle.h;
            // if the text has changed
            SDL_Surface* textSurface = TTF_RenderText_Solid(graphics.display->font, currentTextBox->value, graphics.display->textColor);
            if (NULL == textSurface) {
                perror("Error while creating a SDL_Surface");
                exit(-1);
            }

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(graphics.display->renderer, textSurface);
            if (NULL == textTexture) {
                SDL_FreeSurface(textSurface);
                perror("Error while creating a SDL_Texture");
                exit(-1);
            }
            currentTextBox->rectangle.w = textSurface->w;
            currentTextBox->rectangle.h = textSurface->h;

            currentTextBox->rectangle.x -= (int) (currentTextBox->rectangle.w/2);
            currentTextBox->rectangle.y -= (int) (currentTextBox->rectangle.h/2);

            SDL_FreeSurface(textSurface);
            currentTextBox->texture = textTexture;

            currentTextBox = currentTextBox->next;
        }
    }
}

void freeTextBoxNodes(struct textBoxNode* firstNode) {
    // deallocates the memory used to  store the text boxes
    if (NULL == firstNode) {
        return;
    }
    struct textBoxNode* currentNode = firstNode;
    struct textBoxNode* nextNode = currentNode->next;

    while (NULL != nextNode) {
        if (NULL != currentNode->texture) {
            SDL_DestroyTexture(currentNode->texture);
        }
        free(currentNode);
        currentNode = nextNode;
        nextNode = currentNode->next;
    }
    free(currentNode);
}
