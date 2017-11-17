#include <iostream>
#include "Test.h"

using namespace std;

Test::Test(string input){
	this->test = input;
}
string Test::type(){
	return this->test;
}
void Test::execute(string input){
}
