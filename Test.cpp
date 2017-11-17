#include <iostream>
#include "Test.h"

using namespace std;
Test::Test(string input){
	this->test = input;
}
Test::Type(){
	return this->test;
}

