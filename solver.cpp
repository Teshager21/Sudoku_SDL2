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
  generateBlocks();
}

void Solver::setBlocksElement(std::map<int,int>mp,int el){
 mblocks[el]=mp;
}

void Solver::generateBlocks(){
   int position,row,col,blockNum,value;
   //b=blockNum:{position:value}
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
   //assign b to mblocks

   std::cout<<"blocks successfully generated"<<std::endl;
   //PENCIL MARKING CANDIDATES
   checkRepeatition(b);
   //pencilToPenMarking();
    std::cout<<"Repetiton successfully checked-round one"<<std::endl;
   //PATTERN RECOGNITION USING GHOST/PHANTOM NUMBERS
   patternRecognition(b);
   //pencilToPenMarking();
   checkRepeatition(b);
   //fillAllPossibleCandidateValues();

}
   
//Looks across stacks and ranks and calculates pen-marked and pencilmarked values for values that are repeated twice across a rank or a stack
void Solver::checkRepeatition(std::map<int,std::map<int,int>>blocks){
   checkRepeatitionAcrossBlocks(blocks,"Rank",0);
  
   std::cout<<"Repitition across the first rank checked"<<std::endl;
   checkRepeatitionAcrossBlocks(blocks,"Rank",1);
   std::cout<<"Repitition across the second rank checked"<<std::endl;
   checkRepeatitionAcrossBlocks(blocks,"Rank",2);
   std::cout<<"Repitition across the third rank checked"<<std::endl;
   checkRepeatitionAcrossBlocks(blocks,"Stack",0);
   std::cout<<"Repitition across the first stack"<<std::endl;

   checkRepeatitionAcrossBlocks(blocks,"Stack",1);
   std::cout<<"Repitition across the second stack"<<std::endl;
   checkRepeatitionAcrossBlocks(blocks,"Stack",2);
}
  
//calculates values that are repeated twice in a stack or a rank along with their position
void Solver::checkRepeatitionAcrossBlocks(std::map<int,std::map<int,int>>blocks,std::string scope, int scopeSpecifier){
std::map<int,int>repeats; //position:freq
std::map<int, std::map<int,std::vector<int>>>existingValues; //value:value: {positions}
//RANKS
if (scope=="Rank"){
   //populate repeats and existing values
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
      std::cout<<"Existing Values successfully generated"<<std::endl;
      
        std::cout<<"Existing Values successfully Logged"<<std::endl;
         logMapofMapsV(existingValues);
 //remove elements that are repeated twice
 std::map<int, std::map<int,std::vector<int>>>existingValues2; //value:value: {positions}
      for(const auto& pair:existingValues){
         if(repeats[pair.first]==2){
         existingValues2[pair.first]=existingValues[pair.first];
         }
      }
  std::cout<<"Double Repetition in existingvalues successfully erased!"<<std::endl;
      figureSpecificPosition(existingValues2);
      std::cout<<std::endl<<"========================================================================================================\n";
    std::cout<<std::endl<<"Successfully figured specific positions for rank: "<<scopeSpecifier<<"\n";

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

      // std::cout<<std::endl<<"Repeats\n";
      // logMap(repeats);

      std::cout<<std::endl<<"ExistingValues: Before\n";
      logMapofMapsV(existingValues);
 //remove elements that are repeated twice
      for(const auto& pair:existingValues){
         if(repeats[pair.first]==2){}
         else{
            existingValues.erase(pair.first);  
         }
      }
      figureSpecificPositionS(existingValues);

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
      std::cout << pair.first<<"["<<pair.second<<"], "<<std::endl;
    }
}

void Solver::logMapofMapsV(std::map<int,std::map<int,std::vector<int>>>b){
  for (auto& map : b) {
    for (auto& pair : map.second) {
      if(pair.second.size()>1)
       std::cout << pair.first<<"[" << (pair.second).at(0)<<"," << (pair.second).at(1)<<"], "<<std::endl;
    }
  } 

}
void Solver::logMapofMaps(std::map<int,std::map<int,int>>b){
  for (auto& map : b) {
    for (auto& pair : map.second) {
      std::cout << pair.first<<"[" << (pair.second)<<"], "<<std::endl;
    }
  } 

}

int Solver::Block(int position){
   return (position / 27)*3+ (position % 9)/3;
}
//take the repeated values and fill candidates based on them
void Solver::figureSpecificPosition(std::map<int, std::map<int,std::vector<int>>>existingValues){ //existing values: value: {pos1,pos2}
  
   int row,block;
   
      for(const auto& mp:existingValues){
         for(const auto& pair:mp.second){
            //std::cout<<pair.first<<"["<<pair.second[0]<<","<<pair.second[1]<<"], ";
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
            std::cout<<"Row for the candidates calculated: "<<row<<std::endl;
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

            std::cout<<"successfuly identified block : "<<block<<std::endl;
            //three potential columns
            int col0= block%3*3;
            int col1= col0+1;
            int col2=col1+1;
            int pos0 = row*9+col0;
            int pos1= row*9 +col1;
            int pos2= row*9 +col2;
            std::cout<<"Indentified the three columns"<<col0<<", "<<col1<<", "<<col2<<std::endl;
            std::cout<<"Indentified the three positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

            //narrow down to empty positions
            std::vector<int> cands {0,0,0};
            if(!Model::getInstance()->isPositionFilled(pos0))
               cands[0]=(pos0);
            if(!Model::getInstance()->isPositionFilled(pos1))
               cands[1]=(pos1);
            if(!Model::getInstance()->isPositionFilled(pos2))
               cands[2]=(pos2);
            std::cout<<"Exclude none zero positions: "<<cands[0]<<", "<<cands[1]<<", "<<cands[2]<<std::endl;
            //check which of the empty positions are viable and fill them
      
               for ( int i=0;i<cands.size();i++){
                  std::cout<<"candidate: "<<i<<" Position: "<<cands[i]<<std::endl;
                  if(cands[i]!=0){
                      std::cout<<"Candidate: "<<i<<" to fill: "<<pair.first<<" @ "<<cands[i]<<std::endl;
                      Model::getInstance()->setCandidateValue(cands[i],pair.first);
                      std::cout<<"Candidate: "<<i<<" successfully filled: "<<pair.first<<" @ "<<cands[i]<<std::endl;
                  }
                   
               }
            std::cout<<"Candidates successfully populated!"<<std::endl;
      
         } 
      }
      //CHANGE PENCIL MARKINGS INTO PEN-MARKINGS
      pencilToPenMarking();

}
 //CHANGE PENCIL MARKINGS INTO PEN-MARKINGS
void Solver::pencilToPenMarking(){
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

      // std::cout<<"List of cands with frequency"<<std::endl;
      for(const auto& pair:candpos){
         if(pair.second==1){
         
            for(const auto& cand:*CandidatePositions){
               if(std::find(cand.second.begin(), cand.second.end(), pair.first) != cand.second.end()){
               
                  for(int i=0;i<9;i++){
                     if(Block(cand.first)==i){
                        // std::cout<<pair.first<<"["<<pair.second<<"]@"<<cand.first<<", ";
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
            // std::cout<<pair.first<<"["<<pair.second[0]<<","<<pair.second[1]<<"], ";
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
            // std::cout<<"select col is "<<col<<" select block is: "<<block<<std::endl;
            //three potential rows
            int row0= (block/3)*3;
            int row1= row0+1;
            int row2= row1+1;
            int pos0= row0*9 +col;
            int pos1= row1*9 +col;
            int pos2= row2*9 +col;
            // std::cout<<"list of rows "<<row0<<", "<<row1<<", "<<row2<<std::endl;
            // std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

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
               // std::cout<<"certain fill: "<<cands[0]<<" @ "<<pair.first<<std::endl;
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
for(int i=0;i<9;i++){ //loop through each block
      //find a  completed segment ( row segment/col segment)
      //row completed segment
      std::vector<int>pos;
      auto firstPosition =blocks[i].begin()->first; 
      if(blocks[i][firstPosition]!=0 &&blocks[i][firstPosition+1]!=0 && blocks[i][firstPosition+2]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition]<<", "<<blocks[i][firstPosition+1]<<", "<<blocks[i][firstPosition+2]<<"]"<<std::endl;
         pos=valuesForPatternRecognition(i,blocks[i].begin()->first);
         candidatesFromValues(pos,firstPosition,i);

         std::cout<<"List of positions identified for first row of block-"<<i<<" are: ";
         for(int i=0;i<pos.size();i++){
            std::cout<<pos[i]<<", ";
         }
         std::cout<<std::endl;

         //figure out the row for the candidates for each pos above
         //fill in if position is empty
      }

      if(blocks[i][firstPosition+9]!=0 &&blocks[i][firstPosition+10]!=0 && blocks[i][firstPosition+11]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition+9]<<", "<<blocks[i][firstPosition+10]<<", "<<blocks[i][firstPosition+11]<<"]"<<std::endl;
         pos = valuesForPatternRecognition(i,blocks[i].begin()->first+9);
         candidatesFromValues(pos,firstPosition,i);

         std::cout<<"List of positions identified for second row of block-"<<i<<" are: ";
         for(int i=0;i<pos.size();i++){
            std::cout<<pos[i]<<", ";
         }
         std::cout<<std::endl;
         
      }
       if(blocks[i][firstPosition+18]!=0 &&blocks[i][firstPosition+19]!=0 && blocks[i][firstPosition+20]!=0 ){
         std::cout<<"Found a segment: ["<<blocks[i][firstPosition+18]<<", "<<blocks[i][firstPosition+19]<<", "<<blocks[i][firstPosition+20]<<"]"<<std::endl;
         pos=valuesForPatternRecognition(i,blocks[i].begin()->first+18);
         candidatesFromValues(pos,firstPosition,i);

          std::cout<<"List of positions identified for third row of block-"<<i<<" are: ";
         for(int i=0;i<pos.size();i++){
            std::cout<<pos[i]<<", ";
         }
         std::cout<<std::endl;
      }

      //column completed segment

      if(blocks[i][firstPosition]!=0 &&blocks[i+9][firstPosition+9]!=0 && blocks[i+18][firstPosition+18]!=0 ){
         std::cout<<"Found a col segment: ["<<blocks[i][firstPosition]<<", "<<blocks[i][firstPosition+9]<<", "<<blocks[i][firstPosition+18]<<"]"<<std::endl;
         pos=valuesForPatternRecognitionC(i,blocks[i].begin()->first);
         candidatesFromValuesC(pos,firstPosition,i);
      }

      if(blocks[i][firstPosition+1]!=0 &&blocks[i][firstPosition+10]!=0 && blocks[i][firstPosition+19]!=0 ){
         std::cout<<"Found a col segment: ["<<blocks[i][firstPosition+1]<<", "<<blocks[i][firstPosition+10]<<", "<<blocks[i][firstPosition+19]<<"]"<<std::endl;
         pos=valuesForPatternRecognitionC(i,blocks[i].begin()->first+1);
         candidatesFromValuesC(pos,firstPosition,i);
      }
       if(blocks[i][firstPosition+2]!=0 &&blocks[i][firstPosition+11]!=0 && blocks[i][firstPosition+20]!=0 ){
          std::cout<<"Found a  col segment: ["<<blocks[i][firstPosition+2]<<", "<<blocks[i][firstPosition+11]<<", "<<blocks[i][firstPosition+20]<<"]"<<std::endl;
          pos=valuesForPatternRecognitionC(i,blocks[i].begin()->first+2);
          candidatesFromValuesC(pos,firstPosition,i);
      } 
  }
  std::cout<<"Pattern recognition successfully run!"<<std::endl;
}
//Identify values that will be used with the completed segment
std::vector<int> Solver::valuesForPatternRecognition(int blockNum,int firstPosition){//blockNUm=block containing segment
    //look for a value in the stack/rank not in the completed segment , not the same block as the completed segment, not in the same row/col as the completed segment
      //the two possible blocks
      int firstCell=firstPosition;
      int blocknum1,blocknum2,row1,row2;
      if(blockNum%3==0){
         blocknum1=blockNum+1;
         blocknum2=blockNum+2;
      }
      if(blockNum%3==1){
         blocknum1=blockNum-1;
         blocknum2=blockNum+1;
      }
       if(blockNum%3==2){
         blocknum1=blockNum-1;
         blocknum2=blockNum-2;
      }
      // std::cout<<"Pattern Recognition: the two blocks are: "<< blocknum1<<", "<<blocknum2<<std::endl;
      //the two possible rows
      if((firstCell/9)%3==0){//segment is in the fist row of a rank
        row1= (firstCell/9)+1;
        row2= (firstCell/9)+2;
      }
      if((firstCell/9)%3==1){//segment is in the 2nd row of a rank
        row1= (firstCell/9)-1;
        row2= (firstCell/9)+1;
      }
      if((firstCell/9)%3==2){//segment is in the 3rd row of a rank
        row1= (firstCell/9)-1;
        row2= (firstCell/9)-2;
      }

      // std::cout<<"Pattern recognition: rows"<<row1<<", "<<row2<<std::endl;

      //12 POSSIBLE POSITIONS FOR THE VALUE
      std::vector<int>pos;
      for(int i=0;i<3;i++){
         if((Model::getInstance()->isPositionFilled(9*row1+i+3*(blocknum1%3))) && find(pos.begin(),pos.end(),9*row1+i+3*(blocknum1%3))==pos.end())
            pos.push_back(9*row1+i+3*(blocknum1%3));
         if(Model::getInstance()->isPositionFilled(9*row2+i+3*(blocknum1%3))&&find(pos.begin(),pos.end(),9*row2+i+3*(blocknum1%3))==pos.end()) 
            pos.push_back(9*row2+i+3*(blocknum1%3));

      
         if(Model::getInstance()->isPositionFilled(9*row1+i+3*(blocknum2%3)))
            pos.push_back(9*row1+i+3*(blocknum2%3));
         if(Model::getInstance()->isPositionFilled(9*row2+i+3*(blocknum2%3))) 
            pos.push_back(9*row2+i+3*(blocknum2%3));
      }

      //Exclude these values that are shared by the completed segment

      for(int i=0;i<pos.size();i++){
         if(pos[i]==firstPosition || pos[i]==(firstPosition+1) || pos[i]==(firstPosition+2)){
            pos.erase(pos.begin() + i);
         }
      }
      //print out the values
      // std::cout<<"The potential values for PR are: "<<std::endl;
      for(auto& item:pos){
         // std::cout<<item<<std::endl;
      }
      return pos;
      }
//find candidate positions from values of Pattern Recognition
void Solver::candidatesFromValues(std::vector<int>pos, int firstPosition, int blockNum){
      //figure out the row for candidates
      for(int i=0;i<pos.size();i++){
         int rowSegment= firstPosition/9;
         int rowValue= pos[i]/9;
         int rowCandidates;
         if(abs(rowSegment-rowValue)==2){
               rowCandidates=(rowSegment+rowValue)/2;
         }else{
            if(rowSegment>rowValue){
               if(rowValue%3==0){
                  rowCandidates=rowSegment+1;
               }else{
                  rowCandidates=rowValue-1;
               }
            }else{
               if(rowSegment%3==0){
                  rowCandidates=rowValue+1;
               }else{
                  rowCandidates=rowSegment-1;
               }

            }

         }
         //block of the candidates
         int block= thirdBlockOfRank(Block(pos[i]),blockNum);
          std::cout<<"The candidate row for "<<pos[i]<<" is: "<<rowCandidates<<" @block"<<block<<" for a value position of: "<<firstPosition<<std::endl;
         //The three potential candidate positons
         int value=Model::getInstance()->getValueAtPosition(pos[i]);
         // std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
         std::vector<int>cands=candidatesFromBlockandRow(block,rowCandidates,value);
         // std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
      }  
}

void Solver::candidatesFromValuesC(std::vector<int>pos, int firstPosition, int blockNum){
      //figure out the col for candidates
      for(int i=0;i<pos.size();i++){
         int colSegment= firstPosition%9;
         int colValue= pos[i]%9;
         int colCandidates;
         if(abs(colSegment-colValue)==2){
               colCandidates=(colSegment+colValue)/2;
         }else{
            if(colSegment>colValue){
               if(colValue%3==0){
                  colCandidates=colSegment+1;
               }else{
                  colCandidates=colValue-1;
               }
            }else{
               if(colSegment%3==0){
                  colCandidates=colValue+1;
               }else{
                  colCandidates=colSegment-1;
               }

            }

         }
         //block of the candidates
         int block= thirdBlockOfRank(Block(pos[i]),blockNum);
          std::cout<<"The candidate col for "<<pos[i]<<" is: "<<colCandidates<<" @block"<<block<<" for a value position of: "<<firstPosition<<std::endl;
         //The three potential candidate positons
         int value=Model::getInstance()->getValueAtPosition(pos[i]);
         // std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
         std::vector<int>cands=candidatesFromBlockandCol(block,colCandidates,value);
         // std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
      }  
}

std::vector<int> Solver::valuesForPatternRecognitionC(int blockNum,int firstPosition){
    //look for a value in the stack/rank not in the completed segment , not the same block as the completed segment, not in the same row/col as the completed segment
      //the two possible blocks
      int firstCell=firstPosition;
      int blocknum1,blocknum2,col1,col2;
      if(blockNum/3==0){
         blocknum1=blockNum+3;
         blocknum2=blockNum+6;
      }
      if(blockNum/3==1){
         blocknum1=blockNum-3;
         blocknum2=blockNum+3;
      }
       if(blockNum/3==2){
         blocknum1=blockNum-3;
         blocknum2=blockNum-6;
      }
      // std::cout<<"Col Pattern Recognition: the two blocks are: "<< blocknum1<<", "<<blocknum2<<std::endl;
      //the two possible columns
      if((firstCell%9)%3==0){//segment is in the fist col of a rank
        col1= (firstCell%9)+1;
        col2= (firstCell%9)+2;
      }
      if((firstCell%9)%3==1){//segment is in the 2nd col of a rank
        col1= (firstCell%9)-1;
        col2= (firstCell%9)+1;
      }
      if((firstCell%9)%3==2){//segment is in the 3rd colof a rank
        col1= (firstCell%9)-1;
        col2= (firstCell%9)-2;
      }

      // std::cout<<"Pattern recognition: cols"<<col1<<", "<<col2<<std::endl;

      //12 POSSIBLE POSITIONS FOR THE VALUE
      std::vector<int>pos;
      for(int i=0;i<3;i++){
         //int post= 9*((blocknum1%3)*3+i)+col1
         if((Model::getInstance()->isPositionFilled(27*(blocknum1/3)+col1+9*i)) && find(pos.begin(),pos.end(),27*(blocknum1/3)+col1+9*i)==pos.end())
            pos.push_back(27*(blocknum1/3)+col1+9*i);
         if((Model::getInstance()->isPositionFilled(27*(blocknum1/3)+col2+9*i)) &&find(pos.begin(),pos.end(),27*(blocknum1/3)+col2+9*i)==pos.end()) 
            pos.push_back(27*(blocknum1/3)+col2+9*i);

      
         if(Model::getInstance()->isPositionFilled(27*(blocknum2/3)+col1+9*i)&& find(pos.begin(),pos.end(),27*(blocknum2/3)+col1+9*i)==pos.end())
            pos.push_back(27*(blocknum2/3)+col1+9*i);
         if(Model::getInstance()->isPositionFilled(27*(blocknum2/3)+col2+9*i)&& find(pos.begin(),pos.end(),27*(blocknum2/3)+col2+9*i)==pos.end()) 
            pos.push_back(27*(blocknum2/3)+col2+9*i);
      }

      //Exclude those values that are shared by the completed segment
      for(int i=0;i<pos.size();i++){
         if(pos[i]==firstPosition || pos[i]==(firstPosition+1) || pos[i]==(firstPosition+2)){
            pos.erase(pos.begin() + i);
         }
      }
      //print out the values
      // std::cout<<"The potential values for PR(column) are: "<<std::endl;
      for(auto& item:pos){
         std::cout<<item<<std::endl;
      }

       //figure out the col for candidates
       for(int i=0;i<pos.size();i++){
         int colSegment= firstPosition%9;
         int colValue= pos[i]%9;
         int colCandidates;
         if(abs(colSegment-colValue)==2){
               colCandidates=(colSegment+colValue)/2;
         }else{
            if(colSegment>colValue){
               if(colValue%3==0){
                  colCandidates=colSegment+1;
               }else{
                  colCandidates=colValue-1;
               }
            }else{
               if(colSegment%3==0){
                  colCandidates=colValue+1;
               }else{
                  colCandidates=colSegment-1;
               }

            }

         }
         //block of the candidates
         int block= thirdBlockOfRank(Block(pos[i]),blockNum);
         std::cout<<"The candidate col for "<<pos[i]<<" is: "<<colCandidates<<" @block"<<block<<std::endl;
         //The three potential candidate positons
         int value=Model::getInstance()->getValueAtPosition(pos[i]);
         // std::cout<<"********************************************************************"<<std::endl;
         std::vector<int>cands=candidatesFromBlockandCol(block,colCandidates,value);
         // std::cout<<"********************************************************************"<<std::endl;
       }

      

      return pos;
      }
//calculate candidates from a given block and row
std::vector<int> Solver::candidatesFromBlockandRow(int block,int row,int value){
   //three potential columns
      int col0= block%3*3;
      int col1= col0+1;
      int col2=col1+1;
      int pos0 = row*9+col0;
      int pos1= row*9 +col1;
      int pos2= row*9 +col2;
      // std::cout<<"list of columns "<<col0<<", "<<col1<<", "<<col2<<std::endl;
      // std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;

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
         Model::getInstance()->receiveInput(cands[0],value);
         // std::cout<<"certain candidate (PR) fill: "<<cands[0]<<" @ "<<value<<std::endl;
      }
      if (cands.size()>1){
         for ( int i=0;i<cands.size();i++){
            Model::getInstance()->setCandidateValue(cands[i],value);
            // std::cout<<"successfully filled candidate value: "<<value<<" @ "<<cands[i]<<std::endl;
         }
      }
      return cands;
}

//figures out the # of third block of a rank given the # of two of the block in rank
int Solver::thirdBlockOfRank(int block0, int block1){
   int blockMin,block;
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
 return block;
}
//figure out the third column of a segment
int Solver::thirdColumnOfSegment(std::vector<int>pos, int firstPosition){
    int colCandidates;
   for(int i=0;i<pos.size();i++){
      int colSegment= firstPosition%9;
      int colValue= pos[i]%9;
   
      if(abs(colSegment-colValue)==2){
            colCandidates=(colSegment+colValue)/2;
      }else{
         if(colSegment>colValue){
            if(colValue%3==0){
               colCandidates=colSegment+1;
            }else{
               colCandidates=colValue-1;
            }
         }else{
            if(colSegment%3==0){
               colCandidates=colValue+1;
            }else{
               colCandidates=colSegment-1;
            }

         }

      }  
   }
return colCandidates;
}
//calculate candidates from a given block and column
std::vector<int> Solver::candidatesFromBlockandCol(int block,int col,int value){
   //three potential rows
      int row0= (block/3)*3;
      // int row1= row0+1;
      // int row2=row1+1;
   //three potential cells
      int pos0= row0*9+col;
      int pos1= pos0+9;
      int pos2= pos1+9;
      // std::cout<<"list of rows "<<row0<<", "<<row0+1<<", "<<row0+2<<std::endl;
      // std::cout<<"list of positions "<<pos0<<", "<<pos1<<", "<<pos2<<std::endl;
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
         Model::getInstance()->receiveInput(cands[0],value);
         // std::cout<<"certain candidate (PR) fill: "<<cands[0]<<" @ "<<value<<std::endl;
      }
      if (cands.size()>1){
         for ( int i=0;i<cands.size();i++){
            Model::getInstance()->setCandidateValue(cands[i],value);
            // std::cout<<"successfully filled candidate value: "<<value<<" @ "<<cands[i]<<std::endl;
         }
      }
      return cands;
}

//fills all the possible candidate values
void Solver:: fillAllPossibleCandidateValues(){
// std::cout<<"Filling possible candidates......"<<std::endl;
for(int pos=0;pos<81;pos++){
   for( int value=1;value<=9;value++){
        Model::getInstance()->setCandidateValue(pos,value);    
   }
  
}

}
//capitalize on mathcing pairs
void Solver::MatchingPairs(){
//identify matching pair
//loop through cands of all positions
//check if the count of candidates at a position are 2
//store them in another map
//loop through the map and check if there are matching pairs
//store the matching pairs in a new map
//log them

}
//capitalize on naked singles
void Solver::NakedSingles(){
//loop through cand values and count the values
   for(int pos=0;pos<81;pos++){
      for( int value=1;value<=9;value++){
         std::vector<int> values=Model::getInstance()->getCandidatesAtPosition(pos);
         if(values.size()==9){
            int counter=0;
            int v;
            for(int i=0;i<9;i++){
               
               if(values[i]>0){
                  counter=counter+1;
                  v=values[i];
               }
            }
            if(counter==1){
               std::cout<<"Found a naked single "<<v<<" @ "<<pos<<std::endl;
               Model::getInstance()->setCandidateVector(pos,{0,0,0,0,0,0,0,0,0});
               Model::getInstance()->receiveInput(pos,v);
               //remove the value from other candidates of the unit(block,row/col)
               //remove the value from the candidates of the row
               int nakedRow= pos/9;
               singleOutCandidateValue("row",nakedRow,pos,v);
               //remove the value from the candidates of the row
               int nakedCol= pos%9;
               singleOutCandidateValue("col",nakedCol,pos,v);
               //remove the value from the candidates of the block
               int nakedBlock = (pos /9)+ (pos % 9)/3;
               singleOutCandidateValue("block",nakedBlock,pos,v);
            }  
         }
            
      }
   
   }

}
//deletes all similar candidate values in a unit
void Solver::singleOutCandidateValue(std::string scope,int scopeSpecifier,int position,int value){
//loop through all candidate values
for(int pos=0;pos<81;pos++){
   for( int val=1;val<=9;val++){
//check if its in the same unit
std::vector<int> cVec;
   cVec=Model::getInstance()->getCandidatesAtPosition(pos);
//row  
   if(scope=="row" &&!Model::getInstance()->isPositionFilled(pos) && pos/9==scopeSpecifier && pos!=position && val==value && cVec[val-1]!=0){
      std::cout<<"Found a pair to naked value: "<<val<<" in the row:"<<scopeSpecifier<<" postion: "<<pos<<std::endl;
      cVec[val-1]=0;
      Model::getInstance()->setCandidateVector(pos,cVec);
   }
//col
if(scope=="col" &&!Model::getInstance()->isPositionFilled(pos) && pos%9==scopeSpecifier && pos!=position && val==value && cVec[val-1]!=0){
      std::cout<<"Found a pair to naked value: "<<val<<" in the col:"<<scopeSpecifier<<" postion: "<<pos<<std::endl;
      cVec[val-1]=0;
      Model::getInstance()->setCandidateVector(pos,cVec);

   }
//block
if(scope=="block" &&!Model::getInstance()->isPositionFilled(pos) && (pos /9)+ (pos % 9)/3==scopeSpecifier && pos!=position && val==value && cVec[val-1]!=0){
      std::cout<<"Found a pair to naked value: "<<val<<" in block:"<<scopeSpecifier<<" postion: "<<pos<<std::endl;
      cVec[val-1]=0;
      Model::getInstance()->setCandidateVector(pos,cVec);

   }
}
}
}