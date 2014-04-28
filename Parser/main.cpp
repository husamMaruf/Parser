
#include <iostream>
#include<stdlib.h>
#include "LineTokenizer.h"
#include "predefined.h"
#include <vld.h>



using namespace std;
int main(){

	std::list<std::string> _operators = { "+", "-", "++", "--" };
	std::list<std::string> _types = { "int", "short", "long", "double", "float", "bool" };

	//create predefined token groups list :
	TokenGroup_Operators operators(_operators);
	TokenGroup_VarTypes types(_types);

	std::list<PreDefined_TokenGroup*const > pdtg;
	pdtg.push_front(&operators);
	pdtg.push_front(&types);


	//create the user defined token group :
	UserDefined_TokenGroup udtg;




	//instantiate LineTokenizer object:
	LineTokenizer tk(pdtg, &udtg);



	//use the tokenizer:
	vector<Token*> result;

	string example = "int x ++kkk+++ jjj+++mmm++";
	result = tk.tokenize_line(example);	//<-use debugger to see the result 
	cout << result.size();

	//result.back()->process();


	//delete  the Tokens
	vector<Token*>::iterator iter = result.begin();
	while (iter != result.end()){delete(*iter++);}


	int x;
	cin >> x;


}