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
	
	for(unsigned j = 0; j < strvctr.size(); ++j) {
		if(strvctr.at(j).find("#") != string::npos) {
			//cout << "Removing: " << strvctr.at(j) << endl;
			size = j;
			j = 5000;
			break;
		}
	}
	
	//cout << "SIZE: " <<  size << endl;
	while (size > 0 ) {
		//cout << "PROCESSING " << strvctr.at(i) << endl;
		argmts[i] = (char*)strvctr.at(i).c_str();
		++i;
		--size;
	}
	argmts[i] = NULL;

	
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
