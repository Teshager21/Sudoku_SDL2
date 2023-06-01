#include<iostream>
#include<string>
#include<SDL.h>
#include"controller.h">
#include"model.h"
#include<SDL_ttf.h>


Controller::Controller(Model& model, Window& window): model(model),window(window) {}
Controller::~Controller(){}

void Controller::handleKeyEvents(int selectedValue, Window& window) {
	int position = ((window.getCursorPos(1) - 80) / window.getCellSize()) * 9 + (window.getCursorPos(0) - 80) / window.getCellSize();
	if (model.checkSelectedPosition(position)) {
        model.receiveInput(position, selectedValue);
        std::cout <<std::endl<< "been here: position " << position << " value: " << selectedValue << std::endl;
	}
	else {
		model.setMessages( ("Cell not Available! " + std::to_string(position)));
	}

	std::cout << "the position calculated: " << position;

}

void Controller:: handleKeyboardEvents(SDL_Event& event) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: std::cout << "the number pressed is: 1";
            handleKeyEvents(1,window);
            break;
        case SDLK_2: std::cout << "the number pressed is: 2";
            handleKeyEvents(2,window);

            break;
        case SDLK_3: std::cout << "the number pressed is: 3";
            handleKeyEvents(3, window);

            break;
        case SDLK_4: std::cout << "the number pressed is: 4";
            handleKeyEvents(4, window);

            break;
        case SDLK_5: std::cout << "the number pressed is: 5";

            handleKeyEvents(5, window);
            break;
        case SDLK_6: std::cout << "the number pressed is: 6";
            handleKeyEvents(6, window);

            break;
        case SDLK_7: std::cout << "the number pressed is: 7";
            handleKeyEvents(7, window);

            break;
        case SDLK_8: std::cout << "the number pressed is: 8";
            handleKeyEvents(8, window);

            break;
        case SDLK_9: std::cout << "the number pressed is: 9";
            handleKeyEvents(9, window);

            break;
        case SDLK_LEFT:
            window.handleCursorKeys(event);
            break;
        case SDLK_RIGHT:
            window.handleCursorKeys(event);
            break;
        case SDLK_UP:
            window.handleCursorKeys(event);
            break;
        case SDLK_DOWN:
            window.handleCursorKeys(event);
            break;
        }
    }
}

void Controller::pollEvents(SDL_Event& event,Window& window) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            //running = false;
            window.setState(false);
            break;
        }
        handleKeyboardEvents(event);
    }
    SDL_SetRenderDrawColor(&window.getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&window.getRenderer());
}

void Controller::renderTable(Window& window,Model& model) {
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Surface* surface = nullptr;
    //create texture from the surface
    SDL_Texture* texture = nullptr;
    int col = 0, row = 0;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {
                    char text[10];
                    char test[10];
                    sprintf_s(text, "%d", model.getMembers(i,j,k,l));
                    sprintf_s(test, "%d", 0);
                    if (model.getMembers(i, j, k, l) == 0) {
                        surface = TTF_RenderText_Solid(font, text, { 255,255,255,0 });

                    }
                    else {
                        int pos = 27 * i + 9 * j + 3 * k + l;
                        //if (checkSelectedPosition(pos, filledPositions, filledCells)) {
                        if (model.checkSelectedPosition(pos)) {
                            surface = TTF_RenderText_Solid(font, text, { 0,124,70 });
                        }
                        else {
                            surface = TTF_RenderText_Solid(font, text, { 0,0,200 });
                        }
                    }

                    int hIndent = (window.getCellSize() - surface->w) * 0.5;
                    int vIndent = (window.getCellSize() - surface->h) * 0.5;

                    //create texture from the surfaces
                    col = 3 * i + k;
                    row = 3 * j + l;
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(&window.getRenderer(), surface);
                    SDL_Rect rect = { 20 + window.getCellSize() * (col + 1) + hIndent , 20 + window.getCellSize() * (row + 1) + vIndent , surface->w,surface->h };
                    SDL_RenderCopy(&window.getRenderer(), texture, NULL, &rect);

                    //render the cursor
                    window.drawCursor();
                    displayMessage(window, model);

                    SDL_SetRenderDrawColor(&window.getRenderer(), 255, 255, 255, SDL_ALPHA_TRANSPARENT);
                    SDL_SetRenderDrawColor(& window.getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderPresent(&window.getRenderer());

                }

            }


        }
    }
}

void Controller:: displayMessage(Window& window, Model& model) {
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    TTF_Font* messageFont = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-Regular.ttf", 22);
    SDL_Surface* messageSurface = TTF_RenderText_Solid(messageFont, model.getMessages().c_str(), red);
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(&window.getRenderer(), messageSurface);

    SDL_Rect messageRect = { 80,640,200,26 };
    SDL_RenderCopy(&window.getRenderer(), msgTexture, NULL, &messageRect);

    SDL_SetRenderDrawColor(&window.getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(&window.getRenderer(), &messageRect);
}