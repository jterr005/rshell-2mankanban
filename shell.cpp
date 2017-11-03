#include <iostream>
#include <string>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
        this->success = false;
	this->parent = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

//bool Shell::evaluator() {}


void Shell::insert(Shell* fExe, Shell* Node){
	cout << " entered insert function";
	
	string type = Node->type();
	 if(type == "&&" || type  == "||" || type == ";"){
		cout << " connector statement";
		if(this->parent == NULL){
		cout << " IF ";
			this->parent = Node;
			Node->leftChild = fExe;
		}
		else{
			cout << " ELSE";
			Shell* temp = fExe;
			while(temp->parent != NULL){
			temp = temp->parent;
			}
			temp->parent = Node;
			Node->leftChild = temp;
		}

	}
	else{
		cout << " arg statement";
		this->rightChild = Node;
		Node->parent = fExe;
		
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
