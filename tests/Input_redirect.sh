
#!/bin/sh

#tests for <

cd ..
make clean
make -f makefile || exit

bin/rshell << 'EndOf'

#We don't know how to implement nested input redirections. We also can't connect multiple commands to the input.

cat < wut.txt
echo this should be placed into wut >> wut.txt
cat < wut.txt

EndOf
