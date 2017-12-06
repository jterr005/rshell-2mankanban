#include <iostream>
#include <string>
#include <sstream>
#include "Executables.h"
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

Executables::Executables( string input ) {
	this->argmnt = input;
}

string Executables::type() {
	return argmnt;
}

bool Executables::isParentPipe() {
	if(parent->type() == "|") {
		return true;
	}
	
	else {
		return false;
	}

}

void Executables::execute( string cmd ) {
	int i = 0;
	int size = 0;
	int status = 0;
	vector<string> strvctr;
	char* argmts[1028];
	stringstream ss;
	string tmp;

	ss << cmd;
	
	//Determines size of char* array based on the number of strings in cmd
	while ( ss >> tmp ) {
		++size;
	}
	
	//splits cmd and pushes individual strings into a vector
	boost::split( strvctr, argmnt, boost::is_any_of(" ") );
	
	//checks if this current node is part of a sub-tree
	if ( this->get_subTree() ) {
		
		//removes a blank space that is pushed into strvctr if this node is executed after the first cmd is run
		if ( subTreeCounter > 1 ) {
			strvctr.erase( strvctr.begin() );
		}
		
		++subTreeCounter;
	}
	
	else {
		//removes a black space that is pushed into strvctr if this node is executed after the first cmd is run
		if ( mainCounter > 1 ) {
			strvctr.erase( strvctr.begin() );	
		}
		
		++mainCounter;		
	}	
	
	//Fills argmts array with cmd
	while ( size > 0 ) {
		argmts[ i ] = ( char* )strvctr.at( i ).c_str();
		++i;
		--size;
	}
	
	argmts[ i ] = NULL;
	
	//begins actual processing of cmd
	pid_t pid = fork();
	int fds[2];
	int check;

	check = pipe(fds);
	
	if(check == -1) {
		perror("piping failed: ");
		exit(1);
	}	
	
	//If a left child, executes command but instead of outputing 
	//results to screen, it saves the output in a string that is 
	//used as the input for this argument's parent's right child
	if ( isParentPipe() && this->parent->getLeftChild() == this ) {
		cout << "ENTERED PIPE IF STATEMENT BOOIIIIIII" << endl;
		if(pid == 0) { //CHILD PROCESS
			//Forces execute's output to be written into the WRITE side of the pipe
			//int savestdOut = dup(1);
			dup2(fds[1], 1);
			close(fds[0]);

			//Execute's function
			execvp(argmts[0], argmts);
			perror("execvp failed: ");
			exit(-1);
		}
		
		else if (pid > 0) { //PARENT PROCESS
			if (waitpid(pid, &status, 0) == -1) {
				perror("Wait: ");
				this->success = false;
			}
			
			if (WEXITSTATUS( status ) && WIFEXITED( status ) != 0 ) {
                                this->success = false;
                        }

			else {
				//Forces parent process to READ from child's WRITE side of the pipe
				//int savestdIn = dup(0);
				dup2(fds[0], 0);
				close(fds[1]);
				char buffer[4096];
				int i = 0;
				stringstream ss;
				
				//Pushes READ part of pipe into parent connector's newInput string
				while (read(fds[0], buffer, 4096) > 0) {
					ss << buffer[i];
					++i;
				}
				
				string tempInput = ss.str();
				this->parent->setNewInput(tempInput);
				this->success = true;
				return;

			}
			
			return;
	
		}
		 
		else if ( pid < 0 ) {
                        return;
                }

	}
	
	else {
		if ( pid == 0 ) { //CHILD PROCESS
			execvp ( argmts[ 0 ], argmts );
			perror ( "execvp failed: " );
			exit ( -1 );
		}
	
		else if ( pid > 0 ) { //PARENT PROCESS	
			if ( waitpid( pid, &status, 0 ) == -1 ) {
				perror( "Wait: " );
				this->success = false;
			}
			
			if ( WEXITSTATUS( status ) && WIFEXITED( status ) != 0 ) {
				this->success = false;
			}
		
			else { //if the process was successful, this node's success is set to true
                		this->success = true;
                		return;
        		}	
			
			return;
		}
		
		else if ( pid < 0 ) {
			return;
		}

	}

}

