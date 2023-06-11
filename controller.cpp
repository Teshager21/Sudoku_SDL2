#include<iostream>
#include<string>
#include"controller.h">
#include"model.h"
#include "AssetManager.h"

Controller::Controller(Model& model): model(model) {
    mAssetManager = AssetManager::GetInstance();
    mWindow = Window::getInstance(); 
}
Controller::~Controller(){
    delete m_textTexture;
}
bool Controller::run() {
    Uint32 starting_tick;
    while (mWindow->getState()) {

        starting_tick = SDL_GetTicks();

        pollEvents(*mWindow);
        mWindow->drawGrid();
        grayFixedCells(model, *mWindow);
        displayFixedPositions(*mWindow, model);
        displayVariablePositions(*mWindow, model);
        mWindow->CapFrameRate(starting_tick);
    }
    return true;
}
void Controller::handleKeyEvents(int selectedValue, Window& window) {
	int position = ((window.getCursorPos(1) - 80) / window.getCellSize()) * 9 + (window.getCursorPos(0) - 80) / window.getCellSize();
	if (!model.checkSelectedPosition(position)) {
        model.receiveInput(position, selectedValue);
	}
	else {
		model.setMessages( ("Cell "+ std::to_string(position) + " not Available! ")+std::to_string(model.getMembers(position/9,position%9)));
	}
}
void Controller:: handleKeyboardEvents(SDL_Event& event) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: 
            handleKeyEvents(1,*mWindow);
            break;
        case SDLK_2: 
            handleKeyEvents(2,*mWindow);

            break;
        case SDLK_3: 
            handleKeyEvents(3, *mWindow);

            break;
        case SDLK_4: 
            handleKeyEvents(4, *mWindow);

            break;
        case SDLK_5: 

            handleKeyEvents(5, *mWindow);
            break;
        case SDLK_6: 
            handleKeyEvents(6, *mWindow);

            break;
        case SDLK_7: 
            handleKeyEvents(7, *mWindow);

            break;
        case SDLK_8: 
            handleKeyEvents(8, *mWindow);

            break;
        case SDLK_9: 
            handleKeyEvents(9, *mWindow);

            break;
        case SDLK_LEFT:
            mWindow->handleCursorKeys(event);
            break;
        case SDLK_RIGHT:
            mWindow->handleCursorKeys(event);
            break;
        case SDLK_UP:
            mWindow->handleCursorKeys(event);
            break;
        case SDLK_DOWN:
            mWindow->handleCursorKeys(event);
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
void Controller:: displayMessage(Window& window, Model& model) {
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    Texture texture =Texture(model.getMessages(), "Roboto-Regular.ttf", 22, red);
    texture.SetSrcRect(80, 640);
    texture.renderText();
    texture.Render();  
    SDL_RenderPresent(&Window::getInstance()->getRenderer());
}
void Controller::grayFixedCells(Model& model,Window& window) {
    for (int i = 0; i < model.GetFilledCells(); i++) {
        int pos = model.getFilledPosition(i);
        int row = pos / 9;
        int col = pos % 9;
        
        int x = 0,y=0;
        if(row%3==0){ x = 84 + row * window.getCellSize(); }else{ x = 82 + row * window.getCellSize(); }
        
        if (col % 3 == 0) { y = 84 + col * window.getCellSize(); }else{ y = 82 + col * window.getCellSize(); }
        if (model.checkSelectedPosition(model.getFilledPosition(i))){
            window.SetMemberOfGrayRects(i, y, x);
            SDL_SetRenderDrawColor(&window.getRenderer(), 220, 240, 255, 245); 
            SDL_RenderDrawRect(&window.getRenderer(), &window.GetMemberOfGrayRects(i)); 
            SDL_RenderFillRect(&window.getRenderer(), &window.GetMemberOfGrayRects(i));
        }
    }

} 
void Controller::displayFixedPositions(Window& window,Model& model) {
    for (int m = 0; m < model.GetFilledCells(); m++) {
        int position = model.getFilledPosition(m);
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        sprintf_s(text, "%d", model.getMembers(row,col));
        sprintf_s(test, "%d", 0);
        Texture texture = Texture(text, "Roboto-BoldItalic.ttf", 28, { 255,255,255,0 });
        if (model.getMembers(row, col) == 0) {
            Texture texture = Texture(text, "Roboto-BoldItalic.ttf", 28, { 255,255,255,0 });
        }
        else {
            Texture texture = Texture(text, "Roboto-BoldItalic.ttf", 28, { 0,0,200,0 });
            int hIndent = (window.getCellSize() - texture.GetSurface()->w) * 0.5;
            int vIndent = (window.getCellSize() - texture.GetSurface()->h) * 0.5;
            texture.SetSrcRect(20 + window.getCellSize() * (col + 1) + hIndent, 20 + window.getCellSize() * (row + 1) + vIndent);

            texture.renderText();
        }
        texture.Render();
    }
    window.drawCursor();
    displayMessage(window, model);
    SDL_RenderPresent(&window.getRenderer());
}
void Controller::displayVariablePositions(Window& window, Model& model) {

    for (int m = 0; m < model.getVariablePositions().size(); m++) {
        int position = model.getVariablePositions()[m];
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        sprintf_s(text, "%d", model.getMembers(row, col));
        sprintf_s(test, "%d", 0);
       
        Texture texture = Texture(text, "Roboto-BoldItalic.ttf", 28, { 0,128,70,0 });
        int hIndent = (window.getCellSize() - texture.GetSurface()->w) * 0.5;
        int vIndent = (window.getCellSize() - texture.GetSurface()->h) * 0.5;
        texture.SetSrcRect(20 + window.getCellSize() * (col + 1) + hIndent, 20 + window.getCellSize() * (row + 1) + vIndent);
        texture.renderText();
    }
    window.drawCursor();
    displayMessage(window, model);
    SDL_RenderPresent(&window.getRenderer());
}

