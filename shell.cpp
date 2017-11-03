#include <iostream>
#include "shell.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
        this->success = false;
}

//bool Shell::evaluator() {}

void Shell::insert(Shell* root, Shell* Node) {
	if(type(Node) == "||" || type(Node) = "&&" || type(Node) = ";"){
		root->parent = Node;
		Node->leftChild = root;
	}
	else{
		root->rightChild = Node;
	}
}
void Shell::displayAssist(Shell* curr) {
        if(curr) {
                displayAssist(curr->left);
	 //POSSIBLE ERROR FROM COUT                
 		cout << type(curr) << endl;               
                 displayAssist(curr->right);
	                                                                                                       return;
}		
