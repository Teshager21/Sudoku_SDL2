#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>
int capFrameRate(Uint32 starting_tick);
int generateNumberofFilledCells();

#define fps 60

int main(int argc, char* argv[]) {
    int tableArray[3][3][3][3];
//initialize the table array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    tableArray[i][j][k][l] = 0;
                }
            }

        }
    }
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("SUDOKU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "window not created! " << SDL_GetError();
    }
    std::cout << generateNumberofFilledCells();

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
        //Render grid
        //draw vertical lines
        int gridSize = 30;
        for (int i = 0; i <= 9; i++) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
           SDL_RenderDrawLine(renderer, 50+gridSize, 50 + gridSize * (i + 1), 50+gridSize*10, 50 + gridSize * ((i + 1)));
        }

    //draw horizontal lines
       for (int i = 0; i <= 9; i++) {
          SDL_RenderDrawLine(renderer, 50 + gridSize * (i + 1), 50+gridSize, 50 + gridSize * (i + 1), 50+gridSize*10);  
           //cell values
        }

       //char text[10];
       //int number = 42;
       //sprintf_s(text, "%d",number);
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 20);
    SDL_Color black = { 0,0,0,SDL_ALPHA_OPAQUE };
    //create surface containing text

    SDL_Surface* surface = TTF_RenderText_Solid(font, "4", black);
    //create texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Render the texture screen
    //create a rectangle
    for ( int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    char text[10];
                    sprintf_s(text, "%d", tableArray[i][j][k][l]);
                    SDL_Surface* surface = TTF_RenderText_Solid(font, text, black);
                    //create texture from the surface
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_Rect rect = { 50 + gridSize * (i + 1) + (gridSize - surface->w) * 0.5 , 50 + gridSize * (j + 1) + (gridSize - surface->h) * 0.5 , surface->w,surface->h };
                    SDL_RenderCopy(renderer, texture, NULL, &rect);

                }
            }
            
        }
        
        
    }
    //SDL_Rect rect = { 50+gridSize+(gridSize-surface->w)*0.5 , 50 +gridSize + (gridSize - surface->h) * 0.5 , surface->w,surface->h};

   

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);

}

    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;

}



int capFrameRate(Uint32 starting_tick) {

    if ((1000 / fps) > SDL_GetTicks() - starting_tick) {
        SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
    }
    return 0;

}

int generateNumberofFilledCells() {
    srand(time(NULL));
    int filledCells = rand() % 11 + 30;
    return filledCells;
}


void generateFilledPositions(int(&filledPositions)[], const int filledCells) {
    srand(time(NULL));

    for (int i = 0; i < filledCells; i++) {

        int randPos = rand() % 81;
        //check if the value already exists and repeat the loop step and try again if it does
        int* begin = filledPositions;
        int* end = filledPositions + filledCells / sizeof(int);
        auto ptr = std::find(begin, end, randPos);
        if (ptr != end) {
            i = i - 1;
            continue;
        }
        filledPositions[i] = randPos;
    }

}

