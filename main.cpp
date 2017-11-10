#include <iostream>
//github.com/cs100/rshell-2mankanban.git
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

int main(int, char**)
{
    Shell* fExe = NULL;
    string input;
    cout << "$";
    getline(cin, input);

    char_separator<char> sep("","|&;");
    tokenizer<char_separator<char> > tokens(input,sep);
/*
    for(tokenizer<char_separator<char> >::iterator it = tokens.begin();
    it != tokens.end();++it){
      cout << *it << " ";
    }
*/	
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

	cout << "Running commands: " << endl;
	fExe->run(fExe);
return 0;
}


