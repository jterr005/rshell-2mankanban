#ifndef TEST_H
#define TEST_H

#include "shell.h"
#include <string>


class Test: public Shell {
        protected:
                std::string test;
        public:
		void execute(std::string);
		Test(std::string input);
		std::string type();

              

};
#endif

