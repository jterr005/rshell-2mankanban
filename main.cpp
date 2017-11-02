#include <iostream>
//github.com/cs100/rshell-2mankanban.git
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>

using namespace std;
using namespace boost;

int main(int, char**)
{
    string input;
    cout << "$";
    getline(cin, input);

    char_separator<char> sep("","|&;",boost::keep_empty_tokens);
    tokenizer<char_separator<char> > tokens(input,sep);

    for(tokenizer<char_separator<char> >::iterator it = tokens.begin();
    it != tokens.end();++it){
      cout << *it << endl;
   }
}

