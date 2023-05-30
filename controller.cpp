#include<iostream>
#include<string>
#include<SDL.h>
#include"controller.h">
#include"model.h"
//#include"window.h"
//#include"model.h"


Controller::Controller(Model& model, Window& window): model(model),window(window) {}

void Controller::handleKeyEvents(int selectedValue, SDL_Rect& cursor) {
	int position = ((cursor.y - 30) / window.getCellSize()) * 9 + (cursor.x - 30) / window.getCellSize();
	if (model.checkSelectedPosition(position)) {
        model.receiveInput(position, selectedValue);
	}
	else {
		model.setMessages( ("Cell not Available! " + std::to_string(position)));
	}

	std::cout << "the position calculated: " << position;

}

void Controller:: handleKeyboardEvents(SDL_Event& event, SDL_Rect& cursor, SDL_Rect& cursor2, SDL_Rect& cursor3) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: std::cout << "the number pressed is: 1";
            handleKeyEvents(1, cursor);
            break;
        case SDLK_2: std::cout << "the number pressed is: 2";
            handleKeyEvents(2, cursor);

            break;
        case SDLK_3: std::cout << "the number pressed is: 3";
            handleKeyEvents(3, cursor);

            break;
        case SDLK_4: std::cout << "the number pressed is: 4";
            handleKeyEvents(4, cursor);

            break;
        case SDLK_5: std::cout << "the number pressed is: 5";

            handleKeyEvents(5, cursor);
            break;
        case SDLK_6: std::cout << "the number pressed is: 6";
            handleKeyEvents(6, cursor);

            break;
        case SDLK_7: std::cout << "the number pressed is: 7";
            handleKeyEvents(7, cursor);

            break;
        case SDLK_8: std::cout << "the number pressed is: 8";
            handleKeyEvents(8, cursor);

            break;
        case SDLK_9: std::cout << "the number pressed is: 9";
            handleKeyEvents(9, cursor);

            break;
        case SDLK_LEFT:
            handleCursorKeys(event, cursor, cursor2, cursor3);
            break;
        case SDLK_RIGHT:
            handleCursorKeys(event, cursor, cursor2, cursor3);
            break;
        case SDLK_UP:
            handleCursorKeys(event, cursor, cursor2, cursor3);
            break;
        case SDLK_DOWN:
            handleCursorKeys(event, cursor, cursor2, cursor3);
            break;
        }
    }
}

void Controller::handleCursorKeys(SDL_Event& event, SDL_Rect& cursor, SDL_Rect& cursor2, SDL_Rect& cursor3) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        cursor.x -= window.getCellSize();
        cursor2.x -= window.getCellSize();
        cursor3.x -= window.getCellSize();
        break;
    case SDLK_RIGHT:
        cursor.x += window.getCellSize();
        cursor2.x += window.getCellSize();
        cursor3.x += window.getCellSize();
        break;
    case SDLK_UP:
        cursor.y -= window.getCellSize();
        cursor2.y -= window.getCellSize();
        cursor3.y -= window.getCellSize();
        break;
    case SDLK_DOWN:
        cursor.y += window.getCellSize();
        cursor2.y += window.getCellSize();
        cursor3.y += window.getCellSize();
        break;

    }
}