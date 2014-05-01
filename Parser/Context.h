#include <vector>
#include <list>
class Token;
class UserDefined_TokenGroup;
class PreDefined_TokenGroup;

struct Context{
public:
	Context() :
		prev_tok(NULL),
		currentLine(1)
	{}

	Token * prev_tok;
	int currentLine;
	//add more members if you neeed

private:

};