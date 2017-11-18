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
	int status;

	while (ss >> tmp ) {
		++size;
	}
	
	cmd = ss.str();	
	//cout << "this is after reassigning: " << cmd << endl;
	int i = 0;
	
	vector<string> strvctr;
	boost::split(strvctr, argmnt, boost::is_any_of(" "));
	cout << "This is what is in vector after parsing " << strvctr.at(0) << endl;
		
	if(this->get_subTree()) {
		cout << "entered subTree TEST: " << endl;
		if(subTreeCounter > 1) {
			strvctr.erase(strvctr.begin());
		}
		++subTreeCounter;
	}

	else {
		if(mainCounter > 1) {
			strvctr.erase(strvctr.begin());
			cout << "This is what is in vecotr.at(0) after erasing " << strvctr.at(0) << endl;	
		}
		++mainCounter;		
	}
	
	char* argmts[size + 1];	
	
	
	while (size > 0 ) {
		cout << "PROCESSING " << strvctr.at(i) << endl;
		
		argmts[i] = (char*)strvctr.at(i).c_str();
		++i;
		--size;
	}
	argmts[i] = NULL;
	
	pid_t pid = fork();
	if(pid == 0) { //CHILD PROCESS
		execvp(argmts[0], argmts);
		perror("execvp failed: ");
		exit(-1);/*
		if((execvp(argmts[0], argmts)) == -1) {
			cout << "Process failed" << endl;
			cout << "CHILD PROCESS >> MAINCOUNTER IS: " << mainCounter << endl << endl;
			this->success = false;
			return;
		}*/
	}
	
	else if(pid > 0) { //PARENT PROCESS
		//pid_t check = wait(0);
		//cout << wait(0) << endl;
		if(waitpid(pid, &status, 0) == -1) {
			perror("Wait: ");
			this->success = false;
		}
		if(WEXITSTATUS(status) && WIFEXITED(status) != 0) {
			this->success = false;
		}
		else {
                	cout << "Process successful" << endl;
			cout << "PARENT PROCESS >> MAINCOUNTER IS: " << mainCounter << endl << endl;
                	this->success = true;
                	return;
        	}	
		return;
	}
	else if (pid < 0) {
		cout << "Something went VERY BAD" << endl;
		return;
	}
}
