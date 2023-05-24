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
bool checkSelectedPosition(int selectedPosition, int filledPositions[], int filledCells);

#define fps 5000

int main(int argc, char* argv[]) {
    int tableArray[3][3][3][3];
    std::string messages="";
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
    window = SDL_CreateWindow("SUDOKU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 700, SDL_WINDOW_RESIZABLE);
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
    int gridSize = 60;
    SDL_Rect cursor{ 20 + gridSize,20 + gridSize,gridSize,gridSize };
    SDL_Rect cursor2 { cursor.x + 1,cursor.y + 1,cursor.w - 2,cursor.h - 2 };
    SDL_Rect cursor3 { cursor.x + 2,cursor.y + 2,cursor.w - 4,cursor.h - 4 };

    while (running) {
        
        starting_tick = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            int position = 0;
           
            
            if (SDL_KEYDOWN == event.type) {
                switch (event.key.keysym.sym) {
                case SDLK_1: std::cout << "the number pressed is: 1";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
     
                        receiveInput(tableArray, position, 1, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                    
                     std::cout << "the position calculated: " << position;
                     break;
                case SDLK_2: std::cout << "the number pressed is: 2";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 2, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
   
                    break;
                case SDLK_3: std::cout << "the number pressed is: 3";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 3, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                    
                    break;
                case SDLK_4: std::cout << "the number pressed is: 4";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 4, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                    
                    break;
                case SDLK_5: std::cout << "the number pressed is: 5";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 5, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                    
                    break;
                case SDLK_6: std::cout << "the number pressed is: 6";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 6, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                   
                    break;
                case SDLK_7: std::cout << "the number pressed is: 7";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 7, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                    
                    break;
                case SDLK_8: std::cout << "the number pressed is: 8";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 8, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                   
                    break;
                case SDLK_9: std::cout << "the number pressed is: 9";
                    position = ((cursor.y - 30) / gridSize) * 9 + (cursor.x - 30) / gridSize;
                    if (checkSelectedPosition(position, filledPositions, filledCells)) {
                    receiveInput(tableArray, position, 9, messages);
                    }
                    else {
                        messages = "Cell not Available!";
                    }
                   
                    break;
                case SDLK_LEFT:
                    cursor.x-=gridSize;
                    cursor2.x += gridSize;
                    cursor3.x += gridSize;
                    break;
                case SDLK_RIGHT: 
                    cursor.x += gridSize;
                    cursor2.x += gridSize;
                    cursor3.x += gridSize;
                    break;
                case SDLK_UP: 
                    cursor.y -= gridSize;
                    cursor2.y -= gridSize;
                    cursor3.y -= gridSize;
                    break;
                case SDLK_DOWN:
                    cursor.y += gridSize;
                    cursor2.y += gridSize;
                    cursor3.y += gridSize;
                    break;
                }
            }
        }

        //capFrameRate(starting_tick);
        SDL_UpdateWindowSurface(window);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
      
        //draw vertical lines
     
        for (int i = 0; i <= 9; i++) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            if ((i == 0 || i==9) || (i + 3) % 3 == 0) {
                SDL_RenderDrawLine(renderer, 21 + gridSize, 21 + gridSize * (i + 1), 21 + gridSize * 10, 21 + gridSize * ((i + 1)));
                SDL_RenderDrawLine(renderer, 22 + gridSize, 22 + gridSize * (i + 1), 22 + gridSize * 10, 22 + gridSize * ((i + 1)));
            }
            SDL_RenderDrawLine(renderer, 20 + gridSize, 20 + gridSize * (i + 1), 20 + gridSize * 10, 20 + gridSize * ((i + 1)));
          
        }

       //draw horizontal lines
       for (int i = 0; i <= 9; i++) {
           if (i == 0 || i == 9 ||(i+3)%3==0) {
               SDL_RenderDrawLine(renderer, 21 + gridSize * (i + 1), 21 + gridSize, 21 + gridSize * (i + 1), 21 + gridSize * 10);
               SDL_RenderDrawLine(renderer, 22 + gridSize * (i + 1), 22 + gridSize, 22 + gridSize * (i + 1), 22 + gridSize * 10);
           }
          SDL_RenderDrawLine(renderer, 20 + gridSize * (i + 1), 20+gridSize, 20 + gridSize * (i + 1), 20+gridSize*10);  
        }

     
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 28);
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
                        SDL_Surface* messageSurface = TTF_RenderText_Solid(font, messages.c_str(), black);
          
                    //create texture from the surface
                    col = 3 * i + k;
                    row = 3 * j + l;
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
                    SDL_Rect rect = { 20 + gridSize * (col+1) + hIndent , 20 + gridSize * (row+1) + vIndent , surface->w,surface->h };
                    SDL_Rect messageRect = { 80,40,550,30 };
                    SDL_RenderCopy(renderer, texture, NULL, &rect);
                    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawRect(renderer, &cursor);
                    SDL_RenderDrawRect(renderer, &cursor2);
                    SDL_RenderDrawRect(renderer, &cursor3);
                    SDL_RenderDrawRect(renderer, &messageRect);
                    SDL_RenderPresent(renderer);
                    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255,SDL_ALPHA_TRANSPARENT);
                    SDL_RenderFillRect(renderer, &cursor);
                    SDL_RenderPresent(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

                    

                }
            }
            
        }
        
        
    }
    //a cursor square
    //SDL_RenderPresent(renderer);
    Uint32 frameTime = SDL_GetTicks() - starting_tick;
    Uint32 frameDelay=1000/60;

    //if (frameDelay > frameTime) {
       // SDL_Delay(frameDelay - frameTime);
    //}
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

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
    j = (position - 27 * i - 9 * k ) / 3;
    if (isItRepeated("row", i * 3 + k, value, tableArray) || isItRepeated("col", j * 3 + l, value, tableArray) || isItRepeated("block", i * 3 + j, value, tableArray)) {
        messages = "Repetition, please use another value!";
    }
    else {
        tableArray[j][i][l][k] = value;
        messages = "";
    }
    std::cout <<std::endl<< "received! " <<i<<j<<k<<l<<", position is: "<<position<<" value at the position: "<<tableArray[i][j][k][l] <<std::endl;
    std::cout << "filled values are: ";
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {

                    std::cout<< tableArray[j][i][l][k]<<", ";

                }
            }
            std::cout << std::endl;
        }
    }

}

bool checkSelectedPosition(int selectedPosition, int filledPositions[], int filledCells) {
    for (int i = 0; i < filledCells; i++) {
        if (filledPositions[i] == selectedPosition) {
            return false;
        }
    }
    return true;
}