#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wavfile.h"

int main (int argc, char *argv[]) {
	if (argc != 4) {
	printf("Usage: %s <input_file> <output_filename> <output_folder>\n", argv[0]);
	exit(0);
	}
	
	char end_char = argv[3][strlen(argv[3]) - 1];							/* Check output file path ends in '/' */

	if (end_char == '/') {
		;
	}
	else {
		printf("Error: File path missing \"/\" at the end\n");
		printf("Usage: %s <input_file> <output_filename> <output_folder>\n", argv[0]);
		exit(0);
	}
	
	FILE * fptr;
	char * extension = ".wav";
	char * file_path = strncat(argv[3], argv[2], strlen(argv[2]));
	char * full_file_path = strncat(file_path, extension, 4);			/* Creates full file path for output */
	char ch;
	long n = 0;
	long file_size;
	

	fptr = fopen(argv[1], "rb");   							/* Opens input file */
	if (fptr == NULL) {
		perror("No input file supplied dude");
		exit(0);
	}
	
	FILE * wav_file = wavfile_open(full_file_path);				/* Opens a file and writes the wav header */
	if (wav_file == NULL) {
		perror("Couldn't create sound file for writing");
		exit(0);
	}
	
	fseek(fptr, 0, SEEK_END);								/* Gets input file size */
	file_size = ftell(fptr);
	rewind(fptr);
	
	do {
		ch = fgetc(fptr);
		fputc(ch, wav_file);			/* Copy over to new file */
		n++;
	} while (n < file_size);
	
	wavfile_close(wav_file);			/* Finishes writing header to new file */
}