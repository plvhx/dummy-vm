CC = gcc

all:
	$(CC) -o vm main.c src/vm.c

clean:
	rm -f ./src/*.o
	rm -f ./vm
