#include "parse_mnist.h"

int main(void)
{
    Digit *d;
    d = read_mnist_files("./assets/train-images-idx3-ubyte", "./assets/train-labels-idx1-ubyte");
    render_mnist_digits_console(d, 0, 300);
    cleanup(d);
    return 0;
}
