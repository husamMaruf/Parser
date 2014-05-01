#ifndef TOKENGROUP_H
#define TOKENGROUP_H

#include<list>
#include <algorithm>

struct Context;
class Token;




class TokenGroup{
public: 
	TokenGroup(){}
	virtual					~TokenGroup(){}

	//each token group should implement these methods:

	//this method specifies how the parser should verify tokens from this group
	virtual void		process(const Token &T ,Context *c) const = 0;	

	//create a token from the given symbol , with token_group = the current group.
	virtual Token*	createToken(const int line, const std::string symbol)const  = 0;

	
private:
	TokenGroup(const TokenGroup& other);
	TokenGroup & operator=(const TokenGroup& rhs);
};


#endif
