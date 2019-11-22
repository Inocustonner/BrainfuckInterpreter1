#pragma once
#include "Lexer.h"

enum class NodeType
{
	LOOP,
	EXPR,
	PROG,
};

typedef struct _AST
{
	Token token;
	NodeType type;

	u32 rep;
	u64 nChildren;
	_AST* children;
}AST;

AST *parse(FILE *fp);
