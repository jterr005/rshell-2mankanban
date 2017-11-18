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

void Executables::execute( string cmd ) {
	int i = 0;
	int size = 0;
	int status = 0;
	vector<string> strvctr;
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
	
	char* argmts[ size + 1 ];	
	
	//Fills argmts array with cmd
	while ( size > 0 ) {
		argmts[ i ] = ( char* )strvctr.at( i ).c_str();
		++i;
		--size;
	}
	
	argmts[ i ] = NULL;
	
	//begins actual processing of cmd
	pid_t pid = fork();

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
