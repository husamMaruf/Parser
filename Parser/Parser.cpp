#include "Parser.h"
#include <fstream>
#include "analyzer.h"
#include <iostream>


using namespace std;
std::vector<Token*> Parser::tokenize_line(const std::string line)const {
	std::vector<Token*> res;

	std::size_t prev = 0, pos;

	//split line to words, with delimiters 'tab' and 'space', then split each word to tokens and add to result
	while ((pos = line.find_first_of("\t ", prev)) != std::string::npos)
	{
		if (pos > prev){
			std::vector<Token*> tmp = tokenize_word(line.substr(prev, pos - prev));
			res.insert(res.end(), tmp.begin(), tmp.end());
		}
		prev = pos + 1;
	}
	if (prev < line.length()){
		std::vector<Token*> tmp = tokenize_word(line.substr(prev, std::string::npos));
		res.insert(res.end(), tmp.begin(), tmp.end());
	}

	return res;
}

//splits a word into tokens
std::vector<Token*> Parser::tokenize_word(const std::string word)const{
	std::vector<Token*> temp;
	if (word == "") return temp;

	result next_predefined_tok = get_next_predefined(word);

	// the whole word is a user defined token
	if (next_predefined_tok.token == NULL){
		temp.push_back(new Token(currentLine, word));
		return temp;
	}

	//insert next token to list
	temp.push_back(next_predefined_tok.token);

	//append tokens after the next token;
	std::vector<Token*> after = tokenize_word(word.substr
		(next_predefined_tok.position + next_predefined_tok.length, word.length()));
	temp.insert(temp.end(), after.begin(), after.end());

	//add all tokens that are before the next token:
	std::vector<Token*> result = tokenize_word(word.substr(0, next_predefined_tok.position));
	result.insert(result.end(), temp.begin(), temp.end());

	return result;
}

//returns the next predefined token in a word , with its position and length
Parser::result  Parser::get_next_predefined(const std::string word)const{

	int minpos = word.length() + 1; //holds the earliest position where a predefined token starts

	std::set<int> canditates_sizes; //an ordered set. holds lengths of tokens that start at minpos,

	std::vector<std::string>::const_iterator symbol_iter;
	for (symbol_iter = tokensList.cbegin(); symbol_iter != tokensList.cend(); symbol_iter++)
	{
		// check if word contains it
		int pos = word.find(*symbol_iter, 0);

		if (pos != std::string::npos){

			//if yes ,and symbol starts in minpos, save it's length in canditates_sizes
			if (pos == minpos)
				canditates_sizes.insert(symbol_iter->size());

			//if yes , but symbol starts before minpos , clear the list and update minpos
			if (pos < minpos){
				canditates_sizes.clear();
				minpos = pos;
				canditates_sizes.insert(symbol_iter->size());
			}
		}
	}

	result res;
	if (canditates_sizes.empty()){
		res.token = NULL;
		return res;
	}

	res.position = minpos;
	res.length = *canditates_sizes.rbegin();//last element in set is the biggest
	res.token = new Token(currentLine, word.substr(res.position, res.length));
	return res;

}




void Parser::parse_file(const std::string file_name){

	std::ifstream file(file_name);

	if (!file.good()){
		cout << "cannot open file " << file_name << endl;
		return;
	}

	Analyzer  a;
	bool err = true;

	std::string str;
	std::vector<Token*> tokens_in_line;
	std::vector<Token*> tokens_in_file;


	while (std::getline(file, str))
	{
		tokens_in_line = tokenize_line(str);
		err = a.analyze(tokens_in_line, tokensList) || err;
		tokens_in_file.insert(tokens_in_file.end(), tokens_in_line.begin(), tokens_in_line.end());
		currentLine++;
	}

	a.progEndCheckBrackets(currentLine-1);

	cout << endl << "file " << file_name << " contained " << tokens_in_file.size()
		<< " tokens and " << currentLine -1<< " lines" << endl;


	//delete  the Tokens
	vector<Token*>::iterator iter = tokens_in_file.begin();
	while (iter != tokens_in_file.end()){ delete(*iter++); }
}