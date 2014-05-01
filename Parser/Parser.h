
#include "LineTokenizer.h"
#include <fstream>
#include <iostream>

class Parser{
private:
	LineTokenizer ltokenizer;


public:

	Parser(std::list<PreDefined_TokenGroup* const > _pdtg, UserDefined_TokenGroup * _udtg) :
		ltokenizer(_pdtg, _udtg){}

		void parseFile(std::string file_name);


};

void Parser::parseFile(std::string file_name){
	std::ifstream file("example.txt");
	std::string str;
	while (std::getline(file, str))
	{
		std::cout <<"processing line:\t"<< str<<std::endl;


		std::vector<Token*> tokens_in_line=ltokenizer.tokenize_line(str);

		std::vector<Token*>::iterator iter = tokens_in_line.begin();
		while (iter != tokens_in_line.end()){
			(*iter)->process(/*more paramters you may need*/); 
			iter++;
		}
	}
}