#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "shell.h"
#include <string>

class Connectors: public Shell {
        private:
		std::string cntr;
                Shell* leftChild;
                Shell* rightChild;
        public:
                //void execute(string);
		Connectors(std::string input);
		std::string type();

};
#endif

