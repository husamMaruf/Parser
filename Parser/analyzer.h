#ifndef _ANALYZER_H
#define _ANALYZER_H

#include <map>
#include "Parser.h"
#include "predefinedTokens.h"


//using namespace std; <--dont put 'using' inside h file

class Analyzer
{
private:
	std::map<std::string, std::string> vars;
	int m_ifelse; int m_numOfPar; int m_numOfBrace;
	int m_numOfBrak; bool m_lastWasType;
	std::string m_lastType;  std::string m_lastOperator;
	bool firstUnNullLine;  bool m_lastDec; bool m_lastWasOperator;
	bool m_checkPar[3]; // if found error on parenthesis don't keep checking for errors
	bool m_noErrors;

	void printError(int line);
	//bool isType(const std::string& str) const;
	//bool isToken(const std::string& str, const std::vector<std::string>& tokens) const;
	//bool isOperator(const std::string& str) const;
	//bool isNum(const char ch) const;
	//bool isNum(const std::string& st) const;
	void checkBalancedIfElse(std::string str, int line);
	void checkIfBrackets(std::string str, int line);
	void checkIfDoubleType(std::string str, int line, const std::vector<std::string>& tokensList);
	void checkIfUndeclaredVar(std::string str, int line, const  std::vector<std::string>& tokensList);
	void checkAddVar(std::string str, int line, const  std::vector<std::string>& tokensList);

protected:
public:
	Analyzer();
	virtual ~Analyzer();
	bool analyze(std::vector<Token*>& tokens, const std::vector<std::string>& tokensList);
	void progEndCheckBrackets(int line);
};

#endif