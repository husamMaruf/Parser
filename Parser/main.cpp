#include <iostream>
#include<stdlib.h>
#include "parser.h"
#include "predefinedTokens.h"
#include <vld.h>


void addTokens(std::vector<std::string> vec,const std::string words[], const int size)
{
	for (int i = 0; i < size; i++)
	{
		vec.push_back(words[i]);
	}
}


using namespace std;
int main(){

	std::vector<std::string> predefined_tokens;

	addTokens(predefined_tokens,types, types_size);
	addTokens(predefined_tokens,keywords1, keywords1_size);
	addTokens(predefined_tokens,keywords2, keywords2_size);
	addTokens(predefined_tokens,operators,operators_size);
	addTokens(predefined_tokens,delimiter, delimiters_size);


	Parser p(predefined_tokens);
	p.parse_file("example.txt");

	int x;
	cin >> x;


}