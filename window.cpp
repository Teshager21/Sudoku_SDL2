#include "window.h"
#include<SDL2/SDL.h>
#include<iostream>
#include "texture.h"

Window* Window::sInstance = NULL;

Window::Window(const std::string &title, int width, int height):
	m_title(title), m_width(width),m_height(height)
{
	if (!init()) {
		m_running = true; 
	}
    TTF_Init();
}

Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
    delete sInstance;
    TTF_Quit();
	SDL_Quit(); 
}

Window* Window::getInstance() {
    if (!sInstance) {
        sInstance = new Window("SUDOKU", SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    return sInstance;

}

bool Window::getState() { return m_running; }
void Window::setState(bool state) {m_running=state; }
int Window::getCellSize() { return m_cellSize; }

SDL_Renderer& Window::getRenderer() { 
    return *m_renderer;
}

 void Window:: Render() {
     SDL_RenderPresent(m_renderer);
}

int Window::getCursorPos(int x) { return m_cursorPos[x]; }

bool Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize\n";
		return 0;
	}
	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_BORDERLESS);
	if (&sInstance == nullptr) {
		std::cerr << "Failed to initialize window\n";
    }
    SDL_Surface* screen = NULL;
     m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    screen = SDL_GetWindowSurface(m_window);
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_FillRect(screen, NULL, white);

    for (int i = 0; i < 30; i++) {
        m_grayRects[i].x = 0; // x position
        m_grayRects[i].y =0; // y position
        m_grayRects[i].w = m_cellSize-8; // width
        m_grayRects[i].h = m_cellSize-8; // height
    }

	return true;
}

SDL_Texture* Window::CreateTextTexture(TTF_Font* font, std::string text,SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == NULL) {
        printf("Erro in text render:%s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (texture == NULL) {
        printf("Error in creating texture:%s\n", SDL_GetError());
    }
    return texture;
}

void Window:: ClearBackBuffer() {
    SDL_RenderClear(m_renderer);
}

int Window:: drawGrid() {

//window background
    SDL_Rect backgroundW{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(m_renderer, &backgroundW);
    SDL_SetRenderDrawColor(m_renderer, 30, 70, 81, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(m_renderer, 38, 43, 61, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &backgroundW);
//table background
    SDL_Rect backgroundT{ m_margin,m_margin,m_cellSize*9,m_cellSize*9 };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(m_renderer, &backgroundT);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    //SDL_SetRenderDrawColor(m_renderer, 30, 70, 81, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &backgroundT);

    //draw horizontal lines
    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(m_renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
        if ((i == 0 || i == 9) || (i + 3) % 3 == 0) {
            SDL_RenderDrawLine(m_renderer, m_cellSize, m_cellSize * (i + 1), m_cellSize * 10, m_cellSize * ((i + 1)));
            SDL_RenderDrawLine(m_renderer, 1 + m_cellSize, 1 + m_cellSize * (i + 1), 1 + m_cellSize * 10, 1 + m_cellSize * ((i + 1)));
            SDL_RenderDrawLine(m_renderer, -1 + m_cellSize, -1 + m_cellSize * (i + 1), -1 + m_cellSize * 10, -1+ m_cellSize * ((i + 1)));
        }
        else {
            SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 205);
            SDL_RenderDrawLine(m_renderer, -1 + m_cellSize, -3 + m_cellSize * (i + 1), -1 + m_cellSize * 10, -3 + m_cellSize * ((i + 1)));
        }
    }
    //draw vertical lines
    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(m_renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
        if (i == 0 || i == 9 || (i + 3) % 3 == 0) {

            SDL_RenderDrawLine(m_renderer, m_cellSize * (i + 1), m_cellSize,m_cellSize * (i + 1), m_cellSize * 10);
            SDL_RenderDrawLine(m_renderer, 1 + m_cellSize * (i + 1), 1 + m_cellSize, 1 + m_cellSize * (i + 1), 1 + m_cellSize * 10);
            SDL_RenderDrawLine(m_renderer, -1 + m_cellSize * (i + 1), -1 + m_cellSize, -1 + m_cellSize * (i + 1), -1 + m_cellSize * 10);
        }
        else {
            SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 205);
            SDL_RenderDrawLine(m_renderer, -5 + m_cellSize * (i + 1), -1 + m_cellSize, -5 + m_cellSize * (i + 1), -1 + m_cellSize * 10);
        }

    }

    //Title Background
    SDL_Rect backgroundTitle{ 0,0,SCREEN_WIDTH,50 };
    SDL_RenderDrawRect(m_renderer, &backgroundTitle);
    SDL_SetRenderDrawColor(m_renderer, 30, 70, 81, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &backgroundTitle);
    

    //Run btn
    SDL_Rect run{850,100,100,40};
    SDL_RenderDrawRect(m_renderer,&run);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &run);

    //new game btn
    SDL_Rect newGame{850,200,150,40};
    SDL_RenderDrawRect(m_renderer,&newGame);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &newGame);

    //new pattern Recognition
    SDL_Rect pttrnRecognition{850,250,250,40};
    SDL_RenderDrawRect(m_renderer,&pttrnRecognition);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &pttrnRecognition);

     //populate possible Candidates
    SDL_Rect possibleCandidates{850,300,250,40};
    SDL_RenderDrawRect(m_renderer,&possibleCandidates);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &possibleCandidates);

    //populate possible Candidates
    SDL_Rect pen2pencil{850,350,250,40};
    SDL_RenderDrawRect(m_renderer,&pen2pencil);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &pen2pencil);

    //Naked Single
    SDL_Rect nakedSingleRect{850,400,250,40};
    SDL_RenderDrawRect(m_renderer,&nakedSingleRect);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &nakedSingleRect);

    //Title
    Texture texture = Texture("SUDOKU", "Roboto-Bold.ttf", 20, { 255,255,255,255 });
    texture.SetSrcRect(20,5);
    texture.renderText();
    texture.Render();
    
     //solve btn
    Texture tex = Texture("SOLVE", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    tex.SetSrcRect(870,110);
    tex.renderText();
    tex.Render();

     //close btn
    Texture texclose = Texture("X", "Roboto-Bold.ttf", 20, { 255,255,255,255 });
    texclose.SetSrcRect(1460,15);
    texclose.renderText();
    texclose.Render();

    //pattern recognition
    Texture texpttrn = Texture("PATTERN RECOGNITION", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    texpttrn.SetSrcRect(870,260);
    texpttrn.renderText();
    texpttrn.Render();

       //possilbe candidates
    Texture texPossibleCands = Texture("POSSIBLE CANDS", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    texPossibleCands.SetSrcRect(870,310);
    texPossibleCands.renderText();
    texPossibleCands.Render();

    //pencil to pen marking
    Texture pencilToPen = Texture("PENCIL TO PEN", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    pencilToPen.SetSrcRect(870,360);
    pencilToPen.renderText();
    pencilToPen.Render();

    //naked single
    Texture nakedSingle = Texture("NAKED SINGLE", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    nakedSingle .SetSrcRect(870,410);
    nakedSingle .renderText();
    nakedSingle .Render();

    //new Game btn
    Texture newGamebtn = Texture("NEW GAME", "Roboto-Bold.ttf", 20, { 30,70,81,255 });
    newGamebtn.SetSrcRect(870,210);
    newGamebtn.renderText();
    newGamebtn.Render();
    
    

    return 0;
}
void Window::handleCursorKeys(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        if(m_cursorPos[0]>m_margin)
         m_cursorPos[0] -= m_cellSize;
         isCandidateMode=false;
        break;
    case SDLK_RIGHT:
        if(m_cursorPos[0]<m_cellSize*9)
            m_cursorPos[0] += m_cellSize;
            isCandidateMode=false;
        break;
    case SDLK_UP:
        if (m_cursorPos[1] > m_margin)
            m_cursorPos[1] -= m_cellSize;
            isCandidateMode=false;
        break;
    case SDLK_DOWN:
        if (m_cursorPos[1] < m_cellSize*9)
            m_cursorPos[1] += m_cellSize;
            isCandidateMode=false;
        break;

    }
}

void Window::handleMouseClicks(SDL_Event& event) {
    //std::cout << event.type<<std::endl;
    if ((event.type == SDL_MOUSEBUTTONDOWN || event.type==SDL_FINGERDOWN) && event.button.clicks==1) {
        isCandidateMode=false;
        int col = (event.button.x - m_margin) / (m_cellSize);
        int row = (event.button.y - m_margin) / (m_cellSize);
        if (col < 9 && row < 9 && col>=0 && row>=0) {
            m_cursorPos[0] = m_margin + col * m_cellSize;
            m_cursorPos[1] = m_margin + row * m_cellSize;
        }

        //click the solve btn
        if(event.button.x>850 && event.button.x<1000 &&event.button.y>100 && event.button.y<160){
            mRun= true;
        }

         //click the close btn
        if(event.button.x>1460 && event.button.x<1500 &&event.button.y>0 && event.button.y<50){
            setState(false);
        }

       //click the newgame btn
        if(event.button.x>850 && event.button.x<1000 &&event.button.y>200 && event.button.y<240){
            mRestart=true;
        } 
        //pattern recogniton
         if(event.button.x>850 && event.button.x<1100 &&event.button.y>250 && event.button.y<290){
            mpatternRecognition=true;
        } 
        //populate all possible candidates
        if(event.button.x>850 && event.button.x<1150 &&event.button.y>300 && event.button.y<340){
            mpossibleCandidates=true;
        } 

         if(event.button.x>850 && event.button.x<1300 &&event.button.y>350 && event.button.y<390){
            mPentoPencil=true;
        } 
         if(event.button.x>850 && event.button.x<1450 &&event.button.y>400 && event.button.y<440){
            mNakedSingle=true;
        } 


    }

    if(event.type==SDL_MOUSEBUTTONDOWN && event.button.clicks==2){
        isCandidateMode=true;
    }
     

}

void Window::drawCursor() {
    SDL_Rect cursor{ m_cursorPos[0],m_cursorPos[1],m_cellSize,m_cellSize };
    SDL_Rect cursor2{ m_cursorPos[0] + 1,m_cursorPos[1] + 1,m_cellSize - 2,m_cellSize - 2 };
    SDL_Rect cursor3{ m_cursorPos[0] + 2,m_cursorPos[1] + 2,m_cellSize - 4,m_cellSize - 4 };

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    if(isCandidateMode)
     SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    else
     SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawRect(m_renderer, &cursor);
    SDL_RenderDrawRect(m_renderer, &cursor2);
    SDL_RenderDrawRect(m_renderer, &cursor3);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(m_renderer, &cursor);
    SDL_RenderFillRect(m_renderer, &cursor2);
    SDL_RenderFillRect(m_renderer, &cursor3);

}

void Window::CapFrameRate(Uint32 starting_tick) {
    Uint32 frameTime = SDL_GetTicks() - starting_tick;
    Uint32 frameDelay = 1000 / fps;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}

SDL_Rect& Window::GetMemberOfGrayRects(int x) {
    return m_grayRects[x];
}

void Window::SetMemberOfGrayRects(int pos,int x, int y) {
    m_grayRects[pos].x=x;
    m_grayRects[pos].y = y;
}
