# arm-grayscale

## About
An ARM-assembly project that converts bitmap images to grayscale without C
libraries.

The images are read with Linux system calls in order to bypass using C
libraries. Specifically the system calls used are:
* **MMAP2**
* **MUNMAP**
*  **OPEN**
* **READ**
* **LSEEK**
* **CLOSE**
* **EXIT**

Here are some good websites that helped with this little side project.
* [Simplified Windows BMP File Format Specification](http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm)
* [BMP Image Format](http://paulbourke.net/dataformats/bmp/)
* [Linux ARM System Calls](https://w3challs.com/syscalls/?arch=arm_thumb)

## Building
This project has only been tested on a Raspberry Pi 2 Model B running Raspbian
using the `4.1.13-v7+ #826` kernel. In order to compile, simply run the
Makefile located in one of the folders. Here is a list of folders along with
their descriptions.

```
ccall        - C grayscale converter using C-wrappers for system calls.
cfopen       - C grayscale converter using fopen and a program that spews out Bitmap information.
final/gray   - ARM grayscale bitmap image converter.
final/hues   - ARM hue-shift bitmap image manipulator.
final/invert - ARM invert bitmap image manipulator.
images       - The test images that were used: Obama, Trump, Mountain, and Cat.
```
