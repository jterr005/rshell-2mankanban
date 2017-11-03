#include <iostream>
#include "Connectors.h"

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
		cout << "this is now a connector" << endl;
	}
		this->leftChild = NULL;
		this->rightChild = NULL;
		
}
