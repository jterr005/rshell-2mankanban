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
	
	++mainCounter;
	struct stat scan;
	if(strvctr.at(0) == "-e") {
		if(stat(strvctr.at(1).c_str(), &scan) == 0) {
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
	if(strvctr.at(0) == "-f") {
		if(stat(strvctr.at(1).c_str(), &scan) == 0 && S_ISREG(scan.st_mode)) {
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
	if(strvctr.at(0) == "-d") {
		if(stat(strvctr.at(1).c_str(), &scan) == 0 && S_ISDIR(scan.st_mode)) {
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
	else {
		if(stat(strvctr.at(1).c_str(), &scan) == 0) { 
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
}
