#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Attribute Packed puts all things next to each other.
typedef struct __attribute__((__packed__)) {
    unsigned char fileMarker1; // B
    unsigned char fileMarker2; // M
    unsigned int   bfSize;     // File size in bytes.
    uint16_t unused1;          // These are just here
    uint16_t unused2;          // for future possibilities.
	 unsigned int   imageDataOffset; // Offset from start of file to pixel
                                    // section.
} FILEHEADER;

typedef struct  __attribute__((__packed__)) {
    unsigned int   biSize; // The header size must be at least 40
    int            width;  // Width of image in pixels.
    int            height; // Height of image. Bottom to top.
    uint16_t planes;       // Always 1, number of image planes.
    uint16_t bitPix;       // Bits per pixel, usually 24 (3 bytes).
    unsigned int   biCompression; // 0 means uncompressed.
    unsigned int   biSizeImage;   // Size of image, optional if uncompressed.
    int            biXPelsPerMeter; // The num of pixels in a meter,
    int            biYPelsPerMeter; // these aren't always used.
    unsigned int   biClrUsed;       // These are only important with
    unsigned int   biClrImportant;  // lower depth images.
} INFOHEADER;

typedef struct __attribute__((__packed__)) {
    unsigned char  b;
    unsigned char  g;
    unsigned char  r;
} IMAGE;  

int main(int argc, char ** argv) {
    FILEHEADER fh;
    INFOHEADER ih;
    IMAGE im;

    FILE *img = fopen("img.bmp", "rb");
    fseek(img, 0L, SEEK_END);
    int fileLen = ftell(img);

    fseek(img, 0L, SEEK_SET); // Reset to beginning.

    fread(&fh, 1, sizeof(FILEHEADER), img); // Read file header
    fread(&ih, 1, sizeof(INFOHEADER), img); // Read image header

    // This will move to where the pixel data actually starts!
	 // image, offset, SEEK_SET means offset is relative to start of file.
    fseek(img, fh.imageDataOffset, SEEK_SET); // To pixel data.
    // Read the first pixel (lower left corner).
    fread(&im, 1, sizeof(IMAGE), img);

	 printf("fM1 = %c, fM2 = %c, bfS = %u, un1 = %hu, un2 = %hu, iDO = %u\n",
		fh.fileMarker1, fh.fileMarker2, fh.bfSize, fh.unused1, fh.unused2,
		fh.imageDataOffset);

	 printf("biSize = %d, w = %d, h = %d, planes = %u, bitPix = %u,\n"
           "biCompression = %u, biSizeImage = %u, biXPelsPerMeter =  %d,\n"
           "biYPelsPerMeter = %d, biClrUsed = %u, biClrImportant = %u\n",
    ih.biSize, ih.width, ih.height, ih.planes, ih.bitPix, ih.biCompression,
    ih.biSizeImage, ih.biXPelsPerMeter, ih.biYPelsPerMeter, ih.biClrUsed,
    ih.biClrImportant);

    printf("w = %d, h = %d\n", ih.width, ih.height);

    printf("R: %u, G: %u, B: %u\n", im.r, im.g, im.b);

    printf("LEN IN BYTES = %d\n", fileLen);

    return 0;
}
