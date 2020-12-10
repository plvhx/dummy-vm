CC = gcc
LEX = flex
YACC = bison
MV = mv

SRCDIR = ./src

LEXER_OBJ_DEPS = \
	$(SRCDIR)/vm_langspec_lexer.c \
	$(SRCDIR)/vm_langspec_parser.tab.h

COMPILER_OBJS = \
	$(SRCDIR)/ast.o \
	$(SRCDIR)/vm_langspec_lexer.o \
	$(SRCDIR)/vm_langspec_parser.o

compiler: $(COMPILER_OBJS)
	$(CC) -o compiler $(COMPILER_OBJS)

$(SRCDIR)/ast.o: $(SRCDIR)/ast.c
	$(CC) -c $< -o $@

$(SRCDIR)/vm_langspec_lexer.o: $(LEXER_OBJ_DEPS)
	$(CC) -c $< -o $@

$(SRCDIR)/vm_langspec_parser.o: $(SRCDIR)/vm_langspec_parser.tab.c
	$(CC) -c $< -o $@

$(SRCDIR)/vm_langspec_lexer.c: $(SRCDIR)/vm_langspec_lexer.l
	$(LEX) -o $@ $<

$(SRCDIR)/vm_langspec_parser.tab.c $(SRCDIR)/vm_langspec_parser.tab.h: $(SRCDIR)/vm_langspec_parser.y
	$(YACC) -d -k $(SRCDIR)/vm_langspec_parser.y -o $(SRCDIR)/vm_langspec_parser.tab.c

clean:
	rm -f \
		$(SRCDIR)/vm_langspec_lexer.c \
		$(SRCDIR)/vm_langspec_parser.tab.c \
		$(SRCDIR)/vm_langspec_parser.tab.h
	rm -f $(SRCDIR)/*.o
	rm -f compiler.o
	rm -f compiler

.PHONY: compiler clean
