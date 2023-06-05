#include<iostream>
#include"window.h"
#include "model.h"
#include"controller.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

int main(int argc, char* argv[]) {
    Window window("SUDOKU",SCREEN_WIDTH,SCREEN_HEIGHT);
    Model model;
    Controller controller(model,window);
    
    Uint32 starting_tick;
  
    while (window.getState()) {

        starting_tick = SDL_GetTicks();

        controller.pollEvents(window);
        window.drawGrid();
        
        controller.grayFixedCells(model, window);
        controller.displayFixedPositions(window, model);
        controller.displayVariablePositions(window, model);
        
        window.CapFrameRate(starting_tick);
 
        //clearing
        //SDL_FreeSurface(surface);
        //SDL_DestroyTexture(texture);
        //TTF_CloseFont(font);
    }

    return 0;
}

