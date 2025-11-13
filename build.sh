#!/bin/bash

CFLAGS='-std=c89 -Werror -Wextra -Wpedantic -fsanitize=address'
CFILES='parse_mnist.c test.c'
LIBS=''

clang -o main ${CFLAGS} ${CFILES} ${LIBS}
./main
rm main
