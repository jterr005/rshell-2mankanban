#ifndef SHELL_H
#define SHELL_H

using namespace std;

class Shell {
	protected:
		char prompt = "$";
		bool success = false;
		Shell* parent = NULL;
        public:
		Shell();
                virtual void execute() = 0;
                bool evaluator();
                void insert(Shell*);
                void display();

};
#endif

