#include "model.h"
#include "iostream"

class Solver{

private:
    Model* mModel;
    static Solver* sInstance;

public:

private:
 Solver();
 ~Solver();
    


public:

static Solver* getInstance();

void solve(); 


};