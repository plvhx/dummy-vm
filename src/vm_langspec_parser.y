%{

#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
	  mnemonic param
		{
			$$ = vm_ast_create_multi_ex_call(
				VM_AST_INSTRUCTION_LINE,
				NULL,
				$1,
				$2,
				NULL
			);
		}
	| mnemonic register TOKEN_COMMA param
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
	| mnemonic register TOKEN_COMMA param TOKEN_COMMA param
		{
			$$ = vm_ast_create_multi_ex_call(
				VM_AST_INSTRUCTION_LINE,
				NULL,
				$1,
				$2,
				$4,
				$6,
				NULL
			);
		}
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

static void vm_ast_compilation_visitor_callback(FILE *file, int opcode)
{
	fputc(opcode, file);
}

static int vm_ast_ensure_file_extension(const char *file)
{
	int i;
	size_t len = strlen(file);

	for (i = 0; i < len; i++) {
		if (file[i] == '.') {
			break;
		}
	}

	if (len - (i + 1) != 4) {
		return 0;
	}

	if (file[++i] != 'd' ||
		file[++i] != 'a' ||
		file[++i] != 's' ||
		file[++i] != 'm') {
		return 0;
	}

	return 1;
}

static int vm_ast_compile(const char *file)
{
	if (!vm_ast_ensure_file_extension(file)) {
		return 0;
	}

	yyin = fopen(file, "r");
	yyparse();

	char *ofile = strdup(file);
	int i;

	for (i = 0; ofile[i] != '\0'; i++) {
		if (ofile[i] == '.')
			break;
	}

	ofile[++i] = 'c';
	ofile[++i] = 'p';
	ofile[++i] = 'l';
	ofile[++i] = 'x';

	FILE *out = fopen(ofile, "w");

	if (out == NULL) {
		return 0;
	}

	vm_ast_traverse(
		VM_CG(ast),
		out,
		vm_ast_compilation_visitor_callback
	);

	fclose(out);
	free(ofile);

	return 1;
}

int main(int argc, char **argv)
{
	int ret, opt;

	if (argc == 1) {
		fprintf(stderr, "Usage: %s -c <filename>.dasm\n", argv[0]);
		return 1;
	}

	while ((opt = getopt(argc, argv, "c:")) != -1) {
		switch (opt) {
			case 'c':
				ret = vm_ast_compile(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s -c <filename>.dasm\n", argv[0]);
				return 1;
		}
	}

	return 0;
}
