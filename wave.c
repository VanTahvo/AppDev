#include <stdio.h>
#include "wave.h"
#include <math.h>
#include "screen.h"

// function definition
void printID(char s[]){
	int i;
	for(i=0; i<4; i++) putchar(s[i]);
	printf("\n");
}

// printID and fillID are so-called local functions because they are merely used by
// the functions in this file/module
void fillID(char *d, const char s[]){
	int i;
	for(i=0; i<4; i++) *d++=s[i];
}

void testTone(int f, double d){
	WAVHDR h;
	FILE *fp;
	int i;
	short int sample;

	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.Subchunk1ID, "fmt ");
	fillID(h.Subchunk2ID, "data");
	// chunksize will be declared later
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = SAMPLE_RATE*h.NumChannels*(h.BitsPerSample/8);
	h.BlockAlign = h.NumChannels*h.BitsPerSample/8;
	h.Subchunk2Size = h.ByteRate * d;
	h.ChunkSize = h.Subchunk2Size + 36;
	fp = fopen("testtone.wav", "w");
	fwrite(&h, sizeof(h), 1, fp);
	for(i=0; i<SAMPLE_RATE*d; i++){
		sample = 32767*sin(2*PI*f*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1, fp);
	}
	fclose(fp);
	printf("Test tone created!\n");
}

void dispWAVHDR(WAVHDR h){
	double duration;

	duration = (double)h.Subchunk2Size/h.ByteRate;

#ifdef DEBUG
	printf("Chunk ID: "); printID(h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	printf("Format: "); printID(h.Format);
	printf("Subchunk1 ID: "); printID(h.Subchunk1ID);
	printf("Subchuck1 size: %d\n", h.Subchunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Number of Channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits / Sample: %d\n", h.BitsPerSample);
	printf("Subchunk2 ID: %d\n"); printID(h.Subchunk2ID);
	printf("Subchuck2 size: %d\n", h.Subchunk2Size);
	duration = (double)h.Subchunk2Size/h.ByteRate;
	printf("Duration: %.3f sec\n", duration);
#else
	gotoXY(1,1); setFGcolor(RED); printf("[%.2f]", duration);
	gotoXY(1,10); setFGcolor(CYAN); printf("[%d bits/s]", h.BitsPerSample);
	gotoXY(1,30); setFGcolor(YELLOW); printf("[%d sps]", h.SampleRate);
	resetColors();
	fflush(stdout);
#endif
}

void dispWAVdata(short int s[]){
	int i, j;
	double sum200, rms200;

	for(i=0; i<80; i++){
		sum200 = 0.0;
		for(j=0; j<SAMPLE_RATE/80; j++){
			sum200 += (*s)*(*s);
			s++;
		}
		rms200 = sqrt(sum200/200);
#ifdef DEBUG	// conditional compiling
		printf("%2d: %10.2f ", i, rms200);
#else
		// display vertical bars
		displayBar(i+1, rms200);
#endif
	}
}
