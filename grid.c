#include <stdlib.h>  // for dynamic memory allocation
#include "grid.h"

char** initGrid() {
    //creates the grid, in the form of a 2D array of chars
    char** createdGrid = malloc(9 * sizeof(char*));

    if (NULL != createdGrid) {
        // if malloc succeeds
        for (int i = 0; i < 9; i++) {
            createdGrid[i] = malloc(9 * sizeof(char*) * 2);

            if (NULL == createdGrid[i]) {
                // if calloc failed
                perror("Failed to initialize the rows");
                exit(-1);
            }

            for (int j = 0; j < 9; j++) {
                createdGrid[i][j * 2] = '0' + (char) i;
                createdGrid[i][j * 2 + 1] = '\0';  // null terminator to use a pointer to this for the display
            }
        }
    }
    else {
        perror("Failed to initialize the grid");
        exit(-1);
    }

    return createdGrid;
};

void freeGrid(char** gridToFree) {
    // free the grid by first freeing each row and then the grid itself
    if (NULL != gridToFree) {
        for (int i = 0; i < 9; i++) {

            //if (NULL != gridToFree[i]) {
            //    free(gridToFree[i]);
            //}
            // no need to check this because free(NULL) is authorized
            free(gridToFree[i]);

        }

        free(gridToFree);
    }
}

bool setValue(char value, char row, char column, char** grid) {
    // try to change the value of a tile and returns wheter it was a success or not
    // value should NEVER be '0' (as it is possible to have multiple '0''s on a line/row/square
    // value = '1', '2', '3', '4', '5', '6', '7', '8', '9'

    // checks vertical and horizontal lines
    for (int i = 0; i < 9; i++) {
        if (grid[i][2 * column] == value || grid[row][2 * i] == value) {
            return false;
        }
    }

    // checks 3x3 squares
    for (int i = 3 * (row / 3); i < 3 * ((row / 3) + 1); i++) {
        for (int j = 3 * (column / 3); j < 3 * ((column / 3) + 1); j++) {
            if (grid[i][2 * j] == value) {
                return false;
            }
        }
    }

    // if no error, sets the value in the tile
    grid[row][2 * column] = value;
    
    return true;
}

struct lineNode* addLinesToGraphics() {
    // add the lines to the graphics

    struct lineNode* firstLine = NULL;
    struct lineNode* lastLine = NULL;

    // horizontal lines
    for (int i = 15; i <= 465; i += 50) {
        lastLine = addLineToGraphics(lastLine, 95, i, 545, i, 0, 0, 0, 255);
        if (NULL == firstLine) {
            // if it is the first time that the for loop is runned
            firstLine = lastLine;
        }
    }

    // vertical lines

    for (int i = 95; i <= 545; i += 50) {
        lastLine = addLineToGraphics(lastLine, i, 15, i, 465, 0, 0, 0, 255);
    }

    return firstLine;

}

struct textBoxNode* addTextBoxesToGraphics(char** grid, struct display* display) {

    struct textBoxNode* firstNode = NULL;
    struct textBoxNode* lastNode = NULL;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ('0' != grid[i][2 * j]) {
                lastNode = addTextBoxToGraphics(lastNode, 120 + 50 * i, 40 + 50 * j, &grid[i][2 * j], 1, display);
                if (NULL == firstNode) {
                    firstNode = lastNode;
                }
            }
        }
    }

    return firstNode;
}

struct rectangleNode* addRectanglesToGraphics() {
    // add the rectangles to the graphics

    struct rectangleNode* firstRectangle = NULL;
    struct rectangleNode* lastRectangle = NULL;

    int color = 220;

    for (int i = 95; i <= 395; i += 150) {
        for (int j = 15; j <= 315; j += 150) {
            lastRectangle = addRectangleToGraphics(lastRectangle, i, j, 150, 150, color, color, color, 255);
            // alternates color between white and grey
            color = (color == 255) ? 220 : 255;
            if (NULL == firstRectangle) {
                firstRectangle = lastRectangle;
            }
        }
    }

    return firstRectangle;
}

void addGridToGraphics(struct graphicsController* graphics, char** grid) {
    // adds the elements that must be displayed
    if (NULL == graphics->elements) {
        // if the initialization was not properly done
        perror("Error with the allocation of graphics.elements");
        exit(-1);
    }
    graphics->elements->lines = addLinesToGraphics();
    graphics->elements->rectangles = addRectanglesToGraphics();
    graphics->elements->textBoxes = addTextBoxesToGraphics(grid, graphics->display);
}
