
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
	Context *c = new Context(ltokenizer.getUser_defined_token_group(), ltokenizer.getPredefined_token_groups());

	std::ifstream file("example.txt");
	std::string str;
	std::vector<Token*> tokens_in_line;
	while (std::getline(file, str))
	{
		std::cout <<"processing line:\t"<< str<<std::endl;


		 tokens_in_line=ltokenizer.tokenize_line(str);

		std::vector<Token*>::iterator current_tok = tokens_in_line.begin();
		while (current_tok != tokens_in_line.end()){
			(*current_tok)->process(c); 
			c->prev_tok = *current_tok;
			
			current_tok++;
			
		}
		c->currentLine++;
	}

	//delete context
	delete c;

	//delete tokens_in_line
	std::vector<Token*>::iterator iter = tokens_in_line.begin();
	while (iter != tokens_in_line.end()){ delete(*iter++); }
}