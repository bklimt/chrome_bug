
#include <vga.h>
#include <vgagl.h>
#include <unistd.h>

void PutPixel(unsigned int x, unsigned int y, unsigned char color);

unsigned char GetPixel(unsigned int x, unsigned int y);

void SetPaletteColor(unsigned char color,
                     unsigned char red,
                     unsigned char green,
                     unsigned char blue);

void Flip();

// Returns a random integer in [0, max).
int randint(int n);
