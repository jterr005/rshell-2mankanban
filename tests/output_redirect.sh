
#!/bin/sh

#tests for >

cd ..
make clean
make -f makefile || exit

bin/rshell << 'EndOf'

#We don't know how to implement nested output redirections. We also don't know how to implement multiple commands to work with output redirections.

ls > wut.txt
cat wut.txt
pwd > wut.txt
cat wut.txt
echo More amazing text to be added to this great project. > wut.txt
cat wut.txt
echo THIS IS A HUGE SPAM OF TEXT TO SHOW THE POWER OF HOW WE CAN TRUNCATE A FILE DOWN TO ADD NEW AND FRESH STUFF TO IT > wut.txt
cat wut.txt
ls > wut.txt
cat wut.txt

EndOf
