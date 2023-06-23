#include"model.h"
#include<ctime>
#include<iostream>
#include<algorithm>

Model* Model::sInstance=NULL;

Model::Model() {
    if (init()) {
        messages = ".";
    }
}
Model::~Model() {

}

Model* Model::getInstance(){
    if (!sInstance) {
        sInstance = new Model();
    }
    return sInstance;
}

bool Model::init() {
    generateFilledPositions();
    populateInitialCells();
    return true;
}

std::map<int,std::vector<int>>* Model::getCandidates(){
    return &mCandidatePositions;
}

void Model::setCandidateVector(int position,std::vector<int> vec){
    mCandidatePositions[position]=vec;    
}

void Model::setCandidateValue( int position,int value){
    if (!checkSelectedPosition(position)) { 
            if (!repeatedValue(position,value)) {   
                
                if(mCandidatePositions.count(position)){
                    (mCandidatePositions)[position].at(value-1)=value;
                }else{
                    (mCandidatePositions)[position]={0,0,0,0,0,0,0,0,0};
                    (mCandidatePositions)[position].at(value-1)=value;
                }
                 if(isPositionFilled(position)){
                    receiveInput(position,0);
                }
               
            }
        }else {
            setMessages( ("Cell "+ std::to_string(position) + " not Available! ")+std::to_string(getMembers(position/9,position%9)));
        }

}

std::string Model::getMessages() { return messages; }
int Model::getMembers(int x, int y) {
    return mBoard[x][y];
}

int Model::getFilledPosition(int x) {
    return filledPositions[x];
}

std::vector<int> Model::getVariablePositions() {
    return variablePositions;
}

void Model::setMessages(std::string message) { messages = message; }

int Model::GetFilledCells(){ return filledCells; }

void Model:: generateFilledPositions() {
    srand(time(NULL));
    for (int i = 0; i < filledCells; i++) {

        int randPos = rand() % 81;
        if (isElementofArray(filledPositions, randPos)) {
            i = i - 1;
            continue;
        }
        filledPositions[i] = randPos;
    }
}

bool Model::isElementofArray(int(&arr)[30], int value) {
    for (int i = 0; i < sizeof(arr)/sizeof(arr[i]); i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

void Model::populateInitialCells( ) {
    srand(time(NULL));
   
    int col = 0, row = 0,block=0,fill=0;
    for (int i = 0; i < filledCells; i++) {
        col = filledPositions[i] % 9;
        row = filledPositions[i] / 9;
        block = (filledPositions[i] / 27)*3+ (filledPositions[i] % 9)/3;
        do {
          fill = rand() % 9 + 1;
        }
        while(isItRepeated("row", row, fill) || isItRepeated("col", col, fill) || isItRepeated("block", block, fill));
                mBoard[row][col] = fill; 
    }
}

bool Model::isItRepeated(std::string scope, int scopeSpecifier, double value) {
    std::string rowElem;
    if (scope == "row") {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (i == scopeSpecifier) {
                    if (value == mBoard[i][j]) {
                        return true;
                    }
                }
            }
        }
    }

    if (scope == "col") {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j == scopeSpecifier) {
                    if (value == mBoard[i][j]) {
                        return true;
                    }
                }
            }
        }
    }

    if (scope == "block") {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                int position = row * 9 + col;
                if ((position / 27)*3+ (position % 9)/3 == scopeSpecifier) {
                    if (value == mBoard[row][col]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Model::isPositionFilled(int position){
    int row= position/9;
    int col=position%9;
   if(mBoard[row][col]==0){
    return false;
   }  
   return true; 
}

void Model::receiveInput( int position, int value) {
    int i=0, j=0;
    i = position / 9;
    j = position % 9;

    if(value==0){
       mBoard[i][j] = value;
       return;  
    }

    if (isItRepeated("row", i , value) || isItRepeated("col", j, value) || isItRepeated("block", (position / 27) * 3 + (position % 9) / 3, value)) {
        messages = std::to_string(value) + ": already used!";
    }
    else {
        mBoard[i][j] = value;
        variablePositions.push_back(position);
        messages = ".";
    }
}


bool Model::repeatedValue(int position,int value){

    int i=0, j=0;
    i = position / 9;
    j = position % 9;

  if (isItRepeated("row", i , value) || isItRepeated("col", j, value) || isItRepeated("block", (position / 27) * 3 + (position % 9) / 3, value)) {
        messages = std::to_string(value) + ": already used!";
        return true;
    } 
    return false; 
}

bool Model::checkSelectedPosition(int selectedPosition) {

   return isElementofArray(filledPositions,selectedPosition);
    }


bool Model::isgameWon() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {      
                    if (mBoard[i][j] == 0) {
                        return false;
                    }
                }
    }
    return true;
}

