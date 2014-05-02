#include <iostream>
#include<stdlib.h>
#include "parser.h"
//#include <vld.h>



using namespace std;
int main(){


	Parser tk;



	//use the tokenizer:
	vector<Token*> result;

	result = tk.parse_file("example.txt");



	//delete  the Tokens
	vector<Token*>::iterator iter = result.begin();
	while (iter != result.end()){ delete(*iter++); }


	int x;
	cin >> x;


}