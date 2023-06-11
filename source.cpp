#include<iostream>
#include"controller.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700

int main(int argc, char* argv[]) {
    Model model;
    Controller controller(model);

    controller.run();
    

    return 0;
}

