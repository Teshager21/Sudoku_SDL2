#include<iostream>
#include<string>
#include"model.h"
#include "AssetManager.h"
#include "controller.h"

Controller::Controller(){
    mAssetManager = AssetManager::GetInstance();
    mWindow = Window::getInstance(); 
    mModel= Model::getInstance();
}
Controller::~Controller(){
    delete m_textTexture;
}
bool Controller::run() {
    Uint32 starting_tick;
    while (mWindow->getState()) {
        starting_tick = SDL_GetTicks();
        pollEvents();
        mWindow->drawGrid();
        grayFixedCells();
        displayFixedPositions();
        displayVariablePositions();
        mWindow->CapFrameRate(starting_tick);
    }
    return true;
}
void Controller::handleKeyEvents(int selectedValue) {
	int position = ((mWindow->getCursorPos(1) - 80) / mWindow->getCellSize()) * 9 + (mWindow->getCursorPos(0) - 80) / mWindow->getCellSize();
	if (!mModel->checkSelectedPosition(position)) {
        mModel->receiveInput(position, selectedValue);
	}
	else {
		mModel->setMessages( ("Cell "+ std::to_string(position) + " not Available! ")+std::to_string(mModel->getMembers(position/9,position%9)));
	}
}
void Controller:: handleKeyboardEvents(SDL_Event& event) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: 
            handleKeyEvents(1);
            break;
        case SDLK_2: 
            handleKeyEvents(2);

            break;
        case SDLK_3: 
            handleKeyEvents(3);

            break;
        case SDLK_4: 
            handleKeyEvents(4);

            break;
        case SDLK_5: 

            handleKeyEvents(5);
            break;
        case SDLK_6: 
            handleKeyEvents(6);

            break;
        case SDLK_7: 
            handleKeyEvents(7);

            break;
        case SDLK_8: 
            handleKeyEvents(8);

            break;
        case SDLK_9: 
            handleKeyEvents(9);

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

void Controller::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mWindow->setState(false);
            break;
        }
        handleKeyboardEvents(event);
        mWindow->handleMouseClicks(event);
    }
    SDL_SetRenderDrawColor(&mWindow->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&mWindow->getRenderer());
}
void Controller:: displayMessage() {
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    Texture texture =Texture(mModel->getMessages(), "Roboto-Regular.ttf", 22, red);
    texture.SetSrcRect(80, 640);
    texture.renderText();
    texture.Render();  
    SDL_RenderPresent(&mWindow->getRenderer());
}
void Controller::grayFixedCells() {
    for (int i = 0; i < mModel->GetFilledCells(); i++) {
        int pos = mModel->getFilledPosition(i);
        int row = pos / 9;
        int col = pos % 9;
        
        int x = 0,y=0;
        if(row%3==0){ x = 84 + row * mWindow->getCellSize(); }else{ x = 82 + row * mWindow->getCellSize(); }
        
        if (col % 3 == 0) { y = 84 + col * mWindow->getCellSize(); }else{ y = 82 + col * mWindow->getCellSize(); }
        if (mModel->checkSelectedPosition(mModel->getFilledPosition(i))){
            mWindow->SetMemberOfGrayRects(i, y, x);
            SDL_SetRenderDrawColor(&mWindow->getRenderer(), 240, 240, 240, 245); 
            SDL_RenderDrawRect(&mWindow->getRenderer(), &mWindow->GetMemberOfGrayRects(i)); 
            SDL_RenderFillRect(&mWindow->getRenderer(), &mWindow->GetMemberOfGrayRects(i));
        }
    }

} 
void Controller::displayFixedPositions() {
    for (int m = 0; m < mModel->GetFilledCells(); m++) {
        int position = mModel->getFilledPosition(m);
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        snprintf(text, sizeof(text),"%d", mModel->getMembers(row,col));
        snprintf(test, sizeof(test),"%d", 0);
        Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 255,255,255,0 });
        if (mModel->getMembers(row, col) == 0) {
            Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 255,255,255,0 });
        }
        else {
            Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 0,0,200,0 });
            int hIndent = (mWindow->getCellSize() - texture.GetSurface()->w) * 0.5;
            int vIndent = (mWindow->getCellSize() - texture.GetSurface()->h) * 0.5;
            texture.SetSrcRect(20 + mWindow->getCellSize() * (col + 1) + hIndent, 20 + mWindow->getCellSize() * (row + 1) + vIndent);

            texture.renderText();
        }
        texture.Render();
    }
    mWindow->drawCursor();
    displayMessage();
    SDL_RenderPresent(&mWindow->getRenderer());
}
void Controller::displayVariablePositions() {

    for (int m = 0; m < mModel->getVariablePositions().size(); m++) {
        int position = mModel->getVariablePositions()[m];
        int row = position / 9;
        int col = position % 9;
        char text[10];
        char test[10];
        snprintf(text,sizeof(text), "%d", mModel->getMembers(row, col));
        snprintf(test,sizeof(test), "%d", 0);
       
        Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 0,128,70,0 });
        int hIndent = (mWindow->getCellSize() - texture.GetSurface()->w) * 0.5;
        int vIndent = (mWindow->getCellSize() - texture.GetSurface()->h) * 0.5;
        texture.SetSrcRect(20 + mWindow->getCellSize() * (col + 1) + hIndent, 20 + mWindow->getCellSize() * (row + 1) + vIndent);
        texture.renderText();
    }
    mWindow->drawCursor();
    displayMessage();
    SDL_RenderPresent(&mWindow->getRenderer());
}

