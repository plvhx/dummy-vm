%{

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "vm_langspec_parser.tab.h"

static char *vm_lex_alloc_strbuf(const char *buf);
static int vm_lex_is_register(const char *buf);

%}

INTEGER		[-+]?[0-9]+
STRING 		[a-zA-Z][a-zA-Z0-9]*

%%

{INTEGER}	{ yylval.buf = vm_lex_alloc_strbuf(yytext); return TOKEN_INTEGER; }
{STRING}	{
	yylval.buf = vm_lex_alloc_strbuf(yytext);
	return !vm_lex_is_register(yylval.buf) ? TOKEN_MNEMONIC : TOKEN_REGISTER;
}
","			{ return TOKEN_COMMA; }
[ \t\r]+	;
[\n]+		;

%%

static char *vm_lex_alloc_strbuf(const char *buf)
{
	int i;
	char *rbuf = calloc(strlen(buf) + 1, sizeof(char));

	assert(rbuf != NULL);

	for (i = 0; buf[i] != '\0'; i++) {
		rbuf[i] = buf[i];
	}

	return rbuf;
}

static int vm_lex_is_register(const char *buf)
{
	if (!strcasecmp(buf, "r0") ||
		!strcasecmp(buf, "r1") ||
		!strcasecmp(buf, "r2") ||
		!strcasecmp(buf, "r3")) {
		return 1;
	}

	return 0;
}
