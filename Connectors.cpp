#include <iostream>
#include "Connectors.h"

using namespace std;

Connectors::Connectors(string input){
	if(input == "&"){
		this->cntr = "&&"
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
		this->prompt = "$";
		this->Qsuccess = false;
