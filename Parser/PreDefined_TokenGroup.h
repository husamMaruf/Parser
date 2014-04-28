#ifndef PREDEFINED_TOKENGROUP_H
#define PREDEFINED_TOKENGROUP_H


#include "Token.h"


class PreDefined_TokenGroup :public TokenGroup{
private:
	std::list<std::string> known_symbols; 


protected:
	PreDefined_TokenGroup(std::list<std::string> _known_symbols) :
		known_symbols(_known_symbols){}


public:
	~PreDefined_TokenGroup(){}

	virtual bool isInGroup(const std::string symbol)const {
		std::list<std::string >::const_iterator findIter = 
			std::find(known_symbols.cbegin(), known_symbols.cend(), symbol);
		return findIter != known_symbols.cend();
	}

	std::list<std::string>const & get_known_symbols(){ 
		return known_symbols;
	}
};
#endif