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
	int m_ifelse;
	int m_numOfPar;
	int m_numOfBrace;
	int m_numOfBrak;
	bool m_lastWasType;
	std::string m_lastType;
	bool firstUnNullLine;
	bool m_lastDec;
	// if found error on parenthesis don't keep checking for errors
	bool m_checkPar[3];
	bool m_noErrors;

	void printError(int line);
	virtual bool isType(const std::string& str) const;
	bool Analyzer::isToken(const std::string& str, const std::vector<std::string>& tokens) const;
	virtual bool isAlpha(const char ch) const;
	virtual bool isOperator(const std::string& str) const;
	bool isNum(const char ch) const;
	bool isNum(const std::string& st) const;
	void checkBalancedIfElse(std::string str, int line);
	void checkIfBrackets(std::string str, int line);
	void checkIfDoubleType(std::string str, int line, const std::vector<std::string>& tokensList);
	void checkIfUndeclaredVar(std::string str, int line, const  std::vector<std::string>& tokensList);
	void checkAddVar(std::string str, int line, const  std::vector<std::string>& tokensList);

protected:
public:
	Analyzer();
	virtual ~Analyzer();
	const std::map<std::string, std::string>& getVars() const { return vars; }//<--not used anywhere
	bool analyze(std::vector<Token*>& tokens, const std::vector<std::string>& tokensList);
	bool getNoErrors() const { return m_noErrors; }// <-- not used 
};

#endif