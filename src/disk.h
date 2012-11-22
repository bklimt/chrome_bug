
#ifndef __DISK_H__
#define __DISK_H__

#define G320x200x256 0
#define TEXT 1

void vga_init();
int vga_setmode(unsigned char mode);
void PutPixel(unsigned int x, unsigned int y, unsigned char color);
void Flip();
void WairRetrace();
void GetPaletteColor(unsigned char ColorNo, 
                     unsigned char* r,
                     unsigned char* g,
                     unsigned char* b);

void SetPaletteColor(unsigned char ColorNo, 
                     unsigned char r,
                     unsigned char g,
                     unsigned char b);
                 
// Returns a random integer in [0, max).
int randint(int n);

#endif
