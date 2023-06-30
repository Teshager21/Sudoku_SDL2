#include<iostream>
#include<gtest/gtest.h>
#include "../solver.h"
// #include "../controller.h"
//assert=fatal, expect not so, one assertion alone in a test
//unit test = arrange, act,assert
using namespace std;

//TESTING THE SOLVER CLASS
TEST(TestSuite,SubTest_1){
    ASSERT_FALSE(1==2);
}
//check if the model class intializes correclty
TEST(TestSuite,Block){
    //arrange
 Solver* s = Solver::getInstance();
  EXPECT_EQ(s->Block(0),0);
}
TEST(TestSuite,Block2){
    //arrange
 Solver* s = Solver::getInstance();
  EXPECT_EQ(s->Block(35),1);
}
TEST(TestSuite,Block3){
    //arrange
 Solver* s = Solver::getInstance();
  EXPECT_EQ(s->Block(35),5);
}

int main(int argc, char **argv){
//std::cout<<"Test run!";
testing::InitGoogleTest (&argc,argv);
return RUN_ALL_TESTS();
}
