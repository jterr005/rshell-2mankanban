#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "Shell.h"

using namespace std;

class Connectors {
        private:
		string cntr;
                Shell* leftChild;
                Shell* rightChild;
        public:
                void execute(string);
		Connectors(string input);
};
#endif

