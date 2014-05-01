#include "analyzer.h"
#include <iomanip>

Analyzer::Analyzer() :

m_ifelse(0),
m_numOfPar(0),
m_numOfBrace(0),
m_numOfBrak(0),
m_lastWasType(false),
m_lastType("Undefined"),
firstUnNullLine(true),
m_noErrors(true)
{
	memset(m_checkPar, true, 3);
}

Analyzer::~Analyzer()
{
}


void Analyzer::printError(int line)
{
	m_noErrors = false;
	cout << "Line " << line << ": Error - ";
}

bool Analyzer::isType(const string& str) const
{
	for (int i = 0; i < 8; i++)
	{
		if (types[i] == str)
		{
			return true;
		}
	}
	return false;
}

bool Analyzer::isToken(const string& str, const vector<string>& tokens) const
{
	for (unsigned int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == str)
		{
			return true;
		}
	}
	return false;
}

bool Analyzer::isAlpha(const char ch) const
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool Analyzer::isNum(const char ch) const
{
	return (ch >= '0' && ch <= '9');
}

bool Analyzer::isNum(const string& st) const
{
	int numOfDots = 0;
	for (unsigned int i = 0; i < st.length(); i++)
	{
		if (st.at(i) == '.')
		{
			if (i == st.length() - 1)
			{
				return false;
			}
			numOfDots++;
		}
		if ((!isNum(st.at(i)) && st.at(i) != '.') || numOfDots > 1)
		{
			return false;
		}
	}
	return true;
}


bool Analyzer::isOperator(const string& str) const
{
	for (unsigned int i = 0; i < 11; i++)
	{
		if (operators[i] == str)
		{
			return true;
		}
	}
	return false;
}

bool Analyzer::isLegalName(const string& str) const
{
	if (!isAlpha(str.at(0)))
	{
		return false;
	}
	for (unsigned int i = 1; i < str.length(); i++)
	{
		if (!isAlpha(str.at(i)) && !isNum(str.at(i)))
		{
			return false;
		}
	}
	return true;
}

bool Analyzer::analyze(vector<Token*>& tokens, vector<string>& tokensList)
{
	vector<Token*>::const_iterator it = tokens.cbegin();
	while (it != tokens.cend()){
		if ((*it)->getLine() == 1 || firstUnNullLine) {
			//check if the prgram start with MAIN or main
			firstUnNullLine = false;
			if (((*it)->getSymbol() != "MAIN") && ((*it)->getSymbol() != "main"))
			{
				printError((*it)->getLine());
				cout << "error, 'main' has to be the first" << endl;
			}
		}
		if ((*it)->getSymbol() == "("){
			m_numOfPar++;
		}
		if ((*it)->getSymbol() == ")"){
			m_numOfPar--;
		}
		if ((*it)->getSymbol() == "["){
			m_numOfBrak++;
		}
		if ((*it)->getSymbol() == "]"){
			m_numOfBrak--;
		}
		if ((*it)->getSymbol() == "{"){
			m_numOfBrace++;
		}
		if ((*it)->getSymbol() == "}"){
			m_numOfBrace--;
		}

		if (m_numOfPar < 0 && m_checkPar[0]) {
			m_checkPar[0] = false;
			printError((*it)->getLine());
			cout << "')' without '('" << endl;
		}
		if (m_numOfBrak < 0 && m_checkPar[1])
		{
			m_checkPar[1] = false;
			printError((*it)->getLine());
			cout << "']' without '['" << endl;
		}
		if (m_numOfBrace < 0 && m_checkPar[2])
		{
			m_checkPar[2] = false;
			printError((*it)->getLine());
			cout << "'}' without '{'" << endl;
		}

		// not balanced if-else
		if ((*it)->getSymbol() == "if")
		{
			m_ifelse++;
		}
		if ((*it)->getSymbol() == "else")
		{
			m_ifelse--;
		}

		if (m_ifelse < 0 && (*it)->getSymbol() == "else")
		{
			printError((*it)->getLine());
			cout << "error, \"else\" without \"if\"" << endl;
			m_ifelse++;
		}

		if (isToken((*it)->getSymbol(), tokensList) && m_lastWasType) // double type
		{
			printError((*it)->getLine());
			cout << "error, multiple type" << endl;
		}
		if (isType((*it)->getSymbol()))
		{
			m_lastType = (*it)->getSymbol();
			m_lastWasType = true;
		}
		else
		{
			if (!isToken((*it)->getSymbol(), tokensList) && isLegalName((*it)->getSymbol()) && m_lastWasType) // declaration
			{
				if (vars.find((*it)->getSymbol()) == vars.end()) // check if is in var list
				{
					vars[(*it)->getSymbol()] = m_lastType;
					m_lastType = "Undef";
				}
				else
				{
					if (m_lastWasType)
					{
						printError((*it)->getLine());
						cout << (*it)->getSymbol() << " already declared!" << endl;
					}
				}
			}

			/*else
			{
			if (!isToken((*it)->getSymbol(), tokensList) && !isLegalName((*it)->getSymbol()) && m_lastWasType) // check decaration is legal
			{
			printError((*it)->getLine());
			cout << "illegal variable name: " << (*it)->getSymbol() << endl;
			m_lastWasType = false;
			continue;
			}
			}*/
			m_lastWasType = false;
		}
		// check for use of undeclared variable
		if (!isToken((*it)->getSymbol(), tokensList) && !isNum((*it)->getSymbol()) && vars.find((*it)->getSymbol()) == vars.end() &&
			("MAIN" != (*it)->getSymbol()) && ("main" != (*it)->getSymbol()))
		{
			printError((*it)->getLine());
			cout << "implicit declaration of " << (*it)->getSymbol() << endl;
		}
		it++;
	}
	return m_noErrors;
}