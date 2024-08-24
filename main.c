#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation

#include "grid.h"
#include "graphics.h"

void closeProgram(struct graphicsController graphics, char** grid);

int main(int argc, char* argv[]) {
    
    struct graphicsController graphics = initGraphics();
    initText(&graphics, "./fonts/BebasNeue-Regular.ttf", 24);

    char **grid = initGrid();
    addGridToGraphics(&graphics);


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

