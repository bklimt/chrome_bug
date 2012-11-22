
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "disk.h"
#include "pcx.h"

int disk_frame = 1290;
PCX buffer("images/back_hd.pcx");

void vga_init() {
}

int vga_setmode(unsigned char mode) {
  return 0;
}

void PutPixel(unsigned int x, unsigned int y, unsigned char color) {
  if (x >= 0 && x < buffer.width() && y >= 0 && y < buffer.height()) {
    buffer.SetPixel(x, y, color);
  }
}

void Flip() {
  char* filename = strdup("output/frame-XXXXXXXX.pcx");
  sprintf(filename, "output/frame-%08d.pcx", disk_frame--);
  buffer.Write(filename);
  free(filename);
}

void WairRetrace() {
}

void GetPaletteColor(unsigned char color,
                     unsigned char* r,
                     unsigned char* g,
                     unsigned char* b) {
  *r = buffer.palette(color, 0);
  *g = buffer.palette(color, 1);
  *b = buffer.palette(color, 2);
}

void SetPaletteColor(unsigned char color,
                     unsigned char r,
                     unsigned char g,
                     unsigned char b) {
  buffer.SetPalette(color, 0, r << 2);
  buffer.SetPalette(color, 1, g << 2);
  buffer.SetPalette(color, 2, b << 2);
}
                 
// Returns a random integer in [0, max).
int randint(int n) {
  return random() % n;
}
