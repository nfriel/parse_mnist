/*
 * IDX file parser designed for MNIST dataset
 * Written in C89
 * IDX file specification found at https://www.fon.hum.uva.nl/praat/manual/IDX_file_format.html
 * MNIST dataset mirrors found at https://github.com/cvdfoundation/mnist
*/

#ifndef PARSE_MNIST_H_
#define PARSE_MNIST_H_

#include <stdio.h>
#include <stdint.h>

#define D_WIDTH 28
#define D_HEIGHT 28

#define bool int
#define true 1
#define false 0

#define array_size(a) (sizeof(a) / sizeof(a[0]))

typedef enum {
    IDX_DATATYPE_UBYTE = 0x08,
    IDX_DATATYPE_BYTE = 0x09,
    IDX_DATATYPE_SHORT = 0x0B,
    IDX_DATATYPE_INT = 0x0C,
    IDX_DATATYPE_FLOAT = 0x0D,
    IDX_DATATYPE_DOUBLE = 0x0E
} IDX_DATATYPE;

typedef struct {
    FILE *fp;
    uint8_t dimensions;
    uint32_t *size_in_dimension;
    IDX_DATATYPE datatype;
} IDX_File;

typedef struct {
    uint8_t value;
    uint8_t data[D_WIDTH * D_HEIGHT];
} Digit;

void test(void);

#endif /* PARSE_MNIST_H_ */
