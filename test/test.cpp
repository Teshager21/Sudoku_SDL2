#include<iostream>
#include<gtest/gtest.h>

using namespace std;

TEST(TestName,SubTest_1){
    ASSERT_TRUE(1==2);
}

int main(int argc, char **argv){
//std::cout<<"Test run!";
testing::InitGoogleTest (&argc,argv);
return RUN_ALL_TESTS();
}
