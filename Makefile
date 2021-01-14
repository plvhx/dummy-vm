CC = gcc
LEX = flex
YACC = bison
MV = mv

SRCDIR = ./src
TESTVM_DIR = ./test-vm

LEXER_OBJ_DEPS = \
	$(SRCDIR)/vm_langspec_lexer.c \
	$(SRCDIR)/vm_langspec_parser.tab.h

COMPILER_OBJS = \
	$(SRCDIR)/ast.o \
	$(SRCDIR)/vm_langspec_lexer.o \
	$(SRCDIR)/vm_langspec_parser.o

RUNNER_OBJS = \
	$(SRCDIR)/insn.o \
	$(SRCDIR)/regs.o \
	$(SRCDIR)/value.o \
	$(SRCDIR)/vm.o

DISPATCHER_OBJS = \
	$(RUNNER_OBJS) \
	dispatcher.o

TESTVM_OBJS = \
	$(RUNNER_OBJS) \
	$(TESTVM_DIR)/movb_imm8_to_r0.o \
	$(TESTVM_DIR)/movb_imm8_to_r1.o \
	$(TESTVM_DIR)/movb_imm8_to_r2.o \
	$(TESTVM_DIR)/movb_imm8_to_r3.o \
	$(TESTVM_DIR)/movb_r0_to_r0.o \
	$(TESTVM_DIR)/movb_r1_to_r0.o \
	$(TESTVM_DIR)/movb_r2_to_r0.o \
	$(TESTVM_DIR)/movb_r3_to_r0.o \
	$(TESTVM_DIR)/movb_r0_to_r1.o \
	$(TESTVM_DIR)/movb_r1_to_r1.o \
	$(TESTVM_DIR)/movb_r2_to_r1.o \
	$(TESTVM_DIR)/movb_r3_to_r1.o \
	$(TESTVM_DIR)/movb_r0_to_r2.o \
	$(TESTVM_DIR)/movb_r1_to_r2.o \
	$(TESTVM_DIR)/movb_r2_to_r2.o \
	$(TESTVM_DIR)/movb_r3_to_r2.o \
	$(TESTVM_DIR)/movb_r0_to_r3.o \
	$(TESTVM_DIR)/movb_r1_to_r3.o \
	$(TESTVM_DIR)/movb_r2_to_r3.o \
	$(TESTVM_DIR)/movb_r3_to_r3.o \
	$(TESTVM_DIR)/addb_imm8_imm8_to_r0.o \
	$(TESTVM_DIR)/addb_imm8_imm8_to_r1.o \
	$(TESTVM_DIR)/addb_imm8_imm8_to_r2.o \
	$(TESTVM_DIR)/addb_imm8_imm8_to_r3.o \
	$(TESTVM_DIR)/subb_imm8_imm8_to_r0.o \
	$(TESTVM_DIR)/subb_imm8_imm8_to_r1.o \
	$(TESTVM_DIR)/subb_imm8_imm8_to_r2.o \
	$(TESTVM_DIR)/subb_imm8_imm8_to_r3.o \
	$(TESTVM_DIR)/mulb_imm8_imm8_to_r0.o \
	$(TESTVM_DIR)/mulb_imm8_imm8_to_r1.o \
	$(TESTVM_DIR)/mulb_imm8_imm8_to_r2.o \
	$(TESTVM_DIR)/mulb_imm8_imm8_to_r3.o \
	$(TESTVM_DIR)/divb_imm8_imm8_to_r0.o \
	$(TESTVM_DIR)/divb_imm8_imm8_to_r1.o \
	$(TESTVM_DIR)/divb_imm8_imm8_to_r2.o \
	$(TESTVM_DIR)/divb_imm8_imm8_to_r3.o \
	$(TESTVM_DIR)/addb_imm8_r0_to_r0.o \
	$(TESTVM_DIR)/addb_imm8_r0_to_r1.o \
	$(TESTVM_DIR)/addb_imm8_r0_to_r2.o \
	$(TESTVM_DIR)/addb_imm8_r0_to_r3.o \
	$(TESTVM_DIR)/subb_imm8_r0_to_r0.o \
	$(TESTVM_DIR)/subb_imm8_r0_to_r1.o \
	$(TESTVM_DIR)/subb_imm8_r0_to_r2.o \
	$(TESTVM_DIR)/subb_imm8_r0_to_r3.o \
	$(TESTVM_DIR)/mulb_imm8_r0_to_r0.o \
	$(TESTVM_DIR)/mulb_imm8_r0_to_r1.o \
	$(TESTVM_DIR)/mulb_imm8_r0_to_r2.o \
	$(TESTVM_DIR)/mulb_imm8_r0_to_r3.o \
	$(TESTVM_DIR)/divb_imm8_r0_to_r0.o \
	$(TESTVM_DIR)/divb_imm8_r0_to_r1.o \
	$(TESTVM_DIR)/divb_imm8_r0_to_r2.o \
	$(TESTVM_DIR)/divb_imm8_r0_to_r3.o \
	$(TESTVM_DIR)/addb_imm8_r1_to_r0.o \
	$(TESTVM_DIR)/main.o

all: compiler dispatcher test-vm

compiler: $(COMPILER_OBJS)
	$(CC) -o compiler $(COMPILER_OBJS)

dispatcher: $(DISPATCHER_OBJS)
	$(CC) -o dispatcher $(DISPATCHER_OBJS)

test-vm: $(TESTVM_OBJS)
	$(CC) -o $(TESTVM_DIR)/test_vm $(TESTVM_OBJS)

$(TESTVM_DIR)/movb_imm8_to_r0.o: $(TESTVM_DIR)/movb_imm8_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_imm8_to_r1.o: $(TESTVM_DIR)/movb_imm8_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_imm8_to_r2.o: $(TESTVM_DIR)/movb_imm8_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_imm8_to_r3.o: $(TESTVM_DIR)/movb_imm8_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r0_to_r0.o: $(TESTVM_DIR)/movb_r0_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r1_to_r0.o: $(TESTVM_DIR)/movb_r1_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r2_to_r0.o: $(TESTVM_DIR)/movb_r2_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r3_to_r0.o: $(TESTVM_DIR)/movb_r3_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r0_to_r1.o: $(TESTVM_DIR)/movb_r0_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r1_to_r1.o: $(TESTVM_DIR)/movb_r1_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r2_to_r1.o: $(TESTVM_DIR)/movb_r2_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r3_to_r1.o: $(TESTVM_DIR)/movb_r3_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r0_to_r2.o: $(TESTVM_DIR)/movb_r0_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r1_to_r2.o: $(TESTVM_DIR)/movb_r1_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r2_to_r2.o: $(TESTVM_DIR)/movb_r2_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r3_to_r2.o: $(TESTVM_DIR)/movb_r3_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r0_to_r3.o: $(TESTVM_DIR)/movb_r0_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r1_to_r3.o: $(TESTVM_DIR)/movb_r1_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r2_to_r3.o: $(TESTVM_DIR)/movb_r2_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/movb_r3_to_r3.o: $(TESTVM_DIR)/movb_r3_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_imm8_to_r0.o: $(TESTVM_DIR)/addb_imm8_imm8_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_imm8_to_r1.o: $(TESTVM_DIR)/addb_imm8_imm8_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_imm8_to_r2.o: $(TESTVM_DIR)/addb_imm8_imm8_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_imm8_to_r3.o: $(TESTVM_DIR)/addb_imm8_imm8_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_imm8_to_r0.o: $(TESTVM_DIR)/subb_imm8_imm8_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_imm8_to_r1.o: $(TESTVM_DIR)/subb_imm8_imm8_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_imm8_to_r2.o: $(TESTVM_DIR)/subb_imm8_imm8_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_imm8_to_r3.o: $(TESTVM_DIR)/subb_imm8_imm8_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_imm8_to_r0.o: $(TESTVM_DIR)/mulb_imm8_imm8_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_imm8_to_r1.o: $(TESTVM_DIR)/mulb_imm8_imm8_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_imm8_to_r2.o: $(TESTVM_DIR)/mulb_imm8_imm8_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_imm8_to_r3.o: $(TESTVM_DIR)/mulb_imm8_imm8_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_imm8_to_r0.o: $(TESTVM_DIR)/divb_imm8_imm8_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_imm8_to_r1.o: $(TESTVM_DIR)/divb_imm8_imm8_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_imm8_to_r2.o: $(TESTVM_DIR)/divb_imm8_imm8_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_imm8_to_r3.o: $(TESTVM_DIR)/divb_imm8_imm8_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_r0_to_r0.o: $(TESTVM_DIR)/addb_imm8_r0_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_r0_to_r1.o: $(TESTVM_DIR)/addb_imm8_r0_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_r0_to_r2.o: $(TESTVM_DIR)/addb_imm8_r0_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_r0_to_r3.o: $(TESTVM_DIR)/addb_imm8_r0_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_r0_to_r0.o: $(TESTVM_DIR)/subb_imm8_r0_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_r0_to_r1.o: $(TESTVM_DIR)/subb_imm8_r0_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_r0_to_r2.o: $(TESTVM_DIR)/subb_imm8_r0_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/subb_imm8_r0_to_r3.o: $(TESTVM_DIR)/subb_imm8_r0_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_r0_to_r0.o: $(TESTVM_DIR)/mulb_imm8_r0_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_r0_to_r1.o: $(TESTVM_DIR)/mulb_imm8_r0_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_r0_to_r2.o: $(TESTVM_DIR)/mulb_imm8_r0_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/mulb_imm8_r0_to_r3.o: $(TESTVM_DIR)/mulb_imm8_r0_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_r0_to_r0.o: $(TESTVM_DIR)/divb_imm8_r0_to_r0.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_r0_to_r1.o: $(TESTVM_DIR)/divb_imm8_r0_to_r1.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_r0_to_r2.o: $(TESTVM_DIR)/divb_imm8_r0_to_r2.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/divb_imm8_r0_to_r3.o: $(TESTVM_DIR)/divb_imm8_r0_to_r3.c
	$(CC) -c $< -o $@

$(TESTVM_DIR)/addb_imm8_r1_to_r0.o: $(TESTVM_DIR)/addb_imm8_r1_to_r0.c
	$(CC) -c $< -o $@

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
	rm -f $(TESTVM_DIR)/*.o
	rm -f $(TESTVM_DIR)/test_vm
	rm -f compiler.o
	rm -f compiler
	rm -f dispatcher.o
	rm -f dispatcher

.PHONY: compiler clean
