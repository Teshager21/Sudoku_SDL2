#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>
#include<ctime>
#include<cstdlib>  
#include"window.h"
#include "model.h"


#define fps 60
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define cellSize 60


int capFrameRate(Uint32 starting_tick);
int generateNumberofFilledCells();
void generateFilledPositions(int(&filledPositions)[30], const int filledCells);
void populateInitialCells(int(&tableArray)[3][3][3][3], const int filledCells, int filledPositions[30]);
bool isItRepeated(std::string scope, int scopeSpecifier, double value, int(&tableArray)[3][3][3][3]);
void receiveInput(int(&tableArray)[3][3][3][3], int position, int value, std::string& messages);
bool checkSelectedPosition(int selectedPosition, int filledPositions[], int filledCells);
bool isgameWon(int tableArray[3][3][3][3]);
int drawGrid(SDL_Renderer* renderer);
void handleKeyEvents(int selectedValue, int (&cursorPos)[2], int filledCells, int(&filledPositions)[30], int(&tableArray)[3][3][3][3], std::string messages);
void handleCursorKeys(SDL_Event& event, int (&cursorPos)[2]);
void handleKeyboardEvents(SDL_Event& event, int (&cursorPos)[2], int filledCells, int(&filledPositions)[30], int(&tableArray)[3][3][3][3], std::string messages);
void drawCursor(int(&cursorPos)[2], SDL_Renderer& renderer);
void displayMessage(SDL_Renderer& renderer, std::string messages);
void pollEvents(SDL_Event& event, bool& running, int(&cursorPos)[2], int filledCells, int(&filledPositions)[30], int(&tableArray)[3][3][3][3], std::string messages);
void renderTable(int(&tableArray)[3][3][3][3], SDL_Renderer& renderer, int(&cursorPos)[2], int filledCells, int(&filledPositions)[30]);


int main(int argc, char* argv[]) {
    int tableArray[3][3][3][3]{{{0,0,0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    std::string messages="";
    Window window("SUDOKU",SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_Renderer& renderer = window.getRenderer();
    const int filledCells = 30;
    int filledPositions[30];
    Model model;
    //00
    model.generateFilledPositions();
    generateFilledPositions(filledPositions, filledCells);
    //std::cout << "list of filled position: ";
    //for (int i = 0; i < filledCells; i++) {
        //std::cout << filledPositions[i] << ", ";
    //}
    //std::cout << std::endl;

    populateInitialCells(tableArray, filledCells, filledPositions);
    model.populateInitialCells();
    int (*tArray)[3][3][3] = model.getArray();
     
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {
                    //std::cout << tableArray[i][j][k][l] << "[" << i << j << k << l << "]" << "[" << 27 * i + 9 * k + 3 * j + l << "], ";
                    std::cout<<&tArray[i][j][k][l]<<"["<<i<<j<<k<<l<<"]" << "[" << 27 * i + 9 * k + 3 * j + l << "], ";
                }
            }

        }
    }
    TTF_Init();
    Uint32 starting_tick;
    SDL_Event event;
    bool running = true;
    int cursorPos[2] = { 20 + cellSize,20 + cellSize };
   
    while (running) {
        SDL_GL_SetSwapInterval(1);
        starting_tick = SDL_GetTicks();
        pollEvents(event, running, cursorPos, filledCells, filledPositions, tableArray, messages);
        SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(&renderer);
        drawGrid(&renderer);

    //TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 28);
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Color black = { 0,0,0,SDL_ALPHA_OPAQUE };
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    SDL_Color blue = { 0,0,255,SDL_ALPHA_OPAQUE };
    SDL_Color white = { 255,255,255,SDL_ALPHA_OPAQUE };

    renderTable(tableArray, renderer, cursorPos, filledCells, filledPositions);
    
    displayMessage(renderer, messages);
   
    Uint32 frameTime = SDL_GetTicks() - starting_tick;
    Uint32 frameDelay=1000/fps;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);

    }

    //clearing
    /*SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);*/

}
    return 0;

}

bool isElementofArray(int (&arr)[30], int value) {
    for(int i = 0; i < sizeof(arr); i++) {
        if (arr[i] == value) {
            return true;
       }
    }
    return false;
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
    std::cout << "the old generation: " << filledCells << " size of filled pos: " << sizeof(filledPositions) << std::endl;
    for (int i = 0; i < filledCells; i++) {

        int randPos = rand() % 81;
        if (isElementofArray(filledPositions,randPos)) {
            i = i - 1;
            continue;
        }
        filledPositions[i] = randPos;
        //std::cout<<"Generated Position: " << i << ": " << filledPositions[i] << ", " << std::endl;
    }
    

}

void populateInitialCells(int(&tableArray)[3][3][3][3], const int filledCells, int filledPositions[30]) {
    srand(time(NULL));
    //int* start = filledPositions;
    //int* finish = filledPositions + filledCells * sizeof(int);
    int pos = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    pos = 27 * i + 9 * k + 3 * j + l;
                    //auto exists = std::find(start, finish, pos);
                    for (int a = 0; a < filledCells; a++) {
                       if (filledPositions[a] == pos) {
                         // if (isElementofArray(filledPositions, pos)) {
                            int fill;
                            do {
                                fill = rand() % 9 + 1;
                            } while (isItRepeated("row", i * 3 + k, fill, tableArray) || isItRepeated("col", j * 3 + l, fill, tableArray) || isItRepeated("block", i * 3 + j, fill, tableArray));

                            tableArray[j][i][l][k] = fill;
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

    if (scope == "col") {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {

                        if (j * 3 + l == scopeSpecifier) {
                            if (value == tableArray[i][j][k][l]) {
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }

    if (scope == "block") {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {

                        if (i * 3 + j == scopeSpecifier) {
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
        messages =std::to_string(value) + ": already used!";
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

bool isgameWon(int tableArray[3][3][3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (tableArray[i][j][k][l] == 0) {
                        return false;
                    }
                }
            }

        }
    }
    return true;
}

int drawGrid(SDL_Renderer* renderer) {
    //draw horizontal lines

    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        if ((i == 0 || i == 9) || (i + 3) % 3 == 0) {
            SDL_RenderDrawLine(renderer, 21 + cellSize, 21 + cellSize * (i + 1), 21 + cellSize * 10, 21 + cellSize * ((i + 1)));
            SDL_RenderDrawLine(renderer, 22 + cellSize, 22 + cellSize * (i + 1), 22 + cellSize * 10, 22 + cellSize * ((i + 1)));
            SDL_RenderDrawLine(renderer, 20 + cellSize, 20 + cellSize * (i + 1), 20 + cellSize * 10, 20 + cellSize * ((i + 1)));
        }
        else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 120);
            SDL_RenderDrawLine(renderer, 20 + cellSize, 18 + cellSize * (i + 1), 20 + cellSize * 10, 18 + cellSize * ((i + 1)));
        }
    }
    //draw vertical lines
    for (int i = 0; i <= 9; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        if (i == 0 || i == 9 || (i + 3) % 3 == 0) {

            SDL_RenderDrawLine(renderer, 21 + cellSize * (i + 1), 21 + cellSize, 21 + cellSize * (i + 1), 21 + cellSize * 10);
            SDL_RenderDrawLine(renderer, 22 + cellSize * (i + 1), 22 + cellSize, 22 + cellSize * (i + 1), 22 + cellSize * 10);
            SDL_RenderDrawLine(renderer, 20 + cellSize * (i + 1), 20 + cellSize, 20 + cellSize * (i + 1), 20 + cellSize * 10);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 120);
            SDL_RenderDrawLine(renderer, 16 + cellSize * (i + 1), 20 + cellSize, 16 + cellSize * (i + 1), 20 + cellSize * 10);
        }

    }
    return 0;
}

void handleKeyEvents(int selectedValue,int (&cursorPos)[2], int filledCells, int(&filledPositions)[30], int(&tableArray)[3][3][3][3], std::string messages) {
    int position = ((cursorPos[1] - 30) / cellSize) * 9 + (cursorPos[0] - 30) / cellSize;
    if (checkSelectedPosition(position, filledPositions, filledCells)) {

        receiveInput(tableArray, position, selectedValue, messages);
    }
    else {
        messages = "Cell not Available! " + std::to_string(position);
    }

    std::cout << "the position calculated: " << position;

}

void handleCursorKeys(SDL_Event& event,int (&cursorPos)[2]) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
        cursorPos[0] -= cellSize;
        //cursor2.x -= cellSize;
        //cursor3.x -= cellSize;
        break;
    case SDLK_RIGHT:
        cursorPos[0] += cellSize;
        //cursor2.x += cellSize;
        //cursor3.x += cellSize;
        break;
    case SDLK_UP:
        cursorPos[1] -= cellSize;
        //cursor2.y -= cellSize;
        //cursor3.y -= cellSize;
        break;
    case SDLK_DOWN:
        cursorPos[1] += cellSize;
        //cursorPos[1] += cellSize;
        //cursorPos[1] += cellSize;
        break;

    }
}
void handleKeyboardEvents(SDL_Event& event,int (&cursorPos)[2], int filledCells, int(&filledPositions)[30], int(&tableArray)[3][3][3][3], std::string messages) {
    if (SDL_KEYDOWN == event.type) {
        switch (event.key.keysym.sym) {
        case SDLK_1: std::cout << "the number pressed is: 1";
            handleKeyEvents(1, cursorPos, filledCells, filledPositions, tableArray, messages);
            break;
        case SDLK_2: std::cout << "the number pressed is: 2";
            handleKeyEvents(2, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_3: std::cout << "the number pressed is: 3";
            handleKeyEvents(3, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_4: std::cout << "the number pressed is: 4";
            handleKeyEvents(4, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_5: std::cout << "the number pressed is: 5";

            handleKeyEvents(5, cursorPos, filledCells, filledPositions, tableArray, messages);
            break;
        case SDLK_6: std::cout << "the number pressed is: 6";
            handleKeyEvents(6, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_7: std::cout << "the number pressed is: 7";
            handleKeyEvents(7, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_8: std::cout << "the number pressed is: 8";
            handleKeyEvents(8, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_9: std::cout << "the number pressed is: 9";
            handleKeyEvents(9, cursorPos, filledCells, filledPositions, tableArray, messages);

            break;
        case SDLK_LEFT:
            handleCursorKeys(event, cursorPos);
            break;
        case SDLK_RIGHT:
            handleCursorKeys(event, cursorPos);
            break;
        case SDLK_UP:
            handleCursorKeys(event, cursorPos);
            break;
        case SDLK_DOWN:
            handleCursorKeys(event, cursorPos);
            break;
        }
    }
}

void displayMessage(SDL_Renderer& renderer,std::string messages) {
    SDL_Color red = { 255,0,0,SDL_ALPHA_OPAQUE };
    TTF_Font* messageFont = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-Regular.ttf", 24);
    SDL_Surface* messageSurface = TTF_RenderText_Solid(messageFont, messages.c_str(), red);
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(&renderer, messageSurface);
    
    SDL_Rect messageRect = { 80,40,200,19 };
    SDL_RenderCopy(&renderer, msgTexture, NULL, &messageRect);

    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(&renderer, &messageRect);
}

void drawCursor(int (&cursorPos)[2],SDL_Renderer& renderer) {
    SDL_Rect cursor{ cursorPos[0],cursorPos[1],cellSize,cellSize };
    SDL_Rect cursor2{ cursorPos[0] + 1,cursorPos[1] + 1,cellSize - 2,cellSize - 2 };
    SDL_Rect cursor3{ cursorPos[0] + 2,cursorPos[1] + 2,cellSize - 4,cellSize - 4 };

    SDL_SetRenderDrawBlendMode(&renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(&renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(&renderer, &cursor);
    SDL_RenderDrawRect(&renderer, &cursor2);
    SDL_RenderDrawRect(&renderer, &cursor3);

    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(&renderer, &cursor);
    SDL_RenderFillRect(&renderer, &cursor2);
    SDL_RenderFillRect(&renderer, &cursor3);

}

void pollEvents(SDL_Event& event,bool& running,int (&cursorPos)[2],int filledCells,int (&filledPositions)[30],int (&tableArray)[3][3][3][3],std::string messages) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }

        int position = 0;
        handleKeyboardEvents(event, cursorPos, filledCells, filledPositions, tableArray, messages);
    }
}

void renderTable(int(&tableArray)[3][3][3][3], SDL_Renderer& renderer, int(&cursorPos)[2], int filledCells, int(&filledPositions)[30]) {
    TTF_Font* font = TTF_OpenFont("C:\\Users\\PC\\Downloads\\Roboto-BoldItalic.ttf", 28);
    SDL_Surface* surface = nullptr;
    //create texture from the surface
    SDL_Texture* texture = nullptr;
    int col = 0, row = 0;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {
                    char text[10];
                    char test[10];
                    sprintf_s(text, "%d", tableArray[i][j][k][l]);
                    sprintf_s(test, "%d", 0);
                    if (tableArray[i][j][k][l] == 0) {
                        surface = TTF_RenderText_Solid(font, text, { 255,255,255,0 });

                    }
                    else {
                        int pos = 27 * i + 9 * j + 3 * k + l;
                        if (checkSelectedPosition(pos, filledPositions, filledCells)) {
                            surface = TTF_RenderText_Solid(font, text, { 0,124,70 });
                        }
                        else {
                            surface = TTF_RenderText_Solid(font, text, { 0,0,200 });
                        }
                    }

                    int hIndent = (cellSize - surface->w) * 0.5;
                    int vIndent = (cellSize - surface->h) * 0.5;

                    //create texture from the surfaces
                    col = 3 * i + k;
                    row = 3 * j + l;
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, surface);
                    SDL_Rect rect = { 20 + cellSize * (col + 1) + hIndent , 20 + cellSize * (row + 1) + vIndent , surface->w,surface->h };
                    SDL_RenderCopy(&renderer, texture, NULL, &rect);

                    //render the cursor
                    drawCursor(cursorPos, renderer);

                    SDL_SetRenderDrawColor(&renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
                    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderPresent(&renderer);

                }

            }


        }
    }
}