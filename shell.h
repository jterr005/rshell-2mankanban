#ifndef SHELL_H
#define SHELL_H

using namespace std;

class Shell {
	protected:
		char prompt;
		bool success;
		Shell* parent = NULL;
		
        public:
		Shell();
               // virtual void execute() = 0;
               	void displayAssist(Shell*);
                virtual string type(Shell*) = 0;
                //bool evaluator();
                void insert(Shell* root, Shell* node);
                //void display();

};
#endif

