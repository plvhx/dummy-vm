#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "src/vm.h"

static void vm_runner_run_file(const char* file)
{
    int fd = open(file, O_RDONLY);
    struct stat st;

    if (fd < 0) {
        perror("open() fail.\n");
        return;
    }

    memset(&st, 0, sizeof(struct stat));

    if (fstat(fd, &st) < 0) {
        perror("fstat() fail.\n");
        return;
    }

    char* obuf = calloc(st.st_size, sizeof(char));

    if (obuf == NULL) {
        perror("calloc() fail.\n");
        return;
    }

    if (read(fd, obuf, st.st_size) < 0) {
        perror("read() fail.\n");
        return;
    }

    vm_t* vm = vm_init(obuf, strlen(obuf));
    vm_run(vm);
    vm_destroy(vm);

    free(obuf);
    close(fd);
}

int main(int argc, char** argv)
{
    int opt;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s -f <filename>.cplx\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
        case 'f':
            vm_runner_run_file(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s -f <filename>.cplx\n", argv[0]);
            return 1;
        }
    }

    return 0;
}
