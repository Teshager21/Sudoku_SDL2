#include "window.h"
#include<SDL.h>
#include<iostream>

Window::Window(const std::string &title, int width, int height):
	m_title(title), m_width(width),m_height(height)
{
	if (!init()) {
		m_closed = true; 
	}
}
Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit(); 
}
double Window::getCellSize() { return m_cellSize; }



bool Window::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Failed to initialize\n";
		return 0;
	}
	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
	if (m_window == nullptr) {
		std::cerr << "Failed to initialize window\n";
   }
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	return true;

}

void Window::pollEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			break;
		case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_1: std::cout << "the number pressed is: 1";
               // position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                
                break;
            case SDLK_2: std::cout << "the number pressed is: 2";
               // position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_3: std::cout << "the number pressed is: 3";
                //position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_4: std::cout << "the number pressed is: 4";
                //position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_5: std::cout << "the number pressed is: 5";
               // position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_6: std::cout << "the number pressed is: 6";
               // position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_7: std::cout << "the number pressed is: 7";
                //position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_8: std::cout << "the number pressed is: 8";
                //position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_9: std::cout << "the number pressed is: 9";
                //position = ((cursor.y - 30) / cellSize) * 9 + (cursor.x - 30) / cellSize;
                

                break;
            case SDLK_LEFT:
                
                break;
            case SDLK_RIGHT:
                
                break;
            case SDLK_UP:
                
                break;
            case SDLK_DOWN:
                
                break;
            }

		default:
			break;

		}
			
	}
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