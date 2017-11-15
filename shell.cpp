#include <iostream>
#include <string>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
        this->success = 1;
	this->parent = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

bool Shell::evaluator() {
	return this->success;
}


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
		Shell* temp = fExe;
		while(temp->parent != NULL){
		temp = temp->parent;
		}
		temp->rightChild = Node;
		Node->parent = temp;
		
	}
	
}

void Shell::display(Shell* fExe){
	Shell* temp = fExe;
	//cout << temp->type() << temp->parent->type() << temp->parent->rightChild->type();

	
	if(fExe->parent == NULL){
		Inorder(fExe);
	}
	else{
		Shell* temp = fExe;
		while(temp->parent != NULL){
			temp = temp->parent;
		}
		Inorder(temp);
	}
	

}
void Shell::Inorder(Shell* Node){
	if(Node != NULL){
		Inorder(Node->leftChild);
		cout << " " <<Node->type() << " ";
		Inorder(Node->rightChild);
	}
}

void Shell::run(Shell* fExe) {
	Shell* temp = fExe;
	
	if(fExe->parent == NULL) {
		cout << "RUNNING TREE FROM IF STATEMENT " << endl << endl;
		runInorder(fExe);
	}
	
	else{
		cout << "RUNNING TREE FROM IF STATEMENT " << endl << endl;
		while(temp->parent != NULL) {
			
			temp = temp->parent;
		}
		runInorder(temp);
	}
}


void Shell::runInorder(Shell* Node) {
	if(Node != NULL) {
		runInorder(Node->leftChild);
		cout << Node->type() <<  " EXECUTED IN RUNINORDER FUNCTION" << endl;   
		Node->execute(Node->type());
		//runInorder(Node->rightChild);		
	}
	return;
}	
