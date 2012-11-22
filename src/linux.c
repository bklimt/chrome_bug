
#include <stdlib.h>

#include "linux.h"

void PutPixel(unsigned int x, unsigned int y, unsigned char color) {
  vga_setcolor(color);
  vga_drawpixel(x, y);
}

unsigned char GetPixel(unsigned int x, unsigned int y) {
  return 0;
}

void SetPaletteColor(unsigned char color,
                     unsigned char red,
                     unsigned char green,
                     unsigned char blue) {
  gl_setpalettecolor(color, red, green, blue);
}

void Flip() {
}

// Returns a random integer in [0, max).
int randint(int n) {
  return random() % n;
}

