#include <iostream>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"
#include "Test.h"

using namespace std;

Shell::Shell(){
        this->prompt = '$';
	this->newInput = "";
        this->success = 1;
	this->subTree = false;
	this->parent = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

bool Shell::evaluator() {
	return this->success;
}

void Shell::set_evaluator(bool statement) {
	this->success = statement;
}
	
void Shell::set_subTree(bool statement) {
	this->subTree = statement;
}

bool Shell::get_subTree() {
	return this->subTree;
}

Shell* Shell::getRightChild() {
	return this->rightChild;
}

Shell* Shell::getLeftChild() {
	return this->leftChild;
}

string Shell::getNewInput() {
	return this->newInput;
}

void Shell::setNewInput(string input) {
	this->newInput = input;
}	

void Shell::insert(Shell* fExe, Shell* Node){
	cout << " entered insert function";
	
	string type = Node->type();
	 if (type == "&&" || type  == "||" || type == ";" ){
		cout << " connector statement";
		if(this->parent == NULL){
		//cout << " IF ";
			this->parent = Node;
			Node->leftChild = fExe;
		}

		else{
			//cout << " ELSE";
			Shell* temp = fExe;
			while (temp->parent != NULL) {
				temp = temp->parent;
			}

			temp->parent = Node;
			Node->leftChild = temp;
		}

	}
	else if (type == "" || type == " " ){
		cout << " EMPTY NODE!!!!!!";
	}

	else{
		cout << " arg statement";
		Shell* temp = fExe;
		while (temp->parent != NULL) {
			temp = temp->parent;
		}

		temp->rightChild = Node;
		Node->parent = temp;
		
	}
	cout << " exited insert function " << endl;
	
}
void Shell::subTreeInsert(Shell* subfExe, Shell* node){
	cout << " entered subtree insert function";
	
	string type = node->type();
	if (type == "&&" || type == "||" || type == ";") {
		cout << " subtree connector statement";
		if (this->parent == NULL) {
			this->parent = node;
			node->rightChild = subfExe;
		}

		else{
			Shell* temp = subfExe;
			while (temp->parent != NULL) {
				temp = temp->parent;
			}

			temp->parent = node;
			node->rightChild = temp;
		}
	}
	else if (type == "" || type == " ") {
                cout << " EMPTY NODE!!!!!!";
        }
	else {
		cout << " sub arg statement";
		Shell* temp = subfExe;
		while (temp->parent != NULL) {
			temp = temp->parent;
		}

		temp->leftChild = node;
		node->parent = temp;
	}
}

void Shell::display(Shell* fExe) {
	if (fExe->parent == NULL) {
		Inorder(fExe);
	}

	else {
		Shell* temp = fExe;
		while (temp->parent != NULL) {
			temp = temp->parent;
		}

		Inorder(temp);
	}
}

void Shell::Inorder(Shell* Node){
	if (Node != NULL) {
		Inorder(Node->leftChild);
		cout << " " <<Node->type();
		Inorder(Node->rightChild);
	}
}

void Shell::run(Shell* fExe) {
	Shell* temp = fExe;
	
	if(fExe->parent == NULL) {
		runInorder(fExe);
	}
	
	else{
		while (temp->parent != NULL) {
			
			temp = temp->parent;
		}
		runInorder(temp);
	}
	return;
}


void Shell::runInorder(Shell* Node) {
	if (Node != NULL) {
		if (Node->type() == "exit" || Node->type() == "Exit") {
			return;
		} 
		runInorder(Node->leftChild);
		Node->execute(Node->type());
		if (!Node->get_subTree()) {
			subTreeCounter = 1;
		}	
		//checks if current Node is ";"
		if (Node->type() == ";") {
			if (!Node->get_subTree()) {
				++mainCounter;
			}
			runInorder(Node->rightChild);
			Node->set_evaluator(true);
			return;
		}
		//checks if current Node is "||"
		if (Node->type() == "||") {
			if (!Node->get_subTree()) {
                                ++mainCounter;
                        }

			if (Node->leftChild->evaluator()) {
				Node->set_evaluator(true);
				return;
			}
			else {
				runInorder(Node->rightChild);
				if (Node->rightChild->evaluator()) {
					Node->set_evaluator(true);
					return;
				}
				else {
					Node->set_evaluator(false);
					return;
				}
			}
		}
		
		//checks if current Node is "&&"
		if (Node->type() == "&&") {
			if (!Node->get_subTree()) {
                                ++mainCounter;
                        }

			if (Node->leftChild->evaluator()) {	
				runInorder(Node->rightChild);
				if (Node->rightChild->evaluator()) {
					Node->set_evaluator(true);
					return; 
				}
				else {
					Node->set_evaluator(false);
					return;
				}
			}
			else {
				Node->set_evaluator(false);
				return;
			}
		}
						
	}
	return;
}

void Shell::deleteTree(Shell* fExe) {
	Shell* temp = fExe;
	
	if (fExe->parent == NULL) {
		deleteInorder(fExe);
	}
	
	else {
		while (temp->parent != NULL) {
			temp = temp->parent;
		}
		deleteInorder(temp);
	}
}

void Shell::deleteInorder(Shell* Node) {
	if (Node != NULL) {
		deleteInorder(Node->leftChild);
		deleteInorder(Node->rightChild);
		delete Node;
	}
	return;
}

void Shell::testNodeInsert(Shell* fExe, Shell* testNode) {
	fExe->leftChild = testNode;
	testNode->parent = fExe;

}

Shell* Shell::getParent(Shell* subfExe) {
	Shell* temp = subfExe;
	
	while (temp->parent != NULL) {  
		temp = temp->parent;
	}
	return temp;
}

void Shell::connectTrees(Shell* root, Shell* subRoot) {
	root->rightChild = subRoot;
	subRoot->parent = root;

}

Shell* Shell::getFExe(Shell* root) {
	Shell* temp = root;
	
	while (temp->leftChild != NULL) {
		temp = temp->leftChild;
	}

	return temp;

}

