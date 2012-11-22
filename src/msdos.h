
#define G320x200x256 0x13
#define TEXT 0x03
#define CLOCKS_PER_SEC CLK_TCK

/*------------------------------------------------------------------------*/

void vga_init();
void vga_setmode(unsigned char mode);

void PutPixel(unsigned int x, unsigned int y, unsigned char color);

unsigned char GetPixel(unsigned int x, unsigned int y);

void Flip();

void WaitRetrace();

void GetPaletteColor(unsigned char ColorNo, 
                     unsigned char* r,
                     unsigned char* g,
                     unsigned char* b);

void SetPaletteColor(unsigned char ColorNo, 
                     unsigned char r,
                     unsigned char g,
                     unsigned char b);

void BlackPalette();
void FadeUp(unsigned char palette[256][3]);
void FadeDown();

// Returns a random integer in [0, max).
int randint(int n);
