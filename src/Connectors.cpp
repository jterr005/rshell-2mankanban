#include <iostream>
#include <string>
#include "Connectors.h"
#include "Executables.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <fstream>

using namespace std;

Connectors::Connectors(string input) {
	if (input == "&") {
		this->cntr = "&";
	}

	else if (input == "|") {
		this->cntr = "|";
	}

	else if (input == ";") {
		this->cntr = ";";
	}

	else if (input == "&&") {
		this->cntr = "&&";
	}

	else if (input == "||") {
		this->cntr = "||";
	}

	else if (input == "<") {
		this->cntr = "<";
	}

	else if (input == ">") {
		this->cntr = ">";
	}

	else if (input == ">>") {
		this->cntr = ">>";
	}

	else {
		this->cntr = "test";
	}

}

string Connectors::type() {
	return cntr;
}

void Connectors::execute(string cntr) {
	if (cntr == "<") { //Input Redirection Branch
		char* argmts[1028];
		mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		int flags = O_RDWR | O_CREAT;

		string fileName = this->rightChild->type();
		string command = this->leftChild->type();
		int savestdin = dup(0);
		if (fileName.at(0) == ' ') {
			fileName.erase(0,1);
		}

		int customin = open(fileName.c_str(), flags, permissions);
		cout << "we opened him" << endl;
		if (customin < 0) {
			perror("Open failed: ");
			exit(1);
		}

		dup2(customin, 0);

		//CONTINUES FORKING AND EXE HERE
		string space = " ";
		string totalCommand;
		totalCommand += command;
		totalCommand += space;
		totalCommand +=fileName;
		vector<string> package;
		boost::split(package, totalCommand, boost::is_any_of(" "));

		unsigned i = 0;
		package.at(1) = package.at(2);
		package.pop_back();
		unsigned packageSize = package.size();
		while (packageSize > 0) {
			argmts[i] = (char*)package.at(i).c_str();
			++i;
			--packageSize;
		}

		argmts[i] = NULL;
		int status = 0;
		pid_t pid = fork();
		if(pid == 0) {
			execvp(argmts[0], argmts);
			perror("execvp failed: ");
			exit(-1);
		}

		else if(pid > 0) {
			if (waitpid(pid, &status, 0) == -1) {
				perror("Wait: ");
				this->success = false;
				close(customin);
				dup2(savestdin, 0);
				close(savestdin);
			}

			if(WEXITSTATUS( status ) && WIFEXITED( status ) != 0 ) {
				this->success = false;
				close(customin);
				dup2(savestdin, 0);
				close(savestdin);
			}

			else {
				close(customin);
				dup2(savestdin, 0);
				close(savestdin);
				this->success = true;
				return;
			}

			return;
		}

		else{
			close(customin);
			dup2(savestdin, 0);
			close(savestdin);
			return;
		}

	}

	if(cntr == ">>") { //Output Appending Redirection Branch
		char* argmts[1028];
		mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
		int flags = O_RDWR | O_CREAT | O_APPEND;

		string fileName = this->rightChild->type();
		string command;
		if(this->leftChild->type() != "&&" || this->leftChild->type() != "||" || this->leftChild->type() != ";" || this->leftChild->type() != ">>" || this->leftChild->type() != ">" || this->leftChild->type() != "<") {
			command = this->leftChild->type();
		}

		else {
			command = this->leftChild->getRightChild()->type();
		}

		int saveOldstdout = dup(1);
		if (fileName.at(0) == ' ') {
			fileName.erase(0,1);
		}

		int out2File = open(fileName.c_str(), flags, permissions);
		if (out2File < 0) {
			perror("Open failed: ");
			exit(1);
		}

		dup2(out2File, 1);

    string totalCommand;
    totalCommand += command;
    vector<string> package;
    boost::split(package, totalCommand, boost::is_any_of(" "));

		package.pop_back();

		unsigned i = 0;
    unsigned packageSize = package.size();
		while (packageSize > 0) {
    	argmts[i] = (char*)package.at(i).c_str();
      ++i;
      --packageSize;
    }

    argmts[i] = NULL;
    int status = 0;
    pid_t pid = fork();

		if (pid == 0) {
    	execvp(argmts[0], argmts);
      perror("execvp failed: ");
      exit(-1);
    }

    else if (pid > 0) {
    	if (waitpid(pid, &status, 0) == -1) {
        perror("Wait: ");
        this->success = false;
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
      }

      if (WEXITSTATUS( status ) && WIFEXITED( status ) != 0 ) {
        this->success = false;
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
      }

      else {
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
        this->success = true;
        return;
      }

      return;
    }

    else {
      close(out2File);
      dup2(saveOldstdout, 1);
      close(saveOldstdout);
      return;
    }

	}

	 if (cntr == ">") { //Output Redirection Branch
    char* argmts[1028];
    mode_t permissions =  S_IWUSR |  S_IWGRP | S_IWOTH;
    int flags = O_WRONLY | O_CREAT | O_TRUNC;

		string fileName = this->rightChild->type();
    string command;
    if(this->leftChild->type() != "&&" || this->leftChild->type() != "||" || this->leftChild->type() != ";" || this->leftChild->type() != ">>" || this->leftChild->type() != ">" || this->leftChild->type() != "<") {
      command = this->leftChild->type();
    }

    else {
      command = this->leftChild->getRightChild()->type();
		}

		int saveOldstdout = dup(1);
    if (fileName.at(0) == ' ') {
      fileName.erase(0,1);
    }

    int out2File = open(fileName.c_str(), flags, permissions);
    if (out2File < 0) {
      perror("Open failed: ");
      exit(1);
    }

    dup2(out2File, 1);
		string totalCommand;
    totalCommand += command;
		vector<string> package;
    boost::split(package, totalCommand, boost::is_any_of(" "));
    package.pop_back();
		unsigned i = 0;
		unsigned packageSize = package.size();
    while (packageSize > 0) {
      argmts[i] = (char*)package.at(i).c_str();
      ++i;
      --packageSize;
    }

    argmts[i] = NULL;
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
      execvp(argmts[0], argmts);
      perror("execvp failed: ");
      exit(-1);
    }

    else if (pid > 0) {
      if (waitpid(pid, &status, 0) == -1) {
        perror("Wait: ");
        this->success = false;
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
      }

      if(WEXITSTATUS( status ) && WIFEXITED( status ) != 0 ) {
        this->success = false;
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
      }

      else {
        close(out2File);
        dup2(saveOldstdout, 1);
        close(saveOldstdout);
        this->success = true;
        return;
      }

      return;
    }

    else {
      close(out2File);
      dup2(saveOldstdout, 1);
      close(saveOldstdout);
      return;
    }

	}

}
