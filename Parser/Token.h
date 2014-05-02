#ifndef TOKEN_H
#define TOKEN_H

#include<string>

class Token{
private:
	const std::string			symbol;
	const int					line;

	Token();
	Token(const Token& rhs);
	Token & operator=(const  Token& rhs);

public:
	Token(const int _line, const std::string _symbol) :
		line(_line), symbol(_symbol){}

	~Token(){/* no need to delete token_group because it already gets deleted by user */ }

	std::string					getSymbol()		const	{ return this->symbol; }
	int							getLine()		const	{ return line; }

};
#endif