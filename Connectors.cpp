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
		cout << "this is not a connector" << endl;
	}
		
}

string Connectors::type(){
	return cntr;
}

void Connectors::execute(string cntr) {}

