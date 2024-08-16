#include <stdio.h>
#include <stdlib.h>  // for dynamic memory allocation

#include "grid.h"
#include "graphics.h"

int main(int argc, char* argv[]) {
    
    char **grid = initGrid();
    struct graphicsController graphics = initGraphics();
    
    if (grid != NULL && graphics.window != NULL && graphics.renderer != NULL) {
        printf("Check-up complete");

        SDL_Delay(3000);

        updateGraphics(graphics);

        SDL_Delay(3000);
    }

    destroyGraphics(graphics);
    freeGrid(grid);
    return 0;
}

