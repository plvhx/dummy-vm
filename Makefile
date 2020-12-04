CC = gcc
DEPS = \
	./src/insn.c \
	./src/vm.c

all:
	$(CC) -o vm main.c $(DEPS)

clean:
	rm -f ./src/*.o
	rm -f ./vm
