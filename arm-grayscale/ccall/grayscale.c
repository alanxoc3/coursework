#include <unistd.h> // For read, write and lseek
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>     // For open
#include <sys/types.h> // For open

#define PIX_OFF_BIT_OFF 10L

void* malloc(size_t size) {
	void * p;
	p = sbrk(0);
	if (sbrk(size) == (void*)-1)
		return NULL;
	return p;
}

int main(int argc, char ** argv) {
	int img = open("img.bmp", O_RDWR); // Open for r+w.

	// TESTING
	unsigned long x = lseek(img, 0, SEEK_END);
	unsigned long y = lseek(img, 0, SEEK_END);
	lseek(img, 0, SEEK_SET);
	printf("IT IS: %lu, %lu\n", x, y);
	printf("printing: %d\n", MAP_FIXED);

	int fileLen = y;
	
	unsigned int pixelDataOffset = 0;
	lseek(img, PIX_OFF_BIT_OFF, SEEK_SET);
	read(img, &pixelDataOffset, sizeof(unsigned int));

	lseek(img, pixelDataOffset, SEEK_SET); // Reset to where the offset is.

	unsigned int pix_len = fileLen - pixelDataOffset;

	unsigned char* fileMem = malloc(pix_len); // Allocate the pixels.
	read(img, fileMem, pix_len);

	int i;
	for (i = 0; i < pix_len; i += 3) {
		int average = (fileMem[i] + fileMem[i+1] + fileMem[i+2]) / 3;
		fileMem[i]   = (unsigned char) average;
		fileMem[i+1] = (unsigned char) average;
		fileMem[i+2] = (unsigned char) average;
	}

	lseek(img, pixelDataOffset, SEEK_SET); // Reset to where the offset is.
	write(img, fileMem, pix_len);

	close(img);

	return 0;
}
