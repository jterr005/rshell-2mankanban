#ifndef SHELL_H
#define SHELL_H
#include <string>

class Shell {
	protected:
		char prompt;
		bool success;
		Shell* parent;
		Shell* rightChild;
		Shell* leftChild;
		
        public:
		Shell();
               // virtual void execute() = 0;
               	//void displayAssist(Shell*);
                //bool evaluator();
                void insert(Shell* fExe,Shell* Node);
		virtual std::string type() = 0;
                //void display();

};
#endif

