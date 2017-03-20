/* Usually there are three parts in header file:
 * the first pasrt is data structure definition,
 * the second part is list of defined constants,
 * the third part is a list of function prototypes */

// data structure definition
typedef struct{
	char ChunkID[4];
	int ChunkSize;
	char Format[4];
	char Subchunk1ID[4];
	int Subchunk1Size;
	short int AudioFormat;
	short int NumChannels;
	int SampleRate;
	int ByteRate;
	short int BlockAlign;
	short int BitsPerSample;
	char Subchunk2ID[4];
	int Subchunk2Size;
}WAVHDR;

// constant definitions
//#define DEBUG 1		// this file makes conditional compiling
#define SAMPLE_RATE 16000
#define PI 3.1415926

// function prototypes
void dispWAVHDR(WAVHDR);
void testTone(int f, double d);
void dispWAVdata(short int s[]);
