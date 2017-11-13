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



void Connectors::execute(string cntr) {
	if(this->cntr == "&&") {
		if(this->leftChild->evaluator() == true && this->rightChild->evaluator() == true) {
			this->success = true;
			return;
		}
		else {
			this->success = false;
			return;
		}
	}
	
	if(this->cntr == "||") {
		if(this->leftChild->evaluator() == true) {
			this->success = true;
			return;
		}
		else if(this->rightChild->evaluator() == true) {
			this->success = true;
			return;
		}
		else {
			this->success = false;
			return;
		}
	}
	
	if(this->cntr == ";") {
		success = true;
		return;
	}
}

