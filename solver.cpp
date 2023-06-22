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
  generateBlocks();
}

void Solver::generateBlocks(){
   int position,row,col,blockNum,value;
   std::map<int,std::map<int,int>>b; //blockNum:{position:value}
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
   //PENCIL MARKING CANDIDATES
   checkRepeatition(b);
   checkRepeatition(b);
   //PATTERN RECOGNITION USING GHOST/PHANTOM NUMBERS
   patternRecognition(b);

}

void Solver::checkRepeatition(std::map<int,std::map<int,int>>blocks){
   //Looks across stacks and ranks and calculates pen-marked and pencilmarked values for values that are repeated twice across a rank or a stack
   checkRepeatitionAcrossBlocks(blocks,"Rank",0);
   checkRepeatitionAcrossBlocks(blocks,"Rank",1);
   checkRepeatitionAcrossBlocks(blocks,"Rank",2);
   checkRepeatitionAcrossBlocks(blocks,"Stack",0);
   checkRepeatitionAcrossBlocks(blocks,"Stack",1);
   checkRepeatitionAcrossBlocks(blocks,"Stack",2);
}

void Solver::checkRepeatitionAcrossBlocks(std::map<int,std::map<int,int>>blocks,std::string scope, int scopeSpecifier){
   //calculates values that are repeated twice in a stack or a rank along with their position
std::map<int,int>repeats;
std::map<int, std::map<int,std::vector<int>>>existingValues; //value:{pos:freq}
//RANKS
if (scope=="Rank"){
      for(int i=0;i<3;i++){
         for (int j=1;j<=9;j++){
            if(existsInMap(j,blocks[i+scopeSpecifier*3])){
               existingValues[j][j].push_back(positionInMap(j,blocks[i+scopeSpecifier*3]));
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
//STACK
   if (scope=="Stack"){
      for(int i=0;i<3;i++){
         for (int j=1;j<=9;j++){
            if(existsInMap(j,blocks[3*i+scopeSpecifier])){
               existingValues[j][j].push_back(positionInMap(j,blocks[3*i+scopeSpecifier]));
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
      figureSpecificPositionS(existingValues);
      std::cout<<"no more\n";

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

int Solver::Block(int position){
   return (position / 27)*3+ (position % 9)/3;
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
            int col0= block%3*3;
            int col1= col0+1;
            int col2=col1+1;
            int pos0 = row*9+col0;
            int pos1= row*9 +col1;
            int pos2= row*9 +col2;
            std::cout<<"list of columns "<<col0<<", "<<col1<<", "<<col2<<std::endl;
            std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

            //narrow down to empty positions
            std::vector<int> cands {0,0,0};
            if(!Model::getInstance()->isPositionFilled(pos0))
               cands[0]=(pos0);
            if(!Model::getInstance()->isPositionFilled(pos1))
               cands[1]=(pos1);
            if(!Model::getInstance()->isPositionFilled(pos2))
               cands[2]=(pos2);

            //check which of the empty positions are viable and fill them
            if(cands.size()==1){
               Model::getInstance()->receiveInput(cands[0],pair.first);
               std::cout<<"certain fill: "<<cands[0]<<" @ "<<pair.first<<std::endl;
            }
            if (cands.size()>1){
               for ( int i=0;i<cands.size();i++){
                  Model::getInstance()->setCandidateValue(cands[i],pair.first);
               }
            }
      
         } 
      }
      //CHANGE PENCIL MARKINGS INTO PEN-MARKINGS
      pencilToPenMarking();

}

void Solver::pencilToPenMarking(){

      //CHANGE PENCIL MARKINGS INTO PEN-MARKINGS
      std::map<int,std::vector<int>> *CandidatePositions;// key=postions, values=candidate values
      CandidatePositions=Model::getInstance()->getCandidates();
      std::map<int,int>candpos={{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0}}; //candidatevalues: their frequency in a block

      for(const auto& pair:*CandidatePositions){
         for(int b=0;b<9;b++){
            if(Block(pair.first)==b){
               //for 1-9 go through candidate of each position then then count its occurence- change the value to pen-marking if it is not repeated
               //loop through 1-9
            for(int i=1;i<=9;i++){
               //loop through the candidate values at the position and count them
                  for(int j=0;j<9;j++){
                     if (pair.second[j]==i){
                        candpos[i]=candpos[i]+1;
                     }
                  }
               }
      
            }
         }
      }

      std::cout<<"List of cands with frequency"<<std::endl;
      for(const auto& pair:candpos){
         if(pair.second==1){
         
            for(const auto& cand:*CandidatePositions){
               if(std::find(cand.second.begin(), cand.second.end(), pair.first) != cand.second.end()){
               
                  for(int i=0;i<9;i++){
                     if(Block(cand.first)==i){
                        std::cout<<pair.first<<"["<<pair.second<<"]@"<<cand.first<<", ";
                        Model::getInstance()->receiveInput(cand.first,pair.first);
                        Model::getInstance()->setCandidateVector(cand.first,{0,0,0,0,0,0,0,0,0});
                     }
                     
                  }
               
               }
            }
         }
      }

}


void Solver::figureSpecificPositionS(std::map<int, std::map<int,std::vector<int>>>existingValues){
  
   int col,block;
   //existing values: value: {pos1,pos2}
   
      for(const auto& mp:existingValues){
         for(const auto& pair:mp.second){
            std::cout<<pair.first<<"["<<pair.second[0]<<","<<pair.second[1]<<"], ";
            //figure out the col---for stacks
            int col1= pair.second[0]%9;
            int col2= pair.second[1]%9;
            int posMin,posMax;
            if(abs((col1-col2))==2){
                  col=(col1+col2)/2;
            }else{
               if(col1>col2){
                  posMax=pair.second[0];
                  posMin=pair.second[1];
               }else{
                  posMax=pair.second[1];
                  posMin=pair.second[0];
               }
               if(Block(posMax)==Block(posMax+1))
                  col=(posMax%9)+1;
               else
                  col=(posMin%9)-1;
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

                  if(blockMin==0 || blockMin==1 || blockMin==2){
                     block= blockMin+6;
                  }else{
                     block= blockMin-3;
                  }
            }
            std::cout<<"select col is "<<col<<" select block is: "<<block<<std::endl;
            //three potential rows
            int row0= (block/3)*3;
            int row1= row0+1;
            int row2= row1+1;
            int pos0= row0*9 +col;
            int pos1= row1*9 +col;
            int pos2= row2*9 +col;
            std::cout<<"list of rows "<<row0<<", "<<row1<<", "<<row2<<std::endl;
            std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

            //narrow down to empty positions
            std::vector<int> cands {0,0,0};
            if(!Model::getInstance()->isPositionFilled(pos0))
               cands[0]=(pos0);
            if(!Model::getInstance()->isPositionFilled(pos1))
               cands[1]=(pos1);
            if(!Model::getInstance()->isPositionFilled(pos2))
               cands[2]=(pos2);

            //check which of the empty positions are viable and fill them
            if(cands.size()==1){
               Model::getInstance()->receiveInput(cands[0],pair.first);
               std::cout<<"certain fill: "<<cands[0]<<" @ "<<pair.first<<std::endl;
            }
            if (cands.size()>1){
               for ( int i=0;i<cands.size();i++){
                  Model::getInstance()->setCandidateValue(cands[i],pair.first);
               }
            }
      
         } 
      }
      //CHANGE PENCIL MARKINGS INTO PEN-MARKINGS
      pencilToPenMarking();
    
}


void Solver::patternRecognition(std::map<int,std::map<int,int>>blocks){

//loop through each block

for(int i=0;i<9;i++){
  // for( const auto& block:blocks[i]){
      //find a  completed segment ( row segment/col segment)
      //row completed segment

      //first row of the block
      auto firstPosition =blocks[i].begin()->first; 
      if(blocks[i][firstPosition]!=0 &&blocks[i][firstPosition+1]!=0 && blocks[i][firstPosition+2]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition]<<", "<<blocks[i][firstPosition+1]<<", "<<blocks[i][firstPosition+2]<<"]"<<std::endl;

      }

      if(blocks[i][firstPosition+9]!=0 &&blocks[i][firstPosition+10]!=0 && blocks[i][firstPosition+11]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition+9]<<", "<<blocks[i][firstPosition+10]<<", "<<blocks[i][firstPosition+11]<<"]"<<std::endl;

      }
       if(blocks[i][firstPosition+18]!=0 &&blocks[i][firstPosition+19]!=0 && blocks[i][firstPosition+20]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition+18]<<", "<<blocks[i][firstPosition+19]<<", "<<blocks[i][firstPosition+20]<<"]"<<std::endl;

      }

      //column segment

      if(blocks[i][firstPosition]!=0 &&blocks[i+9][firstPosition+9]!=0 && blocks[i+18][firstPosition+18]!=0 ){
         std::cout<<"Found a col segment: ["<<blocks[i][firstPosition]<<", "<<blocks[i][firstPosition+9]<<", "<<blocks[i][firstPosition+18]<<"]"<<std::endl;

      }

      if(blocks[i][firstPosition+1]!=0 &&blocks[i][firstPosition+10]!=0 && blocks[i][firstPosition+19]!=0 ){
         std::cout<<"Found a col segment: ["<<blocks[i][firstPosition+1]<<", "<<blocks[i][firstPosition+10]<<", "<<blocks[i][firstPosition+19]<<"]"<<std::endl;

      }
       if(blocks[i][firstPosition+2]!=0 &&blocks[i][firstPosition+11]!=0 && blocks[i][firstPosition+20]!=0 ){
         std::cout<<"Found a  col segment: ["<<blocks[i][firstPosition+2]<<", "<<blocks[i][firstPosition+11]<<", "<<blocks[i][firstPosition+20]<<"]"<<std::endl;

      }

      

  }

std::cout<<"The end!\n";

//look for a value in the stack/rank not in the completed segment , not the same block as the completed segment, not in the same row/col as the completed segment
//fill in ghost numbers in the row/col that is neither same as the completed segement or the value
//identify the three candidate positons in the block not the same as completed segment or the value and the same row/col as the segment
//check and fill candidates in this positions
//run pentoPencil function

// after doing it for all blocks -run check repetition function
}

