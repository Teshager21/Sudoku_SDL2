#include "model.h"
#include "iostream"
#include <algorithm>
class Solver{

private:
    Model* mModel;
    static Solver* sInstance;
    std::map<int,std::map<int,int>>mblocks;
    //std::map<int,std::vector<int>>rows;
    std::map<int,std::vector<int>>cols;
    std::map<int,std::vector<int>>ranks;
    std::map<int,std::vector<int>>stacks;


public:


private:
 Solver();
 ~Solver();
    


public:
void generateBlocks();

static Solver* getInstance();
bool existsInMap(int value,std::map<int,int>mp);

void solve(); 
void checkRepeatitionAcrossBlocks(std::map<int,std::map<int,int>>blocks,std::string scope,int scopeSpecifier);
int positionInMap(int value,std::map<int,int>mp);
void logMap(std::map<int,int>map);
void logMapofMapsV(std::map<int,std::map<int,std::vector<int>>>map);
void logMapofMaps(std::map<int,std::map<int,int>>map);
void figureSpecificPosition(std::map<int, std::map<int,std::vector<int>>>existingValues);
void figureSpecificPositionS(std::map<int, std::map<int,std::vector<int>>>existingValues);
int Block(int position);
void checkRepeatition(std::map<int,std::map<int,int>>blocks);
void pencilToPenMarking();
void patternRecognition(std::map<int,std::map<int,int>>blocks);
};