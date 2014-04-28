#ifndef LINETOKENIZER_H
#define LINETOKENIZER_H

#include<vector>
#include<set>


#include "PreDefined_TokenGroup.h"
#include "UserDefined_TokenGroup.h"

class LineTokenizer{
public:
	LineTokenizer(std::list<PreDefined_TokenGroup*const > _pdtg, UserDefined_TokenGroup * _udtg) :
		predefined_token_groups(_pdtg), currentLine(0), user_defined_token_group(_udtg){}

	~LineTokenizer(){ /* no need to delete the token groups, they are being deleted by user */ }

	//getters & setters:
	int												getCurrentLine()				const { return currentLine;}
	void											setCurrentLine(const int val)		  { currentLine = val; }
	const 	UserDefined_TokenGroup*					getUser_defined_token_group()	const { return user_defined_token_group;}
	const std::list<PreDefined_TokenGroup*const>	getPredefined_token_groups()	const { return predefined_token_groups; }

	//the primary public method: 
	std::vector<Token*>								tokenize_line(const std::string line)	const;


protected:
	struct result{									//used by get_next_predefined()
		Token*	token;
		int		position;
		int		length;
	};

	std::vector<Token*> tokenize_word(const std::string word)								const;
	result				get_next_predefined(const std::string word)							const;
	Token*				createToken(const std::string symbol, const int line)				const;
	result				create_result_from(const int minpos,
										   const std::string word,
										   const std::set<int>&canditates_sizes)			const;


private:
	LineTokenizer();
	LineTokenizer						(const LineTokenizer& other);
	LineTokenizer & operator=			(const LineTokenizer& rhs);

	int currentLine;
	const std::list<PreDefined_TokenGroup*const >	predefined_token_groups;
	const UserDefined_TokenGroup*const	 			user_defined_token_group;
};
#endif