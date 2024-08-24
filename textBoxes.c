#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation
#include "textBoxes.h"
#include "graphics.h"  // for a complete definition of struct display


struct textBoxNode* addTextBoxToGraphics(struct textBoxNode* previousNode, int xPosition, int yPosition, char* text, int lenOfText, struct display* display) {

    // allocate memory for the new element
    struct textBoxNode* newNode = malloc(sizeof(struct textBoxNode));
    if (newNode == NULL) {
        perror("Error creating a text box");
        return NULL;
    }
    newNode->value = text;
    newNode->len = lenOfText;
    newNode->rectangle.x = xPosition;
    newNode->rectangle.y = yPosition;
    newNode->changeNeeded = 0;
    newNode->next = NULL;

    SDL_Surface* textSurface = TTF_RenderText_Solid(display->font, text, display->textColor);
    if (textSurface == NULL) {
        perror("Error while creating a SDL_Surface");
        return NULL;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(display->renderer, textSurface);
    if (textTexture == NULL) {
        SDL_FreeSurface(textSurface);
        perror("Error while creating a SDL_Texture");
        return NULL;
    }
    newNode->rectangle.w = textSurface->w;
    newNode->rectangle.h = textSurface->h;

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
    while (currentTextBox != NULL) {
        if (0 == currentTextBox->changeNeeded) {
            // if the text has changed
            SDL_Surface* textSurface = TTF_RenderText_Solid(graphics.display->font, currentTextBox->value, graphics.display->textColor);
            if (textSurface == NULL) {
                perror("Error while creating a SDL_Surface");
                return;
            }

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(graphics.display->renderer, textSurface);
            if (textTexture == NULL) {
                SDL_FreeSurface(textSurface);
                perror("Error while creating a SDL_Texture");
                return;
            }
            currentTextBox->rectangle.w = textSurface->w;
            currentTextBox->rectangle.h = textSurface->h;

            SDL_FreeSurface(textSurface);
            currentTextBox->texture = textTexture;

            currentTextBox = currentTextBox->next;
        }
    }
}

void freeTextBoxNodes(struct textBoxNode* firstNode) {
    // deallocates the memory used to  store the text boxes
    if (firstNode == NULL) {
        return;
    }
    struct textBoxNode* currentNode = firstNode;
    struct textBoxNode* nextNode = currentNode->next;

    while (nextNode != NULL) {
        if (NULL != currentNode->texture) {
            SDL_DestroyTexture(currentNode->texture);
        }
        free(currentNode);
        currentNode = nextNode;
        nextNode = currentNode->next;
    }
    free(currentNode);
}
