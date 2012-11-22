
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msdos.h"

/*------------------------------------------------------------------------*/

unsigned char far *video_buffer = (unsigned char far *)0xA0000000L;
unsigned char *back_buffer;

/*------------------------------------------------------------------------*/

void vga_init() {
  back_buffer = (unsigned char*)malloc(320 * 200);
  if (back_buffer == NULL) {
    fprintf(stderr, "Unable to allocate back buffer.\n");
    exit(-1);
  }
}

/*------------------------------------------------------------------------*/

void PutPixel(unsigned int x, unsigned int y, unsigned char color) {
  unsigned int offset = (y << 8) + (y << 6) + x;
	back_buffer[offset] = (unsigned char)color;
}

/*------------------------------------------------------------------------*/

unsigned char GetPixel(unsigned int x, unsigned int y) {
  unsigned int offset = (y << 8) + (y << 6) + x;
	return back_buffer[offset];
}

/*------------------------------------------------------------------------*/

void Flip() {
  memcpy(video_buffer, back_buffer, 64000);
}

/*------------------------------------------------------------------------*/

void vga_setmode(unsigned char mode) {
  _AH = 0;
  _AL = (unsigned char)mode;
  geninterrupt(0x10);
}

/*------------------------------------------------------------------------*/

void WaitRetrace() {
	while (!(inp(0x3DA) & 0x08)) {}
	while (inp(0x3DA) & 0x08) {}
}

/*------------------------------------------------------------------------*/

void GetPaletteColor(unsigned char color, 
                     unsigned char* r,
                     unsigned char* g,
                     unsigned char* b) {
	outp(0x3C7, color);
	*r = (unsigned char)inp(0x3C9);
	*g = (unsigned char)inp(0x3C9);
	*b = (unsigned char)inp(0x3C9);
}

/*------------------------------------------------------------------------*/

void SetPaletteColor(unsigned char ColorNo, 
                        unsigned char r,
                        unsigned char g,
                        unsigned char b) {
	outp(0x3C8, ColorNo);
	outp(0x3C9, r);
	outp(0x3C9, g);
	outp(0x3C9, b);
}

/*------------------------------------------------------------------------*/

void BlackPalette() {
	int i;
	for (i=0; i<256; ++i)	{
		SetPaletteColor(i, 0, 0, 0);
	}
}

/*------------------------------------------------------------------------*/

void FadeUp(unsigned char palette[256][3]) {
	int i, j;
	unsigned char temp[3];
	for (i=0; i<64; ++i) {
		WaitRetrace();
		for (j=0; j<256; ++j) {
			GetPaletteColor(j, &temp[0], &temp[1], &temp[2]);
			if (temp[0] > palette[j][0]) temp[0]--;
			if (temp[1] > palette[j][1]) temp[1]--;
			if (temp[2] > palette[j][2]) temp[2]--;
			if (temp[0] < palette[j][0]) temp[0]++;
			if (temp[1] < palette[j][1]) temp[1]++;
			if (temp[2] < palette[j][2]) temp[2]++;
			SetPaletteColor(j, temp[0], temp[1], temp[2]);
		}
	}
}

/*------------------------------------------------------------------------*/

void FadeDown() {
	int i, j;
	unsigned char temp[3];
	for (i=0; i<64; ++i) {
		WaitRetrace();
		for (j=0; j<256; ++j) {
			GetPaletteColor(j, &temp[0], &temp[1], &temp[2]);
			if (temp[0] > 0) temp[0]--;
			if (temp[1] > 0) temp[1]--;
			if (temp[2] > 0) temp[2]--;
			SetPaletteColor(j, temp[0], temp[1], temp[2]);
		}
	}
}

/*------------------------------------------------------------------------*/

// Returns a random integer in [0, max).
int randint(int n) {
  int answer = ((int)drand(n)) - 1;
  if (answer < 0 || answer >= n) {
    vga_setmode(TEXT);
    fprintf(stderr, "drand(%d) -> %d, which is out of the range [1, %d]\n", n, answer + 1, n);
    exit(-1);
  }
  return answer;
}

