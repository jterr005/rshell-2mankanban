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
nclude <iostream>
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

int main(int, char**){
    Shell* fExe = NULL;
    string input;

    while(input != "exit") {	
	input.clear();
	mainCounter = 1;
    	cout << "$ ";
	fExe = NULL;
    	getline(cin, input);
	
	if(input == "exit") {
		break;
	}
    char_separator<char> sep("", "|&;[]");
    tokenizer<char_separator<char> > tokens(input,sep);
	
	for(tokenizer<char_separator<char> >::iterator it = tokens.begin();
	it != tokens.end();++it){
		cout << *it;

		if(*it == "&" || *it == "|" || *it == ";"){
				cout << " CTR ";
				string ctr = *it;
				Connectors* node = new Connectors(ctr);
				cout << "NODE created";
				fExe->insert(fExe,node);
			if(*it == "&" || *it == "|"){
				++it;			
			}	
		}
		else if(*it == "["){
			//tokenizer<char_separator<char> >::iterator bracIte = it;
			cout << " BRACKET " << endl;
			string testBracket = *it;
			++it;
			while(*it != "]"){
				cout << *it << endl;
				testBracket += *it;
				++it;
			}
			
			testBracket += "]";
			cout << testBracket << endl;
			Test* node = new Test(testBracket);
			cout << "NODE created";
				if(fExe == NULL){
					fExe = node;
					cout << " test node root created";
				}
				else{
					fExe->insert(fExe,node);
				}
			
		}
			
		else{
			cout << " ARRG ";
			string arrg  = *it;
			Executables* node = new Executables(arrg);
			cout << "NODE created";
				if(fExe == NULL){
					fExe = node;
					cout << " root created";
				}	
				else{
					fExe->insert(fExe,node);
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


