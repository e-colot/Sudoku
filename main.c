#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation

#include "grid.h"
#include "graphics.h"

void closeProgram(struct graphicsController graphics, char** grid);

int main(int argc, char* argv[]) {
    
    struct graphicsController graphics = { NULL, NULL, NULL, NULL, 0 };
    char **grid = initGrid();

    if (grid == NULL) {
        closeProgram(graphics, grid);
        return -1;
    }

    graphics = initGraphics();
    
    if (graphics.errors != 0) {
        closeProgram(graphics, grid);
        return -1;
    }

    printf("Check-up complete");

    SDL_Delay(500);

    updateGraphics(graphics);

    SDL_Delay(3000);

    closeProgram(graphics, grid);
    return 0;
}

void closeProgram(struct graphicsController graphics, char** grid) {
    destroyGraphics(graphics);
    freeGrid(grid);
}

