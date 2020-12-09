#include <stdio.h>
#include <ast.h>
#include <global.h>

extern FILE *yyin;
extern int yyparse(void);

static void vm_compilation_visitor_callback(FILE *file, int opcode)
{
	fputc(opcode, file);
}

int main(void)
{
	yyin = fopen("sample.dasm", "r");
	yyparse();

	FILE *out = fopen("sample.com", "w");
	vm_ast_traverse(VM_CG(ast), out, vm_compilation_visitor_callback);

	return 0;
}
