#!/bin/sh

#tests for precedence operators

cd ..
make clean
make -f makefile || exit

bin/rshell << 'EndOf'

#We don't know how to implement nested parenthesis. We don't know how they work.
(echo START)
(ls -l ; echo CHECK) || echo FAIL
(echo A ; echo B) && (echo C ; echo D)
(echo this should fail

EndOf

