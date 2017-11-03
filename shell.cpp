#include <iostream>
#include <string>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
        this->success = false;
}

//bool Shell::evaluator() {}


void Shell::insert( Shell* Node) {
	cout << " entered insert function";
	string type = Node->type();
	 if(type == "&" || type  == "|" || type == ";"){
		cout << " connector statement";
	}
	else{
		cout << " arg statement";
	}
	
}

/*
void Shell::displayAssist(Shell* curr) {
        if(curr) {
                displayAssist(curr->left);
	 //POSSIBLE ERROR FROM COUT                
 		cout << type(curr) << endl;               
                 displayAssist(curr->right);
	                                                                                                       return;
}*/		
