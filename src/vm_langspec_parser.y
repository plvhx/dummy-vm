%{

#include "ast.h"
#include "global.h"

extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);

void yyerror(const char *str)
{
	fprintf(stderr, "Error: %s\n", str);
}

int yywrap(void)
{
	return 1;
}

%}

%union {
	vm_ast_t *ast;
	char *buf;
}

%token TOKEN_COMMA
%token <buf> TOKEN_REGISTER
%token <buf> TOKEN_INTEGER
%token <buf> TOKEN_MNEMONIC

%type <ast> init top_statement_list top_statement
%type <ast> complete_insn integer_value register
%type <ast> mnemonic param

%start init

%%

init:
	top_statement_list
		{ VM_CG(ast) = $1; }
	;

top_statement_list:
	  top_statement_list top_statement
	  	{ $$ = vm_ast_add_child($1, $2); }
	| %empty
		{ $$ = vm_ast_create_single_ex_call(VM_AST_ROOT, NULL); }
	;

top_statement:
	complete_insn
		{ $$ = $1; }
	;

complete_insn:
	  mnemonic register TOKEN_COMMA param
	  	{
	  		$$ = vm_ast_create_multi_ex_call(
	  			VM_AST_INSTRUCTION_LINE,
	  			NULL,
	  			$1,
	  			$2,
	  			$4,
	  			NULL
	  		);
	  	}
	| complete_insn TOKEN_COMMA param
		{ $$ = vm_ast_add_child($1, $3); }
	;

integer_value:
	TOKEN_INTEGER
		{ $$ = vm_ast_create_single_ex_call(VM_AST_INTEGER_VALUE, $1); }
	;

register:
	TOKEN_REGISTER
		{ $$ = vm_ast_create_single_ex_call(VM_AST_REGISTER, $1); }
	;

mnemonic:
	TOKEN_MNEMONIC
		{ $$ = vm_ast_create_single_ex_call(VM_AST_MNEMONIC, $1); }
	;

param:
	  integer_value
		{ $$ = $1; }
	| register
		{ $$ = $1; }
	;
%%

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
	fclose(out);

	return 0;
}
