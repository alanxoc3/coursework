.arch armv7-a   // Gives you something.
.cpu cortex-a7  // udiv and sdiv - division unsigned and signed.
.fpu neon-vfpv4 // Allows floating point.
.set STDOUT, 1  // For writing to screen.

// SYSTEM CALLS
.set EXIT,  1
.set READ,  3
.set WRITE, 4
.set OPEN,  5
.set CLOSE, 6
.set LSEEK, 19
.set MUNMAP, 91
.set MMAP2, 192

// OPEN FLAGS
.set O_RDWR, 2

// MMAP FLAGS
.set PROC_READ, 1
.set PROC_WRITE, 2

.set MAP_SHARED,    1
.set MAP_PRIVATE,   2
.set MAP_FIXED,     16
.set MAP_ANONYMOUS, 32

// SEEK INFO
.set SEEK_SET, 0
.set SEEK_END, 2

// BITMAP INFO
.set PIX_OFF_BIT_OFF, 10

.data
pointer: // For the allocation
	.word 0
imageOffset:
	.word -1
badParameters:
	.ascii "Usage: hues [image.bmp]\n"
badFile:
	.ascii "Umm, that filename was invalid.\n"

.text
.global _start
_start:

commandLine: // Read parameter.
	pop {r0, r1} // num of args, location of executable
	teq r0, #2 // Want two parameters.
	beq open
	b errorBadParameters


open:
	// Get the argument.
	pop {r0}

	// Open the image.
	mov r7, #OPEN
	// ldr r0, =filename
	mov r1, #O_RDWR
	svc #0 // -2 is returned on error.

	cmn r0, #2 // Tests
	beq errorBadFile

	mov r10, r0 // Save the file index.

getFileSize:
	mov r7, #LSEEK
	mov r0, r10       // The image id.
	mov r1, #0        // The offset.
	mov r2, #SEEK_END // The starting point.
	svc #0            // Call it.

	mov r11, r0 // Save the size of the file.

jumpToOff:
	mov r7, #LSEEK
	mov r0, r10              // The image id.
	mov r1, #PIX_OFF_BIT_OFF // The offset.
	mov r2, #SEEK_SET        // The starting point.
	svc #0                   // Call it.

readImageOffset:
	mov r7, #READ
	mov r0, r10          // The image id.
	ldr r1, =imageOffset // The location where the offset is to be stored.
	mov r2, #4           // An integer is 4 bytes.
	svc #0

allocate:
	mov r7, #MMAP2
	mov r0, #0          // Hint to kernel where to map file. Usually 0.
	mov r1, r11         // Length to allocate (just the image size).
	mov r2, #(PROC_READ | PROC_WRITE) // Be able to read and write image.
	mov r3, #MAP_SHARED // shared = changes the file, fixed = find space for whole file.
	mov r4, r10         // The image id.
	mov r5, #0          // Offset of file to load.
	svc #0

	ldr r1, =pointer // Storing the pointer
	str r0, [r1]     // location.

loopSetup:
	ldr r2, =imageOffset // Image offset is the counter.
	ldr r2, [r2]
	sub r3, r11, r2 // pixoff = image_size - image_offset.
	add r0, r0, r2  // Load offset.

	mov r6, #0 // starting condition
	mov r7, r3 // ending condition
	mov r5, #3 // Divider is 3 for average

	push { r0-r7 }

// Loops through all the pixels.
loop:
	ldrb r1, [r0, r6] // Blue
	add r6, r6, #1
	ldrb r2, [r0, r6] // Green
	add r6, r6, #1
	ldrb r3, [r0, r6] // Red
	sub r6, #2

	strb r3, [r0, r6]
	add r6, r6, #1
	strb r1, [r0, r6]
	add r6, r6, #1
	strb r2, [r0, r6]
	add r6, r6, #1

	cmp r6, r7
	blt loop
	pop { r0-r7 }

// Order of unmap and close may be switched if wanted
unmap: // PARAMS: pointer, length
	mov r7, #MUNMAP
	ldr r0, =pointer
	ldr r0, [r0]
	mov r1, r11
	svc #0

close: // PARAMS: fileID
	mov r7, #CLOSE  // System call.
	mov r0, r10     // Image id is a parameter.
	svc #0          // Call it.

exit:
	mov r7, #EXIT
	svc #0

// Error methods...
errorBadParameters:
	mov r0, #STDOUT
	ldr r1, =badParameters
	mov r2, #24
	mov r7, #WRITE
	svc #0
	b exit

errorBadFile:
	mov r0, #STDOUT
	ldr r1, =badFile
	mov r2, #32
	mov r7, #WRITE
	svc #0
	b exit
