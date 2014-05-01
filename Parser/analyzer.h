#ifndef _ANALYZER_H
#define _ANALYZER_H
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Token.h"
#include "LineTokenizer.h"
#include "predefined.h"
#include "predefinedTokens.h"


using namespace std;

class Analyzer
{
private:
	map<string, string> vars;
	int m_ifelse;
	int m_numOfPar;
	int m_numOfBrace;
	int m_numOfBrak;
	bool m_lastWasType;
	string m_lastType;
	bool firstUnNullLine;
	// if found error on parenthesis don't keep checking for errors
	bool m_checkPar[3];
	bool m_noErrors;

	void printError(int line);
	virtual bool isType(const string& str) const;
	bool Analyzer::isToken(const string& str, const vector<string>& tokens) const;
	virtual bool isLegalName(const string& str) const;
	virtual bool isAlpha(const char ch) const;
	virtual bool isOperator(const string& str) const;
	bool isNum(const char ch) const;
	bool isNum(const string& st) const;
protected:
public:
	Analyzer();
	virtual ~Analyzer();
	const map<string, string>& getVars() const { return vars; }
	bool analyze(vector<Token*>& tokens, vector<string>& tokensList);
	bool getNoErrors() const { return m_noErrors; }
};

#endif