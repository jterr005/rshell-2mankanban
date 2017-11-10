#include <iostream>
#include <string>
#include "Executables.h"

using namespace std;

Executables::Executables(string input){
	this->argmnt = input;
}

string Executables::type(){
	return argmnt;
}

void Executables::execute(string cmd) {
	char* argmts[2];

	argmts[0] = (char*)cmd.c_str();
	argmts[1] = NULL;
	
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
	}
}
