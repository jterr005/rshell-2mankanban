#include <iostream>
#include "Executables.h"

using namespace std;

Executables::Executables(string input){
	this->argmnt = input;
}
String Executables::type(Shell* node){
	return node->argmnt;
}

