#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>
#include<ctime>
#include<cstdlib>

int capFrameRate(Uint32 starting_tick);
int generateNumberofFilledCells();
void generateFilledPositions(int(&filledPositions)[30], const int filledCells);
void populateInitialCells(int(&tableArray)[3][3][3][3], const int filledCells, int filledPositions[]);
bool isItRepeated(std::string scope, int scopeSpecifier, double value, int(&tableArray)[3][3][3][3]);
void receiveInput(int(&tableArray)[3][3][3][3], int position, int value, std::string& messages);

#define fps 20

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
    const int filledCells = 30;//generateNumberofFilledCells();
    int filledPositions[filledCells];
    generateFilledPositions(filledPositions, filledCells);
    populateInitialCells(tableArray, filledCells, filledPositions);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("SUDOKU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_RESIZABLE);
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
            if (SDL_KEYDOWN == event.type) {
                std::cout << "key pressed down! "<<event.key.keysym.sym;
                switch (event.key.keysym.sym) {
                case SDLK_1: std::cout << "the number pressed is: 1";
                    break;
                case SDLK_2: std::cout << "the number pressed is: 2";
                    break;
                case SDLK_3: std::cout << "the number pressed is: 3";
                    break;
                case SDLK_4: std::cout << "the number pressed is: 4";
                    break;
                case SDLK_5: std::cout << "the number pressed is: 5";
                    break;
                case SDLK_6: std::cout << "the number pressed is: 6";
                    break;
                case SDLK_7: std::cout << "the number pressed is: 7";
                    break;
                case SDLK_8: std::cout << "the number pressed is: 8";
                    break;
                case SDLK_9: std::cout << "the number pressed is: 9";
                    break;
                case SDLK_LEFT: std::cout << "the number pressed is: LEFT";
                    break;
                }
            }
        }

        capFrameRate(starting_tick);
        SDL_UpdateWindowSurface(window);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
      
        //draw vertical lines
        int gridSize = 50;
        for (int i = 0; i <= 9; i++) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
           SDL_RenderDrawLine(renderer, 20+gridSize, 20 + gridSize * (i + 1), 20+gridSize*10, 20 + gridSize * ((i + 1)));
        }

       //draw horizontal lines
       for (int i = 0; i <= 9; i++) {
          SDL_RenderDrawLine(renderer, 20 + gridSize * (i + 1), 20+gridSize, 20 + gridSize * (i + 1), 20+gridSize*10);  
        }

     
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24);
    SDL_Color black = { 0,0,255,SDL_ALPHA_OPAQUE };
    //create surface containing text

    SDL_Surface* surface = TTF_RenderText_Solid(font, "4", black);
    //create texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //create a rectangle
    int hIndent = (gridSize - surface->w)*0.5;
    int vIndent = (gridSize - surface->h) * 0.5;
    int col = 0, row = 0;
   
    for ( int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {
                    char text[10];
                    sprintf_s(text, "%d", tableArray[i][j][k][l]);
                    //sprintf_s(test, "%d", 0);
                    if (text == "0") {
                        std::cout << "one instance";
                    }
                        SDL_Surface* surface = TTF_RenderText_Solid(font, text, black);
         
                    //std::cout << text << std::endl;
                    //SDL_Surface* surface = TTF_RenderText_Solid(font, text, black);
                    //create texture from the surface
                    col = 3 * i + k;
                    row = 3 * j + l;
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_Rect rect = { 20 + gridSize * (col+1) + hIndent , 20 + gridSize * (row+1) + vIndent , surface->w,surface->h };
                    SDL_Rect cursor{ 20+gridSize,20+gridSize,gridSize,gridSize };
                    SDL_RenderCopy(renderer, texture, NULL, &rect);
                    SDL_RenderCopy(renderer, texture, NULL, &cursor);
                    

                }
            }
            
        }
        
        
    }
    //a cursor square
    SDL_Rect cursor { 30,30,50,50 };
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


void generateFilledPositions(int(&filledPositions)[30], const int filledCells) {
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
        //std::cout << filledPositions[i] << ", "<<std::endl;
    }
    

}

void populateInitialCells(int(&tableArray)[3][3][3][3], const int filledCells, int filledPositions[]) {
    srand(time(NULL));
    int* start = filledPositions;
    int* finish = filledPositions + filledCells * sizeof(int);
    int pos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    pos = 27 * i + 9 * k + 3 * j + l;
                    auto exists = std::find(start, finish, pos);
                    for (int a = 0; a < filledCells; a++) {
                        if (filledPositions[a] == pos) {
                            int fill;
                            do {
                                fill = rand() % 9 + 1;
                            } while (isItRepeated("row", i * 3 + k, fill, tableArray) || isItRepeated("col", j * 3 + l, fill, tableArray) || isItRepeated("block", i * 3 + j, fill, tableArray));

                            tableArray[i][j][k][l] = fill;
                        }
                    }

                }
            }
        }
    }

}

bool isItRepeated(std::string scope, int scopeSpecifier, double value, int(&tableArray)[3][3][3][3]) {
    std::string rowElem;
    if (scope == "row") {
        for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 3; j++) {
                    for (int l = 0; l < 3; l++) {

                        if (i * 3 + k == scopeSpecifier) {
                            rowElem = rowElem + "[" + std::to_string(scopeSpecifier) + "]" + ", " + std::to_string(tableArray[i][j][k][l]) + "(" + std::to_string(i) + std::to_string(j) + std::to_string(k) + std::to_string(l) + ")";
                            if (value == tableArray[i][j][k][l]) {
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }
    return false;
}
void receiveInput(int(&tableArray)[3][3][3][3], int position, int value, std::string& messages) {
    int i, j, k, l;
    l = position % 3;
    if (position < 27) {
        i = 0;
        k = position / 9;
    }
    if (position > 26 && position < 54) {
        i = 1;
        k = (position - 27) / 9;
    }
    if (position > 53 && position < 81) {
        i = 2;
        k = (position - 54) / 9;
    }
    j = (position - 27 * i - 9 * k - 1) / 3;
    if (isItRepeated("row", i * 3 + k, value, tableArray) || isItRepeated("col", j * 3 + l, value, tableArray) || isItRepeated("block", i * 3 + j, value, tableArray)) {
        messages = "Repetition, please use another value!";
    }
    else {
        tableArray[i][j][k][l] = value;
        messages = "";
    }
}