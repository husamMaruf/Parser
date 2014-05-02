#include <iostream>
#include<stdlib.h>
#include "parser.h"
#include "predefinedTokens.h"
//#include <vld.h>


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

	addTokens(predefined_tokens,types, 8);
	addTokens(predefined_tokens,keywords1, 5);
	addTokens(predefined_tokens,keywords2, 7);
	addTokens(predefined_tokens,operators, 11);
	addTokens(predefined_tokens,delimiter, 17);


	Parser p(predefined_tokens);
	p.parse_file("example.txt");

	int x;
	cin >> x;


}