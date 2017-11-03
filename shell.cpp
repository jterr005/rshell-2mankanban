#include <iostream>
#include "shell.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
        this->success = false;
}

//bool Shell::evaluator() {}

void Shell::insert(Shell*) {
	if(parent == NULL) {
		
