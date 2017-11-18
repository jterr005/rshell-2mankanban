#!/bin/sh

#tests exit and commands with exit

cd .. 

make clean

make -f makefile || exit 

bin/rshell << 'EndOf'

echo exit
echo don't print this after exit || exit
echo start && echo mid ; exit && echo FINISH
echo START && exit 
echo exit should work before printing this && exit

EndOf
