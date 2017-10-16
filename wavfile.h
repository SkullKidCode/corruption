#ifndef WAVFILE_H
#define WAVFILE_H

#include <stdio.h>

FILE * wavfile_open( const char *filename );
void wavfile_close( FILE *file );

#define WAVFILE_SAMPLES_PER_SECOND 44100

#endif