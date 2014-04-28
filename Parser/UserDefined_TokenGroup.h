#ifndef USERDEFINED_TOKENGROUP_H
#define USERDEFINED_TOKENGROUP_H


#include "Token.h"

class UserDefined_TokenGroup :public TokenGroup{
public:
	UserDefined_TokenGroup(){}
	~UserDefined_TokenGroup(){}

	void process(const Token& T /*add parameters */)const {
		// TODO: implement 
	}

	Token* createToken(const int line, const std::string symbol)const {
		return new Token(line, symbol, this);
	}


private:
	UserDefined_TokenGroup(const  UserDefined_TokenGroup &other);
	const UserDefined_TokenGroup& operator=(const  UserDefined_TokenGroup& rhs);
};

#endif