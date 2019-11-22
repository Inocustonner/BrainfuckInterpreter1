#include "Parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK_PTR(ptr) if ((ptr) == NULL){fprintf(stderr, "Failed to allocate\n");throw;}

global_variable Token curr_token;


void consume()
{
	curr_token = nextToken();
}


AST rule_expr()
{
	AST astExpr;
	memset((void*)&astExpr, '\0', sizeof(astExpr));
	
	astExpr.token = curr_token;
	astExpr.type = NodeType::EXPR;
	while (curr_token.name == astExpr.token.name)
	{
		astExpr.rep++;
		consume();
	}
	return astExpr;
}


AST rule_loop()
{
	//no token needed for loop node
	AST astLoop;
	memset((void*)&astLoop, '\0', sizeof(astLoop));
	
	u32 capacity = 32;
	astLoop.children = (AST*)calloc(capacity, sizeof(AST));
	CHECK_PTR(astLoop.children);
	
	consume(); //[
	while (curr_token.name != TokenName::LOOPE)
	{
		if (curr_token.name == TokenName::EOI) throw;
		
		if (curr_token.name == TokenName::LOOPS)
		{
			astLoop.children[astLoop.nChildren++] = rule_loop();
		}
		else
		{
			astLoop.children[astLoop.nChildren++] = rule_expr();
		}
		
		if (astLoop.nChildren == capacity - 1)
		{
			AST* prev = astLoop.children;
			astLoop.children = (AST*)calloc(capacity + capacity, sizeof(AST));
		    CHECK_PTR(astLoop.children);
			
			memcpy((void*)astLoop.children, (void*)prev, astLoop.nChildren * sizeof(AST));
			free(prev);			
		}
	}
	consume();
	return astLoop;
}


AST *rule_program()
{
	u32 capacity = 64;
	
	AST *prog = (AST*)calloc(1, sizeof(AST));
	CHECK_PTR(prog);
	
	prog->children = (AST*)calloc(capacity, sizeof(AST));
    CHECK_PTR(prog->children);
	
	prog->type = NodeType::PROG;
	while (curr_token.name != TokenName::EOI)
	{
		if (curr_token.name == TokenName::LOOPS)
		{
			prog->children[prog->nChildren++] = rule_loop();
		}
		else
		{
			prog->children[prog->nChildren++] = rule_expr();
		}

		if (prog->nChildren == capacity - 1)
		{
			AST* prev = prog->children;
			prog->children = (AST*)calloc(capacity + capacity, sizeof(AST));
		    CHECK_PTR(prog->children);
			
			memcpy((void*)prog->children, (void*)prev, prog->nChildren * sizeof(AST));
			free(prev);
		}
	}
	return prog;
}


AST *parse(FILE *fp)
{
	initLexer(fp);
	curr_token = nextToken();
	return rule_program();
}
