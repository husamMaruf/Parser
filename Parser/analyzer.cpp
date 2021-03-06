#include "analyzer.h"

#include<iostream>
#include <iomanip>

using namespace std;

Analyzer::Analyzer() :

m_ifelse(0),
m_numOfPar(0),
m_numOfBrace(0),
m_numOfBrak(0),
m_lastWasType(false),
m_lastWasOperator(false),
m_lastOperator("op"),
m_lastType("Undefined"),
firstUnNullLine(true),
m_lastDec(false),
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
	cout << "Line " << line << ": error, ";
}

static bool isType(const string& str) 
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

static bool isToken(const string& str, const vector<string>& tokens)  {
	for (unsigned int i = 0; i < tokens.size(); i++) {
		if (tokens[i] == str) {
			return true;
		}
	}
	return false;
}

static bool isNum(const char ch)  {
	return (ch >= '0' && ch <= '9');
}

// check if the token string is a number
static bool isNum(const string& st)  {
	int numOfDots = 0;
	for (unsigned int i = 0; i < st.length(); i++) {
		if (st.at(i) == '.') {
			if (i == st.length() - 1) {
				return false;
			}
			numOfDots++;
		}
		if ((!isNum(st.at(i)) && st.at(i) != '.') || numOfDots > 1) {
			return false;
		}
	}
	return true;
}

// check if the given string is operator
static bool isOperator(const string& str) {
	for (unsigned int i = 0; i < 11; i++) {
		if (operators[i] == str) {
			return true;
		}
	}
	return false;
}


void Analyzer::checkIfBrackets(std::string str, int line){
	if (str == "("){
		m_numOfPar++;
	}
	if (str == ")"){
		m_numOfPar--;
	}
	if (str == "["){
		m_numOfBrak++;
	}
	if (str == "]"){
		m_numOfBrak--;
	}
	if (str == "{"){
		m_numOfBrace++;
	}
	if (str == "}"){
		m_numOfBrace--;
	}

	if (m_numOfPar < 0 && m_checkPar[0]) {
		m_checkPar[0] = false;
		printError(line);
		cout << "')' without '('" << endl;
	}
	if (m_numOfBrak < 0 && m_checkPar[1]) {
		m_checkPar[1] = false;
		printError(line);
		cout << "']' without '['" << endl;
	}
	if (m_numOfBrace < 0) {
		m_checkPar[2] = false;
		m_numOfBrace++;
		printError(line);
		cout << "'}' without '{'" << endl;
	}
}

void Analyzer::checkBalancedIfElse(std::string str, int line){
	if (str == "if") {
		m_ifelse++;
	}
	if (str == "else") {
		m_ifelse--;
	}

	if (m_ifelse < 0 && str == "else") {
		printError(line);
		cout << "\"else\" without \"if\"" << endl;
		m_ifelse++;
	}
}

void Analyzer::checkIfDoubleType(std::string str, int line, const  vector<std::string>& tokensList){
	if (isToken(str, tokensList) && m_lastWasType) {
		printError(line);
		cout << "multiple type" << endl;
	}

}

void Analyzer::checkIfUndeclaredVar(std::string str, int line, const vector<std::string>& tokensList){
	if (!isToken(str, tokensList) && !isNum(str) && vars.find(str) == vars.end()) {
		printError(line);
		cout << "'" << str << "' isn't declared" << endl;
	}
}

// add new variables if they haven't already defined
void Analyzer::checkAddVar(std::string str, int line, const  vector<std::string>& tokensList){
	if (!isToken(str, tokensList) && m_lastWasType) { // declaration of variable
		if (vars.find(str) == vars.end()) { // check if is in var list
			vars[str] = m_lastType;
			//m_lastType = "Undef";
			m_lastDec = true;
		}
		else {
			if (m_lastWasType) {
				printError(line);
				cout << "variable '" << str << "' already declared" << endl;
			}
		}
	}
}

void Analyzer::progEndCheckBrackets(int line){
	if (m_numOfBrace > 0){
		printError(line);
		cout << m_numOfBrace << " '{' not closed" << endl;
	}

	if (m_numOfBrak > 0){
		printError(line);
		cout << m_numOfBrak << " '[' not closed" << endl;
	}

	if (m_numOfPar > 0){
		printError(line);
		cout << m_numOfPar << " '(' not closed" << endl;
	}
}


bool Analyzer::analyze(vector<Token*>& tokens, const vector<std::string>& tokensList)
{
	vector<Token*>::const_iterator it = tokens.cbegin();
	while (it != tokens.cend()){

		//std::string a = (*it)->getSymbol(); // for debug


		//check if the prgram start with MAIN or main
		if (firstUnNullLine && ((*it)->getSymbol() != "MAIN") && ((*it)->getSymbol() != "main")) {
			printError((*it)->getLine());
			cout << "'main' has to be the first" << endl;
		}

		// main should appear just at the first line
		if ((*it)->getSymbol() == "main" && !firstUnNullLine){
			printError((*it)->getLine());
			cout << "'main' has to be the first" << endl;
		}

		//update and check number of Brackets
		checkIfBrackets((*it)->getSymbol(), (*it)->getLine());

		// not balanced if-else
		checkBalancedIfElse((*it)->getSymbol(), (*it)->getLine());

		// check if double type
		checkIfDoubleType((*it)->getSymbol(), (*it)->getLine(), tokensList);

		// check if double operators
		if (m_lastWasOperator && isOperator((*it)->getSymbol())){
			printError((*it)->getLine());
			cout << "illegal operator '" << m_lastWasOperator << (*it)->getSymbol() << "'" << endl;
		}

		//check if the the string is operator
		if (isOperator((*it)->getSymbol())){
			m_lastWasOperator = true;
			m_lastOperator = (*it)->getSymbol();
		}
		else
			m_lastWasOperator = false;

		// check if the declaration is like int a,b...
		if (m_lastDec && ((*it)->getSymbol() == ",")) {
			m_lastWasType = true;
			m_lastDec = false;
			it++;
			continue;
		}

		// check if  variable declaration
		if (isType((*it)->getSymbol())) {
			m_lastType = (*it)->getSymbol();
			m_lastWasType = true;
		}

		else {
			checkAddVar((*it)->getSymbol(), (*it)->getLine(), tokensList);
			m_lastWasType = false;
		}

		// check for use of undeclared variable
		checkIfUndeclaredVar((*it)->getSymbol(), (*it)->getLine(), tokensList);

		it++;
		firstUnNullLine = false;
	}
	return m_noErrors;
}