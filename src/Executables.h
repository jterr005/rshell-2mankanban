#ifndef EXECUTABLES_H
#define EXECUTABLES_H

#include "shell.h"
#include <string>


class Executables : public Shell {
        protected:
                std::string argmnt;
        public:
		Executables(std::string input);
		void execute(std::string);
		std::string type();
		bool isParentPipe();
};
#endif

