CC = gcc
DEPS = \
	./src/insn.c \
	./src/regs.c \
	./src/vm.c

all:
	$(CC) -DDEBUG -o vm main.c $(DEPS)

clean:
	rm -f ./src/*.o
	rm -f ./vm
