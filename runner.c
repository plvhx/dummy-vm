#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "src/vm.h"

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	struct stat st;

	if (fd < 0) {
		perror("open() fail.\n");
		return 1;
	}

	memset(&st, 0, sizeof(struct stat));

	if (fstat(fd, &st) < 0) {
		perror("stat() fail.\n");
		return 1;
	}

	char *obuf = calloc(st.st_size, sizeof(char));

	if (obuf == NULL) {
		perror("calloc() fail.\n");
		return 1;
	}

	if (read(fd, obuf, st.st_size) < 0) {
		perror("read() fail.\n");
		return 1;
	}

	vm_t *vm = vm_init(obuf);
	vm_run(vm);
	vm_destroy(vm);

	free(obuf);
	close(fd);

	return 0;
}
