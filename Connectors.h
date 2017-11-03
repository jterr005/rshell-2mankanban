#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "Shell.h"

using namespace std;

class Connectors {
        protected:
		string cntr;
                Shell* leftChild;
                Shell* rightChild;
        public:
                void execute(string);

};
#endif

