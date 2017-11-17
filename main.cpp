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
    	char_separator<char> sep("", "|&;[]()");	
	for(tokenizer<char_separator<char> >::iterator it = tokens.begin();it != tokens.end();++it){
		cout << *it << endl;

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
		else if(*it == "" || *it == " "){

		}	
		else if(*it == "["){
			cout << " BRACKET ";
		
	
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
			cout << "NODE created";
				if(fExe == NULL){
					fExe = node;
					cout << " test node root created";
				}
				else{
					fExe->insert(fExe,node);
				}
			
		}
			
		else if(*it == "("){
			cout << " parentheses " << endl;
			
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
				++it;
			}
			cout << "subtree will contain: " << subTree << endl;
				
			std::vector<std::string> parts;
    			boost::split(parts, subTree, boost::is_any_of("|&;"));
			for(vector<string>::iterator subIt = parts.end(); subIt != parts.begin(); --subIt){
			Shell* subfExe = NULL;
				if(*subIt == "&" || *subIt == "|" || *subIt == ";"){
                                	cout << " SUB CTR ";
                                	string ctr = *subIt;
                                	Connectors* node = new Connectors(ctr);
                                	cout << "NODE created";
                                	subfExe->subTreeInsert(subfExe,node);

                        		if(*subIt == "&" || *subIt == "|"){
                                		--subIt;
                        		}
                		}
				else{
                        		cout << " SUB ARRG ";
                        		string arrg  = *subIt;
                        		Executables* node = new Executables(arrg);
                        		cout << "NODE created";
                                	
					if(subfExe == NULL){
                                        	subfExe = node;
                                        	cout << "sub root created";
                                	}
                                	else{
                                        	subfExe->subTreeInsert(subfExe,node);
                                	}
                		}

		
			}
		

		}
			
		else{
			string arrg  = *it;
			if(arrg.at(0) == 't' && arrg.at(1) == 'e' && arrg.at(2) == 's' && arrg.at(3) == 't'){
				cout << " TEST ";
				Test* node = new Test(arrg);
				cout << "NODE created";
					if(fExe == NULL){
						fExe = node;
						cout << " test root created";
					}
					else{
						fExe->insert(fExe,node);
					}
			}
			else if(arrg.at(1) == 't' && arrg.at(2) == 'e' && arrg.at(3) == 's' && arrg.at(4) == 't'){
                                cout << " TEST ";
                                Test* node = new Test(arrg);
                                cout << "NODE created";
                                        if(fExe == NULL){
                                                fExe = node;
                                                cout << " test root created";
                                        }
                                        else{
                                                fExe->insert(fExe,node);
                                        }
                        }
			else{
				cout << " ARRG ";
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


