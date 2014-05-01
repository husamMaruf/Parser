
#include <iostream>
#include<stdlib.h>
#include "parser.h"
#include "predefined.h"
//#include <vld.h>



using namespace std;
int main(){



	std::list<std::string> _operators;// = { "+", "-", "++", "--" };
	_operators.push_back("+");
	_operators.push_back("++");


	std::list<std::string> _types;// = { "int", "short", "long", "double", "float", "bool" };
	_types.push_back("int");

	//create predefined token groups list :
	TokenGroup_Operators operators(_operators);
	TokenGroup_VarTypes types(_types);

	std::list<PreDefined_TokenGroup* const > pdtg;
	pdtg.push_front(&operators);
	pdtg.push_front(&types);


	//create the user defined token group :
	UserDefined_TokenGroup udtg;




	//instantiate LineTokenizer object:
	LineTokenizer tk(pdtg, &udtg);



	//use the tokenizer:
	vector<Token*> result;

	result = tk.tokenize_file("example.txt");
	
	/*
	string example = "int x ++kkk+++ jjj+++mmm++";

	result = tk.tokenize_line(example);	//<-use debugger to see the result 

	vector<Token*>::const_iterator it = result.cbegin();

	while (it != result.cend()){

		cout << "symbol=\t" << (*it)->getSymbol() << "\tpointer to token group=\t" << (*it)->getTokenGroup() <<"\t\n" ;
		it++;
	}
	*/

//	now using Parser:
	Parser p(pdtg,&udtg);
	p.parseFile("example.txt");



	//delete  the Tokens
	vector<Token*>::iterator iter = result.begin();
	while (iter != result.end()){delete(*iter++);}


	int x;
	cin >> x;


}