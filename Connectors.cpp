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
	bool temp = false;
	
	if(this->cntr == "&&") {
		temp = this->leftChild->evaluator();
		if(temp == false) {
			this->success = false;
			return;
		}
		if(temp == true) {
			this->rightChild->execute(rightChild->type());
			temp = this->rightChild->evaluator();
			if(temp == false) {
				this->success = false;
				return;
			}
			else {
				this->success = true;
				return;
			}
		}
	}

	if(this->cntr == "||") {
		if(this->leftChild->evaluator() == true) {
			cout << "Left Child Successful" << endl;
			this->success = true;
			return;
		}
		else {
			this->rightChild->execute(this->rightChild->type());
			if(this->rightChild->evaluator() == false){
				this->success = false;
				return;
			}
			else{
				this->success = true;
				return;
			}
		}
	}
	
	if(this->cntr == ";") {
		this->rightChild->execute(this->rightChild->type());
		success = true;
		return;
	}
}

