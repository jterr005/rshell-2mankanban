#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"
#include "Test.h"

using namespace std;
using namespace boost;

//This is the assignment of a global variable declared somewhere else
int mainCounter = 1;
int subTreeCounter = 1;

int main(int, char**){
    Shell* fExe = NULL;
    Shell* root = NULL;
    Shell* subRoot = NULL;
    string input;
    
    while(input != "exit") {	
	int numOP = 0;
    	int numCP = 0;
    	int numOB = 0;
    	int numCB = 0;
        bool invalid = false;

	input.clear();
	mainCounter = 1;
	subTreeCounter = 1;
    	cout << "$ ";
	fExe = NULL;
    	getline(cin, input);
	
	if(input == "exit") {
		break;
	}
	else if(input.size() == 1){
		cout << "boost libary tokenizer function cannot parse a string with a size of 1" << endl;
		continue;
	}

	char_separator<char> sep("","[]()|&;");
        tokenizer<char_separator<char> > errorTokens(input,sep);
        for(tokenizer<char_separator<char> >::iterator it = errorTokens.begin();it != errorTokens.end();++it){
		if(*it == "(") {
			numOP += 1;
		}
		else if (*it == ")") {
			numCP += 1;
		}
		else if (*it == "[") {
			numOB += 1;
		}
		else if(*it == "]") {
			numCB += 1;
		}
		else if(*it == " exit") {
			cout << "exited";
			return 0;
		}
		else {
		
		}
	}
	if(numOP != numCP){
		cout << "Invalid number of parentheses!!!" << endl;
		invalid = true;
	}
	if(numOB != numCB) {
		cout << "Invalid number of brackets!!!" << endl;
		invalid = true;
	}
	if(invalid){
		continue;
	}
        

    	char_separator<char> errorSep("", "|&;[]()#");
	tokenizer<char_separator<char> > tokens(input,errorSep);	
	for(tokenizer<char_separator<char> >::iterator it = tokens.begin();it != tokens.end();++it){
		//cout << *it;

		if(*it == "&" || *it == "|" || *it == ";"){
			//	cout << " CTR ";
				string ctr = *it;
				Connectors* node = new Connectors(ctr);
			//	cout << "NODE created";
				fExe->insert(fExe,node);
			if(*it == "&" || *it == "|"){
				++it;			
			}	
		}
		else if(*it == "" || *it == " "){

		}
		else if(*it == "#"){
			break;
		}	
		else if(*it == "["){
			//cout << " BRACKET ";
		
	
			string testBracket = *it;
			++it;
			while(*it != "]"){
				//cout << *it << endl;
				testBracket += *it;
				++it;
			}
			
			testBracket += "]";
			//cout << testBracket << endl;
			Test* node = new Test(testBracket);
			//cout << "NODE created";
				if(fExe == NULL){
					fExe = node;
					//cout << " test node root created";
				}
				else{
					fExe->insert(fExe,node);
				}
			
		}
			
		else if(*it == "("){
			//cout << " parentheses " << endl;
			
			string subTree = *it;
			int numOp = 1;
			int numClo = 0;
			++it;
			while(numOp != numClo){
				if(*it == "("){
					numOp += 1;	
				}
				if(*it == ")"){
					numClo += 1;
				}
				subTree += *it;
				if(numOp != numClo){
					++it;
				}
			}
			//cout << "subtree will contain: " << subTree << endl;
			Shell* subfExe = NULL;
		
	
			char_separator<char> subSep("", "|&;()[]");
			//cout << "char sep worked" << endl;
        		tokenizer<char_separator<char> > subTokens(subTree,subSep);
			//cout << " tokenizer worked" << endl;
       			 for(tokenizer<char_separator<char> >::iterator subIt = subTokens.begin();subIt != subTokens.end();++subIt){
				cout << *subIt;
				
				if(*subIt == "&" || *subIt == "|" || *subIt == ";"){
                                	//cout << " SUB CTR ";
                                	string ctr = *subIt;
                                	Connectors* node = new Connectors(ctr);
					node->set_subTree(true);
                                	//cout << "NODE created";
                                	subfExe->insert(subfExe,node);

                        		if(*subIt == "&" || *subIt == "|"){
                                		++subIt;
                        		}
                		}
				else if(*subIt == "(" || *subIt == ")" || *subIt == "" || *subIt == " "){
					
				}
				else if(*subIt == "["){
                        		//cout << " BRACKET ";
                        		string testBracket = *subIt;
                        		++subIt;
                        		while(*subIt != "]"){
					       testBracket += *subIt;
                               			 ++subIt;
                       			 }

                        		testBracket += "]";
					Test* node = new Test(testBracket);
					node->set_subTree(true);
                        		//cout << "NODE created";

                                	if(subfExe == NULL){
                                        	subfExe = node;
                                        	//cout << " test node root created";
                                	}
                                	else{
                                        	subfExe->insert(subfExe,node);
                                	}

				}

				else{
					string arrg  = *subIt;
                        		if(arrg.at(0) == 't' && arrg.at(1) == 'e' && arrg.at(2) == 's' && arrg.at(3) == 't'){
                                		//cout << " TEST ";
                                		Test* node = new Test(arrg);
						node->set_subTree(true);
                                		//cout << "NODE created";
                                        	if(subfExe == NULL){
                                                	subfExe = node;
                                                	//cout << " test root created";
                                        	}	
                                        	else{
                                                	subfExe->insert(subfExe,node);
                                        	}
                        		}
                        		else if(arrg.at(1) == 't' && arrg.at(2) == 'e' && arrg.at(3) == 's' && arrg.at(4) == 't'){
                                		//cout << " TEST ";
                                		Test* node = new Test(arrg);
						node->set_subTree(true);
                                		//cout << "NODE created";
                                        	if(subfExe == NULL){
                                                	subfExe = node;
                                                	//cout << " test root created";
                                        	}
                                        	else{
                                                	subfExe->insert(subfExe,node);
                                       		}
                        		}

					else {
                        			//cout << " SUB ARRG ";
                        			string arrg  = *subIt;
                        			Executables* node = new Executables(arrg);
						node->set_subTree(true);
                        			//cout << "NODE created";
                                	
						if(subfExe == NULL){
                                        		subfExe = node;
                                        		//cout << "sub root created";
                                		}
                                		else{
                                        		subfExe->insert(subfExe,node);
                                		}
					}
                		}

				
			}
			     //cout << "SUBTREE INORDER: " << endl;
     				//subfExe->display(subfExe);
			        //cout << endl;
			        subRoot = subfExe->getParent(subfExe);
				if(fExe != NULL){
					root = fExe->getParent(fExe);
                                       // cout << "subTree root :";
                                       // cout << subRoot->type() << endl;
                                       // cout << "Tree root :";
                                        //cout << root->type() << endl;
                                        root->connectTrees(root, subRoot);
                                        //cout << "trees connected!" << endl;
                                        //cout << "INORDER TREE DISPLAY";
                                        //fExe->display(fExe);
                                        //cout << endl;
                        	}
				else {
					fExe = subRoot->getFExe(subRoot);
				}

                                

				
		}
			
		else{
			string arrg  = *it;
			if(arrg.at(0) == 't' && arrg.at(1) == 'e' && arrg.at(2) == 's' && arrg.at(3) == 't'){
				//cout << " TEST ";
				Test* node = new Test(arrg);
				//cout << "NODE created";
					if(fExe == NULL){
						fExe = node;
						//cout << " test root created";
					}
					else{
						fExe->insert(fExe,node);
					}
			}
			else if(arrg.at(1) == 't' && arrg.at(2) == 'e' && arrg.at(3) == 's' && arrg.at(4) == 't'){
                                //cout << " TEST ";
                                Test* node = new Test(arrg);
                                //cout << "NODE created";
                                        if(fExe == NULL){
                                                fExe = node;
                                                //cout << " test root created";
                                        }
                                        else{
                                                fExe->insert(fExe,node);
                                        }
                        }
			else{
				//cout << " ARRG ";
				Executables* node = new Executables(arrg);
				//cout << "NODE created";
					if(fExe == NULL){
						fExe = node;
						//cout << " root created";
					}	
					else{
						fExe->insert(fExe,node);
					}
			}
		}
		//cout << endl;
	}	

	//cout << "INORDER: " << endl;
	//fExe->display(fExe);
	//cout << endl;

	//cout << "Running commands: " << endl;
	fExe->run(fExe);
	//cout << endl;

	//cout << "Deleting commands: " << endl;
	fExe->deleteTree(fExe);
	fExe = NULL;
	root = NULL;
	subRoot = NULL;
	//cout << endl;
	

   }
   

return 0;
}


