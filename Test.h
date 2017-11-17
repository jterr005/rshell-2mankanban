#ifndef TEST_H
#define TEST_H

#include "shell.h"
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <vector> 


class Test: public Shell {
        protected:
                std::string test;
        public:
		void execute(std::string);
		Test(std::string input);
		std::string type();

              

};
#endif

