#ifndef LINETOKENIZER_H
#define LINETOKENIZER_H

#include<vector>
#include<set>

#include "Token.h"

class Parser{
public:
	Parser(std::vector<std::string> predefined_tokens) :
		tokensList(predefined_tokens),
		currentLine(1)
	{}

	~Parser(){ /* no need to delete the token groups, they are being deleted by user */ }

	//the primary public method:
	void parse_file(const std::string file_name);

private:

	struct result{										 //used by get_next_predefined()
		Token* token;
		int position;
		int length;
	};

	result get_next_predefined(const std::string word) const;

	std::vector<Token*> tokenize_line(const std::string line) const;
	std::vector<Token*> tokenize_word(const std::string word) const;
	std::vector<std::string> tokensList;

	Parser(const Parser& other);
	Parser & operator= (const Parser& rhs);

	int currentLine;

};
#endif