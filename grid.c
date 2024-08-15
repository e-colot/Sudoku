#include <stdlib.h>  // for dynamic memory allocation
#include "grid.h"

char** initGrid() {
    //creates the grid, in the form of a 2D array of chars
    char** createdGrid = malloc(9 * sizeof(char*));

    if (createdGrid != NULL) {
        // if malloc succeeds
        for (int i = 0; i < 9; i++) {
            createdGrid[i] = calloc(9, sizeof(char));

            if (createdGrid[i] == NULL) {
                // if calloc failed
                perror("Failed to initialize the rows");
                return NULL;
            }
        }
    }
    else {
        perror("Failed to initialize the grid");
        return NULL;
    }

    return createdGrid;
};

void freeGrid(char** gridToFree) {
    // free the grid by first freeing each row and then the grid itself
    if (gridToFree != NULL) {
        for (int i = 0; i < 9; i++) {

            if (gridToFree[i] != NULL) {
                free(gridToFree[i]);
            }

        }

        free(gridToFree);
    }
}

bool setValue(char value, char row, char column, char** grid) {
    // try to change the value of a tile and returns wheter it was a success or not

    // checks vertical and horizontal lines
    for (int i = 0; i < 9; i++) {
        if (grid[i][column] == value || grid[row][i] == value) {
            return false;
        }
    }

    // checks 3x3 squares
    for (int i = 3 * (row / 3); i < 3 * ((row / 3) + 1); i++) {
        for (int j = 3 * (column / 3); j < 3 * ((column / 3) + 1); j++) {
            if (grid[i][j] == value) {
                return false;
            }
        }
    }

    // if no error, sets the value in the tile
    grid[row][column] = value;
    
    return true;
}

