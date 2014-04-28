#ifndef TOKEN_H
#define TOKEN_H

#include<string>
#include "TokenGroup.h"

class Token{
private:
	const std::string			symbol;
	const int					line;
	const TokenGroup* const		token_group;			

	Token();
	Token(const Token& rhs);
	Token & operator=(const  Token& rhs);

public:
	Token( const int _line,  const std::string _symbol,  const  TokenGroup  * const  _tg):
		line(_line), symbol(_symbol), token_group(_tg){}

	~Token(){/* no need to delete token_group because it already gets deleted by user */}

	const	TokenGroup* const	getTokenGroup()	const	{ return token_group; }
	std::string					getSymbol()		const	{ return this->symbol; }
	int							getLine()		const	{ return line; }
	void						process(/*add parameters*/)		const	{ token_group->process(*this);}
};
#endif
