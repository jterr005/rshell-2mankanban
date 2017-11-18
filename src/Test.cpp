#include <iostream>
#include "Test.h"

using namespace std;

Test::Test( string input ) {
	this->test = input;
}

string Test::type(){
	return this->test;
}

void Test::execute( string cmd ) {
	vector<string> strvctr;

	//cout << "This is the cmd for test: " << endl;

	//Removes brackets from cmd
	cmd.erase( std::remove( cmd.begin(), cmd.end(), '[' ), cmd.end() );
	cmd.erase( std::remove( cmd.begin(), cmd.end(), ']' ), cmd.end() );
	
	//Removes whitespace from cmd and parses cmd into vector
	boost::split( strvctr, cmd, boost::is_any_of( " " ) );

	//removes blank spaces and the word "test" that is pushed into 
	//strvctr if this node is executed after the first cmd is run	
	if ( !this->get_subTree() ) {	
		
		if ( mainCounter > 1 ) {
			
			if ( cmd.find( "test" ) != string::npos ) {
				strvctr.erase( strvctr.begin() );
				strvctr.erase( strvctr.begin() );
			}

		}
		
		//removes the word "test" that is pushed into strvctr if 
		//this node is executed after the first cmd is run
		else if ( mainCounter == 1 &&  cmd.find( "test" ) != string::npos ) {
			strvctr.erase( strvctr.begin() );
		}

	}
	 	
	++mainCounter;
	
	//beings actual execution of cmd
	struct stat scan;

	if ( strvctr.at( 0 ) == "-e" ) {
		
		if ( stat( strvctr.at( 1 ).c_str(), &scan ) == 0 ) {
			cout << "(True)" << endl;
			this->set_evaluator( true );
			return;
		}
		
		else {
			cout << "(False)" << endl;
			this->set_evaluator( false );
			return;
		}

	}

	if ( strvctr.at( 0 ) == "-f" ) {
		
		if ( stat( strvctr.at( 1 ).c_str(), &scan ) == 0 && S_ISREG( scan.st_mode ) ) {
			cout << "(True)" << endl;
			this->set_evaluator( true );
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator( false );
			return;
		}
	}
	if(strvctr.at(0) == "-d") {
		if(stat(strvctr.at(1).c_str(), &scan) == 0 && S_ISDIR(scan.st_mode)) {
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
	else {
		cout << "STRING AT AT(1)" << strvctr.at(0) << endl;
		if(stat(strvctr.at(0).c_str(), &scan) == 0) { 
			cout << "(True)" << endl;
			this->set_evaluator(true);
			return;
		}
		else {
			cout << "(False)" << endl;
			this->set_evaluator(false);
			return;
		}
	}
}
