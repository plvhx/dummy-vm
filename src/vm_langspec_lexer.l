%{
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "vm_langspec_parser.h"

static char *vm_lex_alloc_strbuf(const char *buf);
%}

INTEGER		[-+]?[0-9]+
REGISTER 	(r0|R0|r1|R1|r2|R2|r2|R3)
MNEMONIC	[a-zA-Z][a-zA-Z0-9]*

%%

{INTEGER}	{ yylval.buf = vm_lex_alloc_strbuf(yytext); return TOKEN_INTEGER; }
{REGISTER}	{ yylval.buf = vm_lex_alloc_strbuf(yytext); return TOKEN_REGISTER; }
{MNEMONIC}	{ yylval.buf = vm_lex_alloc_strbuf(yytext); return TOKEN_MNEMONIC; }
","			{ return TOKEN_COMMA; }

%%

static char *vm_lex_alloc_strbuf(const char *buf)
{
	int i;
	char *rbuf = calloc(strlen(buf), sizeof(char));

	assert(rbuf != NULL);

	for (i = 0; buf[i] != '\0'; i++) {
		rbuf[i] = buf[i];
	}

	return rbuf;
}
