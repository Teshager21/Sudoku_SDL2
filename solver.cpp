#include "solver.h"

Solver* Solver::sInstance = nullptr;

Solver::Solver(){

   mModel= Model::getInstance();
   std::map<int,std::map<int,int>>mblocks={};
   

}

Solver::~Solver(){

}

Solver* Solver::getInstance(){ 
   if (sInstance!=nullptr)
        sInstance = new Solver(); 

    return sInstance;}

void Solver::solve(){
  std::cout<<"Problem solved!";
  generateBlocks();
}

void Solver::generateBlocks(){
int position,row,col,blockNum,value;

std::map<int,std::map<int,int>>b;
for(int m=0;m<9;m++){
   std::map<int,int>block;
      for(int i=0;i<9;i++){
         for(int j=0;j<9;j++){
            position= i*9 + j;
               blockNum = (position / 27)*3+ (position % 9)/3;

               if (blockNum==m){
                  value=Model::getInstance()->getMembers(i,j);
                  block[position]=value;
               }
         }
      }
b[m]=(block);
}
  logMapofMaps(b);
  checkRepeatitionAcrossBlocks(b,"Rank",0);


}

void Solver::checkRepeatitionAcrossBlocks(std::map<int,std::map<int,int>>blocks,std::string scope, int scopeSpecifier){
   //returns values that are repeated twice in a stack or a rank along with their position
std::map<int,int>repeats;
std::map<int, std::map<int,std::vector<int>>>existingValues;
if (scope=="Rank"){
 if(scopeSpecifier==0){
      for(int i=0;i<3;i++){
         for (int j=1;j<=9;j++){
            if(existsInMap(j,blocks[i])){
               existingValues[j][j].push_back(positionInMap(j,blocks[i]));
               if(repeats.count(j)==0)
                  repeats[j]=1;
               else
                  repeats[j]+=1;

            }

         }

      }
      std::cout<<std::endl<<"Repeats\n";
      logMap(repeats);

       std::cout<<std::endl<<"Values\n";
       logMapofMapsV(existingValues);
//remove elements that are repeated twice
      for(const auto& pair:existingValues){
         if(repeats[pair.first]==2){}
         else{
            existingValues.erase(pair.first);  
         }
      }

      std::cout<<std::endl<<"Revised Values\n";
      logMapofMapsV(existingValues);
      std::cout<<"some more\n";
      figureSpecificPosition(existingValues);
      std::cout<<"no more\n";

   }

}


}

bool Solver::existsInMap(int value,std::map<int,int>mp){
   for(const auto& pair:mp){
      if(pair.second==value){
          return true;
      }
     
      }
   return false;
}

int Solver::positionInMap(int value,std::map<int,int>mp){
   int r;
   for(const auto& pair:mp){
      if(pair.second==value){
          r=pair.first;
      }
     
   }
  return r;
}


void Solver::logMap(std::map<int,int>map){
    for (auto& pair : map) {
      std::cout << pair.first<<"["<<pair.second<<"], ";
    }
    std::cout <<  std::endl;
}

void Solver::logMapofMapsV(std::map<int,std::map<int,std::vector<int>>>b){
  for (auto& map : b) {
    for (auto& pair : map.second) {
      if(pair.second.size()>1)
       std::cout << pair.first<<"[" << (pair.second).at(0)<<"," << (pair.second).at(1)<<"], ";
    }
    std::cout <<  std::endl;
  } 

}
void Solver::logMapofMaps(std::map<int,std::map<int,int>>b){
  for (auto& map : b) {
    for (auto& pair : map.second) {
      std::cout << pair.first<<"[" << (pair.second)<<"], ";
    }
    std::cout <<  std::endl;
  } 

}

void Solver::figureSpecificPosition(std::map<int, std::map<int,std::vector<int>>>existingValues){
  
   int row,block;
   for(const auto& mp:existingValues){
      for(const auto& pair:mp.second){
         std::cout<<pair.first<<"["<<pair.second[0]<<","<<pair.second[1]<<"], ";
         //figure out the row---for ranks
         int row1= pair.second[0]/9;
         int row2=pair.second[1]/9;
         int posMin,posMax;
         if(abs((row1-row2))==2){
               row=(row1+row2)/2;
         }else{
            if(row1>row2){
               posMax=pair.second[0];
               posMin=pair.second[1];
            }else{
               posMax=pair.second[1];
               posMin=pair.second[0];
            }
         if(Block(posMax)==Block(posMax+9))
                  row=(posMax/9)+1;
         else
               row=(posMin/9)-1;

         }

         //figure out the three potential positions

         //find the block
         int block0= Block(pair.second[0]);
         int block1=Block(pair.second[1]);
            int blockMin;
         if(abs(block0-block1)==2){
            block=(block0+block1)/2;
         }else{
               if(block0>block1){
                  blockMin =block1;
               }else{blockMin=block0;}

               if(blockMin==0 || blockMin==3 || blockMin==6){
               block= blockMin+2;
         }else{
               block= blockMin-1;
         }

         }

         std::cout<<"select row is "<<row<<" select block is: "<<block<<std::endl;
         //three potential columns
         int col0= block*3;
         int col1= col0+1;
         int col2=col1+1;
         int pos0 = row*9+col0;
         int pos1= row*9 +col1;
         int pos2= row*9 +col2;
         std::cout<<"list of columns "<<col0<<", "<<col1<<", "<<col2<<std::endl;
         std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

         //narrow down to empty positions
         std::vector<int> cands {0,0,0};
         std::cout<<"the value at postion: "<<pos0<<" is: "<<Model::getInstance()->getMembers(row,col0)<<std::endl;
         if(!Model::getInstance()->isPositionFilled(pos0))
               cands[0]=(pos0);
         if(!Model::getInstance()->isPositionFilled(pos1))
               cands[1]=(pos1);
         if(!Model::getInstance()->isPositionFilled(pos2))
               cands[2]=(pos2);

         //check which of the empty positions are viable and fill them
         if(cands.size()==1){
            Model::getInstance()->receiveInput(cands[0],pair.first);
         }
         if (cands.size()>1){
            for ( int i=0;i<cands.size();i++){
               Model::getInstance()->setCandidateValue(cands[i],pair.first);
            }
         }
         //change single pencil markings into pen markings
      } 
   }
}

int Solver::Block(int position){
   return (position / 27)*3+ (position % 9)/3; ;
}

