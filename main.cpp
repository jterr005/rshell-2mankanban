#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include "shell.h"
#include "Connectors.h"
#include "Executables.h"

using namespace std;
using namespace boost;

//This is the assignment of a global variable declared somewhere else
int mainCounter = 1;

int main(int, char**)
{
    Shell* fExe = NULL;
    Shell* testNode = NULL;
    bool testExist = false;
    string input;

    while(input != "exit") {	
	input.clear();
	mainCounter = 1;
	testExist = false;
	testNode = NULL;
    	cout << "$ ";
	fExe = NULL;
    	getline(cin, input);
	
	if(input == "exit") {
		break;
	}
    
    char_separator<char> sep("","|&;");
    tokenizer<char_separator<char> > tokens(input,sep);
	
	for(tokenizer<char_separator<char> >::iterator it = tokens.begin();
	it != tokens.end();++it){
		cout << *it;
		if(*it == "&" || *it == "|" || *it == ";"){
				cout << " CTR ";
				string input = *it;
				Connectors* Node = new Connectors(input);
				cout << "NODE created";
				fExe->insert(fExe,Node);
			if(*it == "&" || *it == "|"){
				++it;	
			}	
		}
		else{
			cout << " ARRG ";
			string input = *it;
			
			if(input.at(0) == 't' && input.at(1) == 'e' && input.at(2) == 's' && input.at(3) == 't'){
				cout << endl;
				cout << "test detected!!!" << endl;
				input.erase(0,5);
				string insertTest = "test";
				Connectors* Node = new Connectors(insertTest);
				testNode = Node;
				testExist = true;
				insertTest.clear();
			}
			



			Executables* Node = new Executables(input);
			cout << "NODE created";
				if(fExe == NULL){
					fExe = Node;
					cout << " root created";
					if(testExist == true){
						fExe->testNodeInsert(fExe,testNode);
					}
				}	
				else{
					fExe->insert(fExe,Node);
				}
		}
		cout << endl;
	}

	cout << "INORDER: " << endl;
	fExe->display(fExe);
	cout << endl;

	cout << "Running commands: " << endl;
	fExe->run(fExe);
	cout << endl;

	cout << "Deleting commands: " << endl;
	fExe->deleteTree(fExe);
	cout << endl;
}

return 0;
}


