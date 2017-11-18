#ifndef SHELL_H
#define SHELL_H
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern int mainCounter;
extern int subTreeCounter;

class Shell {
	protected:
		char prompt;
		bool success;
		bool subTree;
		Shell* parent;
		Shell* rightChild;
		Shell* leftChild;
		
        public:
		Shell();
                virtual void execute(std::string) = 0;
               	void testNodeInsert(Shell* fExe, Shell* testNode);
                void set_evaluator(bool);
		bool evaluator();
                void insert(Shell* fExe, Shell* Node);
		void subTreeInsert(Shell* subfExe, Shell* node);
		virtual std::string type() = 0;
		void display(Shell* fExe);
		void Inorder(Shell* Node);
		void run(Shell* fExe);
		void runInorder(Shell*);
		void deleteTree(Shell*);
		void deleteInorder(Shell*);
		Shell* getParent(Shell* subfExe);
		void connectTrees(Shell* root, Shell* subRoot);
		void set_subTree(bool);
		bool get_subTree();
		Shell* getFExe(Shell* root);

};
#endif

