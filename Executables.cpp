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

	if(execvp(argmts[0], argmts) == -1) {
		cout << "Process failed" << endl;
	}
	else {
		cout << "Process successful" << endl;
	}
}
