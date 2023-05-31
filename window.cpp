#include "window.h"
#include<SDL.h>
#include<iostream>
#include<SDL_ttf.h>

Window::Window(const std::string &title, int width, int height):
	m_title(title), m_width(width),m_height(height)
{
	if (!init()) {
		m_closed = true; 
	}
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
}
Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
    TTF_Quit();
	SDL_Quit(); 
}
double Window::getCellSize() { return m_cellSize; }

SDL_Renderer& Window::getRenderer() {
    return *m_renderer;
}

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
void Window::handleCursorKeys(SDL_Event& event, int(&cursorPos)[2]) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        cursorPos[0] -= m_cellSize;
        break;
    case SDLK_RIGHT:
        cursorPos[0] += m_cellSize;
        break;
    case SDLK_UP:
        cursorPos[1] -= m_cellSize;
        break;
    case SDLK_DOWN:
        cursorPos[1] += m_cellSize;
        break;

    }
}