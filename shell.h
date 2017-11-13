#ifndef SHELL_H
#define SHELL_H
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int mainCounter;

class Shell {
	protected:
		char prompt;
		bool success;
		Shell* parent;
		Shell* rightChild;
		Shell* leftChild;
		
        public:
		Shell();
                virtual void execute(std::string) = 0;
               	//void displayAssist(Shell*);
                bool evaluator();
                void insert(Shell* fExe,Shell* Node);
		virtual std::string type() = 0;
		void display(Shell* fExe);
		void Inorder(Shell* Node);
		void run(Shell* fExe);
		void runInorder(Shell*);

};
#endif

