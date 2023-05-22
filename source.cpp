#include<iostream>
#include<SDL.h>
int capFrameRate(Uint32 starting_tick);

#define fps 60

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("SUDOKU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "window not created! " << SDL_GetError();
    }

    SDL_Surface* screen = NULL;
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);
    Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_FillRect(screen, NULL, white);

    Uint32 starting_tick;
    SDL_Event event;
    bool running = true;
    while (running) {
        starting_tick = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }

        capFrameRate(starting_tick);
        SDL_UpdateWindowSurface(window);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 9; i++) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, 75, 50 + 25 * (i + 1), 275, 50 + 25 * ((i + 1)));
        }
        for (int i = 0; i < 9; i++) {

            SDL_RenderDrawLine(renderer, 50 + 25 * (i + 1), 75, 50 + 25 * (i + 1), 275);
        }

        SDL_RenderPresent(renderer);




    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



int capFrameRate(Uint32 starting_tick) {

    if ((1000 / fps) > SDL_GetTicks() - starting_tick) {
        SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
    }
    return 0;

}

