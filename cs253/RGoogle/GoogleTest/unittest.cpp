// unittest.cpp : Defines the entry point for the console application.

#include "gtest/gtest.h"
#include "simplemath.h"
#include "palindrome.h"
#include "factorial.h"
TEST(unitTest, myCubeTest)
{
    EXPECT_EQ(100, cubic(10,20));	
}
TEST(unitTest,palindromeTest)
{
	char val[10];
    strcpy(val,"mam");
    EXPECT_TRUE(checkPalindrome(val));
}
TEST(unitTest,factorialTest)
{
    EXPECT_LT(101,factorial(10));
    EXPECT_GT(10,factorial(3));
}
TEST(unitTest,StringTest)
{
    EXPECT_STREQ("abc","abc");
}
TEST(unitTest,AddTest){
	EXPECT_EQ(14, plustorial(5));
}

int main(int argc, char **argv) {
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
    }
