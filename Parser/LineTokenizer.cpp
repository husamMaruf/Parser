#include "LineTokenizer.h"


//find the group where this symbol is in , and let it create a token with this symbol.
Token*  LineTokenizer::createToken(const std::string symbol, const int line)const{
	std::list<PreDefined_TokenGroup*>::const_iterator iter;

	for (iter = predefined_token_groups.cbegin(); iter != predefined_token_groups.cend(); ++iter){
		PreDefined_TokenGroup* group = *iter;

		Token *tok = group->createToken(line, symbol);
		if (tok != NULL)
			return tok;
	}
	return NULL;
}

std::vector<Token*> LineTokenizer::tokenize_line(const std::string line)const {
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
std::vector<Token*> LineTokenizer::tokenize_word(const std::string word)const{
	std::vector<Token*> temp;
	if (word == "") return temp;

	result next_predefined_tok = get_next_predefined(word);

	// the whole word is a user defined token
	if (next_predefined_tok.position == -1){
		Token * tok = new Token(currentLine, word, user_defined_token_group);
		temp.push_back(tok);
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
LineTokenizer::result  LineTokenizer::get_next_predefined(const std::string word)const{

	int minpos = word.length() + 1;		//holds the earliest position where a predefined token starts

	std::set<int> canditates_sizes;		//an ordered set. holds lengths of tokens that start at minpos,
										//and are candidates to be the next token. the result will be 
										//the token with the biggest length from this set (the last element)

	std::list<PreDefined_TokenGroup*>::const_iterator group_iter;
	for (group_iter = predefined_token_groups.cbegin(); group_iter != predefined_token_groups.cend(); ++group_iter){
		PreDefined_TokenGroup * group = *group_iter;
		std::list<std::string> known_symbols = group->get_known_symbols();

		//for each symbol in each predefined token group
		std::list<std::string>::const_iterator symbol_iter;
		for (symbol_iter = known_symbols.cbegin(); symbol_iter != known_symbols.cend(); ++symbol_iter){

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
	}
	return create_result_from(minpos, word, canditates_sizes);
}



LineTokenizer::result LineTokenizer::
create_result_from(const int minpos, const std::string word, const std::set<int>& canditates_sizes)const{
	result res;

	//this means that no symbol from the predefined symbols was found in the word and that
	//the whole word should be a user defined token , this case is handled in tokenize_word()
	if (canditates_sizes.empty()){
		res.token = NULL;
		res.length = res.position = -1;
		return res;
	}

	//from all candidates , return the longest token
	res.position = minpos;
	res.length = *canditates_sizes.rbegin();//last element in set is the biggest 
	res.token = createToken(word.substr(res.position, res.length), currentLine);
	return res;
}