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
	stringstream ss;
	string tmp;
	ss << cmd;
	int size = 0;
	//cout << ss.str() << endl;

	while (ss >> tmp ) {
		++size;
	}
		
	int i = 0;
	char* argmts[size + 1];
	vector<string> strvctr;
	boost::split(strvctr, cmd, boost::is_any_of("\t "));
	while (size > 0 ) {
		//cout << "entered ss transfer of " << ww << endl;
		argmts[i] = (char*)strvctr.at(i).c_str();
		++i;
		--size;
	}
	argmts[i] = NULL;

	pid_t pid = fork();
	if(pid == 0) { //CHILD PROCESS
		if(execvp(argmts[0], argmts) == -1) {
			cout << "Process failed" << endl;
		}
	}
	
	else if(pid != 0) { //PARENT PROCESS
		if(wait(0) == -1) {
			cout << "Process failed at wait(0)" << endl;
		}
	cout << "Process successful" << endl;

	success = true;
	}
}
