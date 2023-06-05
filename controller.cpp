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
		model.setMessages( ("Cell "+ std::to_string(position) + " not Available! "));
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

void Controller::pollEvents(Window& window) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            window.setState(false);
            break;
        }
        handleKeyboardEvents(event);
    }
    SDL_SetRenderDrawColor(&window.getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&window.getRenderer());
}

void Controller::renderTable(Window& window,Model& model) {
    
    displayArray(window, model, { 0,124,70 });

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

void Controller::grayFixedCells(Model& model,Window& window) {
    for (int i = 0; i < model.GetFilledCells(); i++) {
        int row = model.getFilledPosition(i) / 9;
        int col = model.getFilledPosition(i) % 9;
        int pos = model.getFilledPosition(i);
        int x = 84+row*window.getCellSize();
        int y = 84 + col * window.getCellSize();
        if (model.checkSelectedPosition(model.getFilledPosition(i))){
            //std::cout << std::endl <<pos<<" "<< model.getFilledPosition(i) << "Position to be grayed: " << model.getFilledPosition(i) << std::endl;
            window.SetMemberOfGrayRects(i, y, x);
            SDL_SetRenderDrawColor(&window.getRenderer(), 230, 230, 230, 255); // set the draw color to red
            SDL_RenderDrawRect(&window.getRenderer(), &window.GetMemberOfGrayRects(i)); // draw the rectangle outline
            SDL_RenderFillRect(&window.getRenderer(), &window.GetMemberOfGrayRects(i));
            //grayCell(pos, window);
        }
    }

}

void Controller::displayArray(Window& window,Model& model,SDL_Color color) {
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Surface* surface = nullptr;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
                    char text[10];
                    char test[10];
                    sprintf_s(text, "%d", model.getMembers(i, j));
                    sprintf_s(test, "%d", 0);
                    if (model.getMembers(i, j) == 0) {
                        //surface = TTF_RenderText_Solid(font, text, { 255,255,255,255 });
                    }
                    else {
                        int pos = 3 * i + j;
                        if (model.checkSelectedPosition(pos)) {
                           //surface = TTF_RenderText_Solid(font, text, { 0,124,70 });
                            //surface = TTF_RenderText_Solid(font, text, color);
                        }
                        else {
                           // surface = TTF_RenderText_Solid(font, text, { 0,0,200 });
                        }
                    }

                    int hIndent = (window.getCellSize() - surface->w) * 0.5;
                    int vIndent = (window.getCellSize() - surface->h) * 0.5;

                    //create texture from the surfaces
                
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(&window.getRenderer(), surface);
                    SDL_Rect rect = { 20 + window.getCellSize() * (j + 1) + hIndent , 20 + window.getCellSize() * (i + 1) + vIndent , surface->w,surface->h };
                    SDL_RenderCopy(&window.getRenderer(), texture, NULL, &rect);
                    //render the cursor
                    window.drawCursor();
                    displayMessage(window, model);
                    SDL_RenderPresent(&window.getRenderer());
        }
    }

} 
void Controller::displayFixedPositions(Window& window,Model& model) {
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Surface* surface = nullptr;

    for (int m = 0; m < model.GetFilledCells(); m++) {
        int position = model.getFilledPosition(m);
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        sprintf_s(text, "%d", model.getMembers(row,col));
        sprintf_s(test, "%d", 0);
        if (model.getMembers(row, col) == 0) {
            surface = TTF_RenderText_Solid(font, text, { 255,255,255,0 });
        }
        else {
            surface = TTF_RenderText_Solid(font, text, { 0,0,200,0 });
        }
        int hIndent = (window.getCellSize() - surface->w) * 0.5;
        int vIndent = (window.getCellSize() - surface->h) * 0.5;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(&window.getRenderer(), surface);
        SDL_Rect rect = { 20 + window.getCellSize() * (col + 1) + hIndent , 20 + window.getCellSize() * (row + 1) + vIndent , surface->w,surface->h };
        SDL_RenderCopy(&window.getRenderer(), texture, NULL, &rect);
      

    }
    window.drawCursor();
    displayMessage(window, model);
    SDL_RenderPresent(&window.getRenderer());
}

void Controller::displayVariablePositions(Window& window, Model& model) {
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Surface* surface = nullptr;

    for (int m = 0; m < model.getVariablePositions().size(); m++) {
        int position = model.getVariablePositions()[m];
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        sprintf_s(text, "%d", model.getMembers(row, col));
        sprintf_s(test, "%d", 0);
        surface = TTF_RenderText_Solid(font, text, { 0,128,70,0 });
        int hIndent = (window.getCellSize() - surface->w) * 0.5;
        int vIndent = (window.getCellSize() - surface->h) * 0.5;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(&window.getRenderer(), surface);
        SDL_Rect rect = { 20 + window.getCellSize() * (col + 1) + hIndent , 20 + window.getCellSize() * (row + 1) + vIndent , surface->w,surface->h };
        SDL_RenderCopy(&window.getRenderer(), texture, NULL, &rect);
    }
    window.drawCursor();
    displayMessage(window, model);
    SDL_RenderPresent(&window.getRenderer());
}

