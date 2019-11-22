#include "Lexer.h"
#include <stdlib.h>
#include <string.h>



const char *tokenNameStr(TokenName id)
{
	switch(id)
	{
		case TokenName::EOI:
			return "EOI";

		case TokenName::MOVF:
			return "MOVF";
			
		case TokenName::MOVB:
			return "MOVB";

		case TokenName::INC:
			return "INC";
			
		case TokenName::DEC:
			return "DEC";

		case TokenName::OUT:
			return "OUT";

		case TokenName::IN:
			return "IN";

		case TokenName::LOOPS:
			return "LOOPS";

		case TokenName::LOOPE:
			return "LOOPE";
  		default:
			fprintf(stderr, "Undefined tokenStrName %d\n", (i32)id);
			throw "Wrong token id or token name for id wasn't defined";
	}
}


global_variable FILE* input;
global_variable u64 pos;
global_variable u64 line;
global_variable char curr_char;

void advance()
{
	++pos;
	curr_char = getc(input);
	if (curr_char == EOF)
	{
		curr_char = '\0';
    }
	if (curr_char == '\n') line++;
}

void initLexer(FILE* fp)
{
	input = fp;
	line = 1;
	pos = 0;
	advance();
}

Token nextToken()
{
	Token token;
	while (curr_char != '\0')
	{
		switch (curr_char)
		{
			case '>':
			{
				token.name = TokenName::MOVF;
				advance();
				return token;
			}
			
			case '<':
			{
				token.name = TokenName::MOVB;
				advance();
				return token;
			}
			
			case '+':
			{
				token.name = TokenName::INC;
				advance();
				return token;
			}
			
			case '-':
			{
				token.name = TokenName::DEC;
				advance();
				return token;
			}
			
			case '.':
			{
				token.name = TokenName::OUT;
				advance();
				return token;
			}
			
			case ',':
			{
				token.name = TokenName::IN;
				advance();
				return token;
			}
			
			case '[':
			{
				token.name = TokenName::LOOPS;
				advance();
				return token;
			}
			
			case ']':
			{
				token.name = TokenName::LOOPE;
				advance();
				return token;
			}
			
			case ' ': case '\t': case '\n': case '\r': advance(); break;
				
		   	default:
				advance();
		}
	}
	token.name = TokenName::EOI;
	return token;
}
