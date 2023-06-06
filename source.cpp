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

    controller.run();
    

    return 0;
}

