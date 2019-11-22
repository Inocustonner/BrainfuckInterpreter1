#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "Interpreter.cpp"


void freeAST(AST *tree)
{
	for (u32 i = 0; i < tree->nChildren; ++i)
	{
		freeAST(&tree->children[i]);
	}
	if (tree->nChildren > 0) free(tree->children);
}


int main(int argc, char* argv[])
{
	FILE *fp = fopen(argv[1], "r");
	if (!fp) return -1;
	AST* prog = parse(fp);
	initInterpreter();
	eval(prog);
	freeAST(prog);
	fclose(fp);
	return 0;
}
