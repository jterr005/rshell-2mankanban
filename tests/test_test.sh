#!/bin/bash

#This bash script tests for the test command

cd ..
make clean
make -f makefile || exit 

bin/rshell << 'EndOf'

[ -e src/Test.cpp ]
[ -e src/DummyFile.cpp ]
[ -f makefile ]
[ -d ../rshell-2mankanban ]

test -e src/Test.cpp
test -e src/DummyFile.cpp
test -f makefile
test -d makefile

([ -e src/Test.cpp ] || echo FAIL) && echo SUCCUESS
(echo PLAY || test src/Connectors.cpp) && echo SUCCESS
test src/Connectors.h ; (echo FIRST PRINT || echo SECOND PRINT) ; (test src/Test.h && echo SUCCESS)
([ -e src/dummyfile.cpp ])

echo test -e makefile
echo test -f Test.cpp
echo [ -f Test.h ]
echo [ -d Connectors.h ]
echo test -d Executables.h

EndOf 
