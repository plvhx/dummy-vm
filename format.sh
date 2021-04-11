#! /bin/sh

clang-format -i ./*.[ch]
clang-format -i ./src/*.[ch]
clang-format -i ./test-ast/*.[ch]
clang-format -i ./test-vm/*.[ch]
