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

DISPATCHER_OBJS = \
	$(SRCDIR)/insn.o \
	$(SRCDIR)/regs.o \
	$(SRCDIR)/value.o \
	$(SRCDIR)/vm.o \
	dispatcher.o

all: compiler dispatcher

compiler: $(COMPILER_OBJS)
	$(CC) -o compiler $(COMPILER_OBJS)

dispatcher: $(DISPATCHER_OBJS)
	$(CC) -o dispatcher $(DISPATCHER_OBJS)

$(SRCDIR)/ast.o: $(SRCDIR)/ast.c
	$(CC) -c $< -o $@

$(SRCDIR)/insn.o: $(SRCDIR)/insn.c
	$(CC) -c $< -o $@

$(SRCDIR)/regs.o: $(SRCDIR)/regs.c
	$(CC) -c $< -o $@

$(SRCDIR)/value.o: $(SRCDIR)/value.c
	$(CC) -c $< -o $@

dispatcher.o: dispatcher.c
	$(CC) -c $< -o $@

$(SRCDIR)/vm.o: $(SRCDIR)/vm.c
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
	rm -f dispatcher.o
	rm -f dispatcher

.PHONY: compiler clean
