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
	cout << "This is the cmd for test: " << endl;	
	
	cmd.erase(std::remove(cmd.begin(), cmd.end(), '['), cmd.end());
	cmd.erase(std::remove(cmd.begin(), cmd.end(), ']'), cmd.end());
	
	//Removes whitespace from cmd and parses cmd into vector
	vector<string> strvctr;
	boost::split(strvctr, cmd, boost::is_any_of(" "));
	
	if(mainCounter > 1) {
		if( cmd.find("test") != string::npos) {
			cout << strvctr.at(0) << endl;
			strvctr.erase(strvctr.begin());
			cout << strvctr.at(0) << endl;
			strvctr.erase(strvctr.begin());
			cout << strvctr.at(0) << endl;
			
		}
	}
	else if (mainCounter == 1 &&  cmd.find("test") != string::npos) {
		cout << "strvctr.at(0) is " << strvctr.at(0) << endl;
		strvctr.erase(strvctr.begin());
		cout << "strvctr.at(0) is " << strvctr.at(0) << " after deleting first vector" << endl;
	}
	 	
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
		cout << "STRING AT AT(1)" << strvctr.at(0) << endl;
		if(stat(strvctr.at(0).c_str(), &scan) == 0) { 
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
