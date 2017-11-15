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
    string input;
    cout << "$ ";
    getline(cin, input);
    
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
			
			
			vector<string> testCase;
			boost::split(testCase, input, boost::is_any_of("test"));
			cout << "size of vector: " << testCase.size() << endl;
			
			for (int i = 0; i < testCase.size(); ++i){ 
				cout << testCase.at(i) << endl;
			}
			



			Executables* Node = new Executables(input);
			cout << "NODE created";
				if(fExe == NULL){
					fExe = Node;
					cout << " root created";
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
return 0;
}


