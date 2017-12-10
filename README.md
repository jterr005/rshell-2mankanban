#rshell-2mankanbwan

The aim of this project is to design a functional Rshell terminal. It's main features are: using connectors (&& || ;) to connect and execute multiple commands on 1 line; being able to run the test function by using the word "test" or using [ ]/ brackets; and being able to take parentheses so that the commands inside could be run.

Bugs:

1.unable to work with nested parentheses as we do not know how to work with a recursive function that would create sub trees within a sub tree

2. unable to parse if the cmd line only 1 character in it. right now it will output a error message and lets the user enter a new command.

3. redirection only works without connectors. We couldn't figure out when we build the tree why when with a connector the redirection did not push its left child's right child into the redirection's right child. It did travel to the correct node but it does not execute properly when a connector is part of the tree.
