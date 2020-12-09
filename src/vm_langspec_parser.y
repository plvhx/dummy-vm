%{

#include "./src/global.h"

extern int yyparse(void);
extern int yylex(void);
extern FILE * yyin;

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
	  	{ $$ = vm_ast_create_multi_ex_call(VM_AST_INSTRUCTION_LINE, $1, $2, $4); }
	| mnemonic register TOKEN_COMMA param TOKEN_COMMA param
		{ $$ = vm_ast_create_multi_ex_call(VM_AST_INSTRUCTION_LINE, $1, $2, $4, $6); }
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
