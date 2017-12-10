#!/bin/sh

#tests for >>

cd ..
make clean
make -f makefile || exit

bin/rshell << 'EndOf'

#We don't know how to implement nested appends or append outputs through multiple commands

ls >> wut.txt
cat wut.txt
pwd >> wut.txt
cat wut.txt
echo super awesome great test part 14 >> wut.txt
cat wut.txt
echo this shouldn't be an empty file anymore because I just made it. AMAZING >> newFile.txt
cat newFile.txt

EndOf
