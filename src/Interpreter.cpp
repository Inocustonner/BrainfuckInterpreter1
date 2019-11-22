#include "Parser.h"
#include <string.h>

#ifndef MEMORY_SIZE_MAX
#define MEMORY_SIZE_MAX 1024 * 1024
#endif

global_variable i8 memory[MEMORY_SIZE_MAX];
global_variable i8 *caret;

internal
void eval(AST *tree);


internal
void eval_expr(AST astExpr)
{
	switch (astExpr.token.name)
	{
		case TokenName::INC:
		{
			*caret += astExpr.rep;			
		}break;

		case TokenName::DEC:
		{
			*caret -= astExpr.rep;
		}break;

		case TokenName::MOVF:
		{
			caret += astExpr.rep;
		}break;

		case TokenName::MOVB:
		{
			caret -= astExpr.rep;
		}break;

		case TokenName::IN:
		{
			*caret = getchar();
		}break;

		case TokenName::OUT:
		{
			putchar(*caret);
		}break;
	}
}


internal
void eval_loop(AST astLoop)
{
	while (*caret != 0)
	{
		for (u32 i = 0; i < astLoop.nChildren; ++i)
		{
			switch (astLoop.children[i].type)
			{
				case NodeType::EXPR:
				{
					eval_expr(astLoop.children[i]);
				}break;

				case NodeType::LOOP:
				{
					eval_loop(astLoop.children[i]);
				}break;
			}
		}
	}
}



internal
void eval_prog(AST astProg)
{
	for (u32 i = 0; i < astProg.nChildren; ++i)
	{
		eval(&astProg.children[i]);
	}
}


internal
void eval(AST *tree)
{
	switch (tree->type)
	{
		case NodeType::EXPR:
		{
			eval_expr(*tree);
		}break;

		case NodeType::LOOP:
		{
			eval_loop(*tree);
		}break;

		case NodeType::PROG:
		{
			eval_prog(*tree);
		}break;
	}
}


internal
void initInterpreter()
{
	memset((void*)memory, '\0', sizeof(memory));
	caret = memory;
}
