#include <gtest/gtest.h>

#include <iostream> 
#include <clocale> 

using namespace std;

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

	
	fflush(stdin); 
	cin.get();
}