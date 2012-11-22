
#ifndef __PCX_H__
#define __PCX_H__

class PCX {
 public:
  PCX(char *filename) { Read(filename); }
  ~PCX();

  void Read(char *filename);
  void Write(char *filename);

  unsigned int width() const { return width_; }
  unsigned int height() const { return height_; }

  unsigned char palette(int color, int channel) const {
    return palette_[color][channel];
  }

  void SetPalette(int color, int channel, unsigned char value) {
    palette_[color][channel] = value;
  }

  void SetPixel(int x, int y, unsigned char color) {
    image_[x + y * width_] = color;
  }

  unsigned char pixel(int x, int y) const {
    return image_[x + y * width_];
  }

  void LoadPalette();

 private:
  void ReadHeader(unsigned char *pcx_data, int size);
  void ReadPalette(unsigned char *pcx_data, int size);
  void ReadImageData(unsigned char *pcx_data, unsigned int size);

  void WriteHeader(FILE *f);
  void WritePalette(FILE* f);
  void WriteImageData(FILE* f);

  unsigned int width_, height_;
  unsigned int bytes_per_line_;
  unsigned char *image_;
  unsigned char palette_[256][3];
};

void DrawPCX(const PCX &pcx, const PCX *const mask, int x, int y, float direction);

#endif

