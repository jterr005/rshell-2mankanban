#include <iostream>
#include <string>
#include "Connectors.h"
#include "Executables.h"

using namespace std;

Connectors::Connectors(string input){
	if(input == "&"){
		this->cntr = "&&";
	}
	else if(input == "|"){
		this->cntr = "||";
	}
	else if(input == ";"){
		this->cntr = ";";
	}
	else{
		cout << "test node created" << endl;
		this->cntr = "test";
	}
		
}

string Connectors::type(){
	return cntr;
}

void Connectors::execute(string cntr) {
	if(cntr == "|") {
		
}

