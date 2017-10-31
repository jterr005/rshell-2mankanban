#include <iostream>
#include <string>
#include <cstring>

using namespace std;
void Tokenizer(string cmd){
	char Delimiters[] = "&&,||,;";
	char *Token[20];
	int i = 1;
	
	/*

	Token[0] = strtok(Delimiters,cmd);
	while( Token[i] != null){
		Token[i] = strtok(cmd, Delimiters);
		++i;
	}
	
	for(int j = 0; j < i;++j){
		cout << Token[j] << endl;
	}
*/
	
}



int main() {
	
	char input[256]
	cout << "$ ";
	getline(cin, input);
	cout << endl;
	//cout << cmd << endl;
	Tokenizer(input);
	return 0;
}
