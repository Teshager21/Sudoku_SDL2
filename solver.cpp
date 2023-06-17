#include "solver.h"

Solver* Solver::sInstance = nullptr;

Solver::Solver(){

   mModel= Model::getInstance();

}

Solver::~Solver(){

}

Solver* Solver::getInstance(){ 
   if (sInstance!=nullptr)
        sInstance = new Solver(); 

    return sInstance;}

void Solver::solve(){
  std::cout<<"Problem solved!";
}

