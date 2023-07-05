#include<iostream>
#include<string>
#include"model.h"
#include "AssetManager.h"
#include "controller.h"


Controller::Controller(){
    mAssetManager = AssetManager::GetInstance();
    mWindow = Window::getInstance(); 
    mModel= Model::getInstance();
    mSolver= Solver::getInstance();
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
        displayCandidates();
        mWindow->CapFrameRate(starting_tick);   
    }
    return true;
}
void Controller::newGame(){
    //clear the board of penmarking and fixed values
    for(int i=0;i<81;i++){
        mModel->receiveInput( i, 0);
    }

   //clear candidate values
  for(int i=0;i<81;i++){
       mModel->setCandidateVector(i,{0,0,0,0,0,0,0,0});
    }
//board populated again
  Model::getInstance()->init();


}
void Controller::handleKeyEvents(int selectedValue) {

	int position = ((mWindow->getCursorPos(1) - mWindow->m_margin) / mWindow->getCellSize()) * 9 + (mWindow->getCursorPos(0) - mWindow->m_margin) / mWindow->getCellSize();
	if(!mWindow->isCandidateMode){
        if (!mModel->checkSelectedPosition(position)) {
             if(!mModel->isItRepeatedValue(position,selectedValue)){
                mModel->setCandidateVector(position,{0,0,0,0,0,0,0,0,0});
            }
            mModel->receiveInput(position, selectedValue);
           
        }
        else {
            mModel->setMessages( ("Cell "+ std::to_string(position) + " not Available! ")+std::to_string(mModel->getMembers(position/9,position%9)));
        }
    } else{
        std::map<int,std::vector<int>>* candidates=mModel->getCandidates();
        mModel->setCandidateValue(position,selectedValue);
        
        
    
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
        if(mWindow->mRun==true){
            mSolver->solve();
            mWindow->mRun=false;
        }
        if(mWindow->mRestart==true){
            std::cout<<"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"<<std::endl;
            newGame();
            mWindow->mRestart=false;
        }
    }
    SDL_SetRenderDrawColor(&mWindow->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(&mWindow->getRenderer());
}
void Controller::displayMessage() {
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    Texture texture =Texture(mModel->getMessages(), "Roboto-Regular.ttf", 22, red);
    texture.SetSrcRect(mWindow->m_margin, mWindow->getCellSize()*9+100);
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
            SDL_SetRenderDrawColor(&mWindow->getRenderer(), 240, 240, 240, 0); 
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
            Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 200,200,200,0 });
            int hIndent = (mWindow->getCellSize() - texture.GetSurface()->w) * 0.5;
            int vIndent = (mWindow->getCellSize() - texture.GetSurface()->h) * 0.5;
            texture.SetSrcRect(mWindow->getCellSize() * (col + 1) + hIndent, mWindow->getCellSize() * (row + 1) + vIndent);

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

        if (mModel->getMembers(row, col) == 0) {
            Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 255,255,255,0 });
        }
        else {
            Texture texture = Texture(text, "Roboto-Bold.ttf", 28, { 228,228,70,0 });
            int hIndent = (mWindow->getCellSize() - texture.GetSurface()->w) * 0.5;
            int vIndent = (mWindow->getCellSize() - texture.GetSurface()->h) * 0.5;
            texture.SetSrcRect(mWindow->getCellSize() * (col + 1) + hIndent, mWindow->getCellSize() * (row + 1) + vIndent);
            texture.renderText();
        }
    }
    mWindow->drawCursor();
    displayMessage();
    SDL_RenderPresent(&mWindow->getRenderer());
}
void Controller::displayCandidates(){

std::map<int,std::vector<int>> mapOfCandidates = *(mModel->getCandidates());

int position;

for( const auto cand : mapOfCandidates){
    
    position=cand.first;

    for(const auto candidateValue :cand.second){
      displayAcandidate(position,candidateValue) ;
    }

}

}
void Controller::displayAcandidate(int position,int candidateValue){
    if(candidateValue!=0){
        int col= position%9;
        int row= position/9;
        int candidateCol= (candidateValue-1)%3;
        int candidateRow= (candidateValue-1)/3;

        int x=mWindow->m_margin + col*mWindow->getCellSize() + (candidateCol)*((mWindow->getCellSize())/3);
        int y=mWindow->m_margin+ row*mWindow->getCellSize()+ (candidateRow)*(mWindow->getCellSize()/3);

        Texture texture = Texture(std::to_string(candidateValue), "Roboto-Regular.ttf", 20, { 111,156,193,SDL_ALPHA_OPAQUE});
        texture.SetSrcRect(x,y);
        texture.renderText();
        SDL_RenderPresent(&mWindow->getRenderer());
    }


}

