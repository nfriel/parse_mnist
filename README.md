### MNIST file parser

- I included the unzipped mnist files in my repo, but you can find the mirrors [here](https://github.com/cvdfoundation/mnist).
- The included build script uses clang, but should work identically with gcc.  

### To test:
1. Navigate into your directory of choice and clone my repository
```console
cd ~/your_folder
git clone https://github.com/nfriel/parse_mnist
cd parse_mnist
```
2. Test the program using the provided build script
```console
chmod +x build.sh
./build.sh
```

### To use in your project:
1. Clone the parse_mnist repo
```console
git clone https://github.com/nfriel/parse_mnist
cd parse_mnist
```
2. Move the parse_mnist.c and the parse_mnist.h files into your project directory
```console
mv parse_mnist.c your_project_src_dir/
mv parse_mnist.h your_project_inc_dir/
```
3. Either use the included mnist files in the assets folder of my repo or download it from elsewhere
4. Use the read_mnist_files function to load image and label data into a Digit array
```c
#include "parse_mnist.h"

int main(void)
{
	Digit *digits;
	digits = read_mnist_files("path/to/image/file", "path/to/label/file");
}
```
5. Either access the image and label data directly, or test by printing out images and corresponding labels to the console
```c
#include "parse_mnist.h"

int main(void)
{
	Digit *digits;
	digits = read_mnist_files("path/to/image/file", "path/to/label/file");

	/* Get the value of the digit 0-9 */
	digits[x].value;

	/* Access the image array */
	digits[x].data[y];
}
```

```c
#include "parse_mnist.h"

int main(void)
{
	Digit *digits;
	digits = read_mnist_files("path/to/image/file", "path/to/label/file");

	/* Render digits from index x to y to the console */
	render_mnist_digits_console(digits, x, y);
}
```
6. Free allocated data
```c
#include "parse_mnist.h"

int main(void)
{
	Digit *digits;
	digits = read_mnist_files("path/to/image/file", "path/to/label/file");
	
	/* The rest of your code */
	
	cleanup(digits);
}
```


