#!/bin/sh

#tests commands with comments

cd ..

make clean

make -f makefile || exit

bin/rshell << 'EndOf'

echo START #&& echo FINISH
cal ; pwd && echo THIRD # ; echo FAIL
ls #; cal
(ls ; pwd) # && echo FINISH

EndOf  
