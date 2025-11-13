#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE 28

typedef struct {
    uint8_t data[ARRAY_SIZE * ARRAY_SIZE];
    uint8_t label;
} Character;

uint32_t lendian32(uint8_t b[4])
{
    return (uint32_t) (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

void get_magic_number(FILE *f)
{
    uint8_t b[4];
    fread(b, 1, 4, f);

    if (b[0] == 0 && b[1] == 0) {
        printf("INFO: byte 1 & 2 = 0\n");
    } else {
        printf("ERROR: byte 1 & 2 != 0\n");
        return;
    }

    printf("INFO: data type: ");
    switch (b[2]) {
    case 0x08:
        printf("unsigned byte\n");
        break;
    case 0x09:
        printf("signed byte\n");
        break;
    case 0x0B:
        printf("short\n");
        break;
    case 0x0C:
        printf("int\n");
        break;
    case 0x0D:
        printf("float\n");
        break;
    case 0x0E:
        printf("double\n");
        break;
    }

    printf("INFO: %i dimensional data\n", b[3]);
}

uint32_t get_number(FILE *f)
{
    uint8_t b[4];
    fread(b, 1, 4, f);
    return (lendian32(b));
}

Character get_character(FILE *f, FILE *l)
{
    int i;
    Character c;
    for (i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++) {
        fread(&c.data[i], 1, 1, f);
        fread(&c.label, 1, 1, l);
    }
    return c;
}

void print_character(Character c)
{
    int i;
    printf("%d:\n", c.label);
    for (i = 0; i < ARRAY_SIZE * ARRAY_SIZE; i++) {
        if (c.data[i] > 100) printf("##"); else printf("  ");
        if (i % ARRAY_SIZE == 0) putchar('\n');
    }
    putchar('\n');
}

int main(void)
{
    int i;
    Character carray[1000];
    FILE *f = fopen("./assets/train-images-idx3-ubyte", "r");
    FILE *l= fopen("./assets/train-labels-idx1-ubyte", "r");
    if (f == NULL) {
        printf("ERROR: unable to open mnist image file\n");
        return -1;
    }
    if (l == NULL) {
        printf("ERROR: unable to open mnist label file\n");
        return -1;
    }

    get_magic_number(f);
    get_magic_number(l);

    printf("INFO: using an %i array\n", get_number(l));
    printf("INFO: using an %ix%ix%i array\n", get_number(f), get_number(f), get_number(f));

    for (i = 0; i < 1000; i++) {
        carray[i] = get_character(f, l);
    }

    for (i = 0; i < 1000; i++) {
        print_character(carray[i]);
    }


    fclose(f);
    fclose(l);
    return 0;
}
