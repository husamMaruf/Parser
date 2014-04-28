#ifndef PREDEFINED_H
#define PREDEFINED_H


#include "PreDefined_TokenGroup.h"

/*
definition and implementation of all classes that derive from PreDefined_TokenGroup
maybe its good to split to .h and .cpp files?
*/

//////////////////////////////////////////////////////////////////////////
class TokenGroup_Operators : public PreDefined_TokenGroup{
public:

	~TokenGroup_Operators(){}
	TokenGroup_Operators(std::list<std::string> known_symbols) :
		PreDefined_TokenGroup(known_symbols){}

	void process(const Token& T /*add parameters*/)const {
		// TODO: implement 
	}

	using PreDefined_TokenGroup::isInGroup;
	Token* createToken(const int line, const std::string symbol)const{
		if (isInGroup(symbol)){
			return new Token(line, symbol, this);
		}
		else return NULL;
	}
private:
	TokenGroup_Operators();
	TokenGroup_Operators(const  TokenGroup_Operators &other);
	const TokenGroup_Operators& operator=(const  TokenGroup_Operators& rhs);
};
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
class TokenGroup_VarTypes : public PreDefined_TokenGroup{
public:
	~TokenGroup_VarTypes(){}
	TokenGroup_VarTypes(std::list<std::string> known_symbols) :
		PreDefined_TokenGroup(known_symbols){}

	void process(const Token& T  /*add parameters*/ )const {
		// TODO: implement 
	}

	using PreDefined_TokenGroup::isInGroup;
	Token* createToken(const int line, const std::string symbol)const {
		if (isInGroup(symbol)){
			return new Token(line, symbol, this);
		}
		else return NULL;
	}
private:
	TokenGroup_VarTypes();
	TokenGroup_VarTypes(const  TokenGroup_VarTypes &other);
	const TokenGroup_VarTypes& operator=(const  TokenGroup_VarTypes& rhs);

};
//////////////////////////////////////////////////////////////////////////
#endif