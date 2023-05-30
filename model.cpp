#include"model.h"
#include<ctime>
#include<iostream>

Model::Model() {

}
Model::~Model() {

}

bool Model::init() {
    int tableArray[3][3][3][3] {{{0,0,0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} };
    messages = "";
    return true;
}

std::string Model::getMessages() { return messages; }

void Model::setMessages(std::string message) { messages = message; }

void Model:: generateFilledPositions(int(&filledPositions)[30], const int filledCells) {
    srand(time(NULL));

    for (int i = 0; i < filledCells; i++) {

        int randPos = rand() % 81;
        if (isElementofArray(filledPositions, randPos)) {
            i = i - 1;
            continue;
        }
        filledPositions[i] = randPos;
        std::cout << "Generated Position: " << i << ": " << filledPositions[i] << ", " << std::endl;
    }


}

bool Model::isElementofArray(int(&arr)[30], int value) {
    for (int i = 0; i < sizeof(arr); i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

void Model::populateInitialCells( ) {
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
                            } while (isItRepeated("row", i * 3 + k, fill) || isItRepeated("col", j * 3 + l, fill) || isItRepeated("block", i * 3 + j, fill));

                            tableArray[j][i][l][k] = fill;
                        }
                    }

                }
            }
        }
    }


}

bool Model::isItRepeated(std::string scope, int scopeSpecifier, double value) {
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

void Model::receiveInput( int position, int value) {
    int i=0, j, k, l;
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
    j = (position - 27 * i - 9 * k) / 3;
    if (isItRepeated("row", i * 3 + k, value) || isItRepeated("col", j * 3 + l, value) || isItRepeated("block", i * 3 + j, value)) {
        messages = std::to_string(value) + ": already used!";
    }
    else {
        tableArray[j][i][l][k] = value;
        messages = "";
    }
    std::cout << std::endl << "received! " << i << j << k << l << ", position is: " << position << " value at the position: " << tableArray[i][j][k][l] << std::endl;
    std::cout << "filled values are: ";
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {

                    std::cout << tableArray[j][i][l][k] << ", ";

                }
            }
            std::cout << std::endl;
        }
    }

}

bool Model::checkSelectedPosition(int selectedPosition) {
    for (int i = 0; i < filledCells; i++) {
        if (filledPositions[i] == selectedPosition) {
            return false;
        }
    }
    return true;
}

bool Model::isgameWon() {
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

