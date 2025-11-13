#include "parse_mnist.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static IDX_File mnist_image_file;
static IDX_File mnist_label_file;

static const char *get_datatype_string(uint8_t type)
{
    switch (type) {
    case IDX_DATATYPE_UBYTE: return "unsigned byte"; break;
    case IDX_DATATYPE_BYTE: return "byte"; break;
    case IDX_DATATYPE_SHORT: return "short"; break;
    case IDX_DATATYPE_INT: return "int"; break;
    case IDX_DATATYPE_FLOAT: return "float"; break;
    case IDX_DATATYPE_DOUBLE: return "double"; break;
    default: return "error"; break;
    };
}

static uint32_t lendian32(uint8_t b[4])
{
    return (uint32_t) (b[0] << 24) | (b[1] << 16)
        | (b[2] << 8) | b[3];
}

static FILE *open_mnist_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        printf("ERROR: unable to open file %s\n", path);
    else
        printf("INFO: opened file \'%s\' successfully\n",
                path);
    return f;
}

static bool read_mnist_header(const char *path, IDX_File *file)
{
    int i;
    size_t ret;
    uint8_t b[4];
    uint32_t tmp;
    const char *datatype;
    file->fp = open_mnist_file(path);

    /* read magic number */
    ret = fread(&b, 1, 4, file->fp);
    if (ret != array_size(b)) {
        printf("ERROR: unable to read file header\n");
        return false;
    } 

    /* read datatype */
    datatype = get_datatype_string(b[2]);
    file->datatype = b[2];
    printf("INFO: using datatype %x: %s\n",file->datatype, datatype);

    /* read array dimensions */
    file->dimensions = b[3];
    printf("INFO: data presented in %d dimensions\n", file->dimensions);

    /* read array dimension sizes */
    file->size_in_dimension = malloc(sizeof(uint32_t) * file->dimensions);
    for (i = 0; i < file->dimensions; i++) {
        ret = fread(&b, 1, 4, file->fp);
        if (ret != array_size(b)) {
            printf("ERROR: unable to read dimension size %i\n", i);
            return false;
        }
        file->size_in_dimension[i] = lendian32(b);
        printf("INFO: size in dimension %i: %i\n", i + 1, file->size_in_dimension[i]);
    }

    putchar('\n');
    return true;
}

static void cleanup(void)
{
    free(mnist_image_file.size_in_dimension);
    free(mnist_label_file.size_in_dimension);
    fclose(mnist_image_file.fp);
    fclose(mnist_label_file.fp);
}

void test(void)
{
    read_mnist_header("./assets/train-images-idx3-ubyte",
            &mnist_image_file);  
    read_mnist_header("./assets/train-labels-idx1-ubyte",
            &mnist_label_file);  
    cleanup();
}
