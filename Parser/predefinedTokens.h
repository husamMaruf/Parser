#ifndef _PREDEFINEDTOKENS_H
#define _PREDEFINEDTOKENS_H

static int  const types_size = 8;
static const std::string types[] = { "char", "short", "int", "long", "float", "double", "void", "function" };

static int  const keywords1_size = 4;
static const std::string keywords1[] = { "if", "else", "for", "while" };

static int  const keywords2_size = 7;
static const std::string keywords2[] = { "class", "private", "public", "protected", "main", "const", "virtual" };

static int  const operators_size = 11;
static  const std::string operators[] = { "++", "--", "==", "->", "=", "+", "-", "*", "&", "<<", ">>" };

static int const delimiters_size = 17;
static const std::string delimiter[] = { "\t", " ", "(", ")", "[", "]", "{", "}", ";", "<", ">", "=", "+", "-", "*", "&", "," };


#endif