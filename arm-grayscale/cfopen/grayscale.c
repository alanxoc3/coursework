#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define PIX_OFF_BIT_OFF 10L

int main(int argc, char ** argv) {
	FILE *img = fopen("img.bmp", "r+");
	
	fseek(img, 0L, SEEK_END); // Get the length of the
	int fileLen = ftell(img); // file in bytes.
	
	unsigned int pixelDataOffset = 0;

	fseek(img, PIX_OFF_BIT_OFF, SEEK_SET); // Reset to where the offset is.
	fread(&pixelDataOffset, sizeof(unsigned int), 1, img);

	fseek(img, pixelDataOffset, SEEK_SET); // Reset to where the offset is.

	unsigned int pix_len = fileLen - pixelDataOffset;
	unsigned char* fileMem = malloc(pix_len); // Allocate the pixels.
	fread(fileMem, 1, pix_len, img);

	int i;
	for (i = 0; i < pix_len; i += 3) {
		int average = (fileMem[i] + fileMem[i+1] + fileMem[i+2]) / 3;
		fileMem[i]   = (unsigned char) average;
		fileMem[i+1] = (unsigned char) average;
		fileMem[i+2] = (unsigned char) average;
		//if (i % (3 * 3 * 3) == 0)
			//printf("AVERAGE: %u, %u, %u\n", fileMem[i],
													  //fileMem[i+1],
													  //fileMem[i+2]);
	}

	fseek(img, pixelDataOffset, SEEK_SET); // Reset to where the offset is.
	fwrite(fileMem, 1, pix_len, img);

	printf("Pixel Data Offset = %u\n", pixelDataOffset);
	printf("FILE LEN IN BYTES = %d\n", fileLen);
	printf("PIX  LEN IN BYTES = %d\n", pix_len);

	fclose(img);
	free(fileMem);

	return 0;
}
