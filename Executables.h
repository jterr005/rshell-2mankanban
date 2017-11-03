#ifndef EXECUTABLES_H
#define EXECUTABLES_H

#include "shell.h"

using namespace std;

class Executables {
        protected:
                string argmnt;
        public:
		Executables(string input);
                void execute(string);
		string type(Shell* node);

};
#endif

