#include <iostream>
#include "Test.h"

using namespace std;

Test::Test(string input){
	this->test = input;
}
string Test::type(){
	return this->test;
}
void Test::execute(string cmd){
	//Removes brackets from cmd
	cmd.erase(std::remove(cmd.begin(), cmd.end(), '['), cmd.end());
	cmd.erase(std::remove(cmd.begin(), cmd.end(), ']'), cmd.end());
	
	//Removes whitespace from cmd and parses cmd into vector
	vector<string> strvctr;
	boost::split(strvctr, cmd, boost::is_any_of(" "));
	
	cout << strvctr.at(0) << " testing space " << strvctr.at(1) << endl;
}
