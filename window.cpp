#include "window.h"
#include<SDL.h>
#include<iostream>
#include<SDL_ttf.h>

Window::Window(const std::string &title, int width, int height):
	m_title(title), m_width(width),m_height(height)
{
	if (!init()) {
		m_running = true; 
	}
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
}
Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
    //TTF_CloseFont(font);
    TTF_Quit();
	SDL_Quit(); 
}

bool Window::getState() { return m_running; }
void Window::setState(bool state) {m_running=state; }
double Window::getCellSize() { return m_cellSize; }

SDL_Renderer& Window::getRenderer() {
    return *m_renderer;
}

int Window::getCursorPos(int x) { return m_cursorPos[x]; }

bool Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize\n";
		return 0;
	}
	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
	if (m_window == nullptr) {
		std::cerr << "Failed to initialize window\n";
    }
    SDL_Surface* screen = NULL;
     m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(m_window);
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_FillRect(screen, NULL, white);


    for (int i = 0; i < 30; i++) {
        m_grayRects[i].x = 0; // x position
        m_grayRects[i].y =0; // y position
        m_grayRects[i].w = m_cellSize-4; // width
        m_grayRects[i].h = m_cellSize-4; // height
    }

	return true;

}

int Window:: drawGrid() {
    //draw horizontal lines

    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        if ((i == 0 || i == 9) || (i + 3) % 3 == 0) {
            SDL_RenderDrawLine(m_renderer, 21 + m_cellSize, 21 + m_cellSize * (i + 1), 21 + m_cellSize * 10, 21 + m_cellSize * ((i + 1)));
            SDL_RenderDrawLine(m_renderer, 22 + m_cellSize, 22 + m_cellSize * (i + 1), 22 + m_cellSize * 10, 22 + m_cellSize * ((i + 1)));
            SDL_RenderDrawLine(m_renderer, 20 + m_cellSize, 20 + m_cellSize * (i + 1), 20 + m_cellSize * 10, 20 + m_cellSize * ((i + 1)));
        }
        else {
            SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 120);
            SDL_RenderDrawLine(m_renderer, 20 + m_cellSize, 18 + m_cellSize * (i + 1), 20 + m_cellSize * 10, 18 + m_cellSize * ((i + 1)));
        }
    }
    //draw vertical lines
    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        if (i == 0 || i == 9 || (i + 3) % 3 == 0) {

            SDL_RenderDrawLine(m_renderer, 21 + m_cellSize * (i + 1), 21 + m_cellSize, 21 + m_cellSize * (i + 1), 21 + m_cellSize * 10);
            SDL_RenderDrawLine(m_renderer, 22 + m_cellSize * (i + 1), 22 + m_cellSize, 22 + m_cellSize * (i + 1), 22 + m_cellSize * 10);
            SDL_RenderDrawLine(m_renderer, 20 + m_cellSize * (i + 1), 20 + m_cellSize, 20 + m_cellSize * (i + 1), 20 + m_cellSize * 10);
        }
        else {
            SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 120);
            SDL_RenderDrawLine(m_renderer, 16 + m_cellSize * (i + 1), 20 + m_cellSize, 16 + m_cellSize * (i + 1), 20 + m_cellSize * 10);
        }

    }
    return 0;
}
void Window::handleCursorKeys(SDL_Event& event) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        m_cursorPos[0] -= m_cellSize;
        break;
    case SDLK_RIGHT:
        m_cursorPos[0] += m_cellSize;
        break;
    case SDLK_UP:
        m_cursorPos[1] -= m_cellSize;
        break;
    case SDLK_DOWN:
        m_cursorPos[1] += m_cellSize;
        break;

    }
}

void Window::drawCursor() {
    SDL_Rect cursor{ m_cursorPos[0],m_cursorPos[1],m_cellSize,m_cellSize };
    SDL_Rect cursor2{ m_cursorPos[0] + 1,m_cursorPos[1] + 1,m_cellSize - 2,m_cellSize - 2 };
    SDL_Rect cursor3{ m_cursorPos[0] + 2,m_cursorPos[1] + 2,m_cellSize - 4,m_cellSize - 4 };

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
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
