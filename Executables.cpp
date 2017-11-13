#include <iostream>
#include <string>
#include <sstream>
#include "Executables.h"
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

Executables::Executables(string input){
	this->argmnt = input;
}

string Executables::type(){
	return argmnt;
}

void Executables::execute(string cmd) {
	cout << "Start of execute function: " <<  cmd << endl;
	stringstream ss;
	string tmp;
	ss << cmd;
	int size = 0;

	while (ss >> tmp ) {
		++size;
	}
	
	cmd = ss.str();	
	cout << "this is after reassigning: " << cmd << endl;
	int i = 0;
	
	vector<string> strvctr;
	boost::split(strvctr, argmnt, boost::is_any_of(" "));
	cout << "This is what is in vector after parsing " << strvctr.at(0) << endl;
	
	if(mainCounter > 1) {
		strvctr.erase(strvctr.begin());
		
	}
	
	char* argmts[size + 1];	
	
	
	while (size > 0 ) {
		cout << "PROCESSING " << strvctr.at(i) << endl;
		
		argmts[i] = (char*)strvctr.at(i).c_str();
		++i;
		--size;
	}
	argmts[i] = NULL;
	++mainCounter;
	
	pid_t pid = fork();
	if(pid == 0) { //CHILD PROCESS
		if(execvp(argmts[0], argmts) == -1) {
			cout << "Process failed" << endl;
			success = false;
		}
	}
	
	else if(pid != 0) { //PARENT PROCESS
		if(wait(0) == -1) {
			cout << "Process failed at wait(0)" << endl;
			success = false;
		}
	cout << "Process successful" << endl;

	success = true;
	}
}
