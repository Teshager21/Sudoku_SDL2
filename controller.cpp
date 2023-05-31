#include<iostream>
#include<string>
#include<SDL.h>
#include"controller.h">
#include"model.h"


Controller::Controller(Model& model, Window& window): model(model),window(window) {}

void Controller::handleKeyEvents(int selectedValue, int (&cursorPos)[2]) {
	int position = ((cursorPos[1] - 30) / window.getCellSize()) * 9 + (cursorPos[0] - 30) / window.getCellSize();
	if (model.checkSelectedPosition(position)) {
        model.receiveInput(position, selectedValue);
	}
	else {
		model.setMessages( ("Cell not Available! " + std::to_string(position)));
	}

	std::cout << "the position calculated: " << position;

}

void Controller:: handleKeyboardEvents(SDL_Event& event, int (&cursorPos)[2]) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: std::cout << "the number pressed is: 1";
            handleKeyEvents(1, cursorPos);
            break;
        case SDLK_2: std::cout << "the number pressed is: 2";
            handleKeyEvents(2, cursorPos);

            break;
        case SDLK_3: std::cout << "the number pressed is: 3";
            handleKeyEvents(3, cursorPos);

            break;
        case SDLK_4: std::cout << "the number pressed is: 4";
            handleKeyEvents(4, cursorPos);

            break;
        case SDLK_5: std::cout << "the number pressed is: 5";

            handleKeyEvents(5, cursorPos);
            break;
        case SDLK_6: std::cout << "the number pressed is: 6";
            handleKeyEvents(6, cursorPos);

            break;
        case SDLK_7: std::cout << "the number pressed is: 7";
            handleKeyEvents(7, cursorPos);

            break;
        case SDLK_8: std::cout << "the number pressed is: 8";
            handleKeyEvents(8, cursorPos);

            break;
        case SDLK_9: std::cout << "the number pressed is: 9";
            handleKeyEvents(9, cursorPos);

            break;
        case SDLK_LEFT:
            window.handleCursorKeys(event, cursorPos);
            break;
        case SDLK_RIGHT:
            window.handleCursorKeys(event, cursorPos);
            break;
        case SDLK_UP:
            window.handleCursorKeys(event, cursorPos);
            break;
        case SDLK_DOWN:
            window.handleCursorKeys(event, cursorPos);
            break;
        }
    }
}

void Controller::pollEvents(SDL_Event& event, bool& running, int(&cursorPos)[2]) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }
        handleKeyboardEvents(event, cursorPos);
    }
}