#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main(int, char**)
{
    string input;
    cout << "$";
    getline(cin, input);

    char_separator<char> sep("&&");
    tokenizer<char_separator<char> > tokens(input, sep);

     for ( tokenizer<char_separator<char> >::iterator it = tokens.begin();
         it != tokens.end();
         ++it)
   {
      cout << *it << "." << endl;
   }
}

