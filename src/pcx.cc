
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"
#include "pcx.h"

void PCX::LoadPalette() {
  int c;
  for (c = 0; c < 256; ++c) {
     SetPaletteColor(c,
                     palette_[c][0] >> 2,
                     palette_[c][1] >> 2,
                     palette_[c][2] >> 2);
  }
}

void PCX::ReadHeader(unsigned char *pcx_data, int size) {
  unsigned int x_min, x_max, y_min, y_max;

  if (size < 128) {
    fprintf(stderr, "PCX file too small to contain a header.\n");
    exit(-1);
  }

  if (pcx_data[1] != 5) {
    fprintf(stderr, "Only PCX 5 (not %d) files are supported.\n", pcx_data[1]);
    exit(-1);
  }

  if (pcx_data[2] != 1) {
    fprintf(stderr, "Unknown PCX encoding: %d.\n", pcx_data[2]);
    exit(-1);
  }

  if (pcx_data[3] != 8) {
    fprintf(stderr, "Only 8-bit PCX files are supported (not %d-bit).\n",
            pcx_data[3]);
    exit(-1);
  }

  if (pcx_data[65] != 1) {
    fprintf(stderr, "Only palette PCX files are supported (not %d plane).\n",
            pcx_data[65]);
    exit(-1);
  }

  x_min = pcx_data[4] + (pcx_data[5] << 8);
  y_min = pcx_data[6] + (pcx_data[7] << 8);
  x_max = pcx_data[8] + (pcx_data[9] << 8);
  y_max = pcx_data[10] + (pcx_data[11] << 8);
  if (x_min != 0) {
    fprintf(stderr, "PCX header: x_min == %d (not 0).\n", x_min);
    exit(-1);
  }
  if (y_min != 0) {
    fprintf(stderr, "PCX header: y_min == %d (not 0).\n", y_min);
    exit(-1);
  }
  /*
  if (x_max != 319) {
    fprintf(stderr, "PCX header: x_max == %d [%x] (not 319).", x_max);
    exit(-1);
  }
  if (y_max != 199) {
    fprintf(stderr, "PCX header: y_max == %d [%x] (not 199).", y_max);
    exit(-1);
  }
  */

  width_ = (x_max - x_min) + 1;
  height_ = (y_max - y_min) + 1;

  bytes_per_line_ = pcx_data[66] + (pcx_data[67] << 8);
  /*if (bytes_per_line_ != x_max + 1) {
    fprintf(stderr,
        "PCX header: bytes_per_line_ != x_min + 1 (%d vs %d).\n",
            bytes_per_line_, x_max + 1);
    exit(-1);
  }*/
}

void PCX::WriteHeader(FILE *f) {
  unsigned char header[128];
  memset(header, 0, 128);

  /* Byte      Item          Size   Description/Comments 
      0         Manufacturer 1      Constant Flag, 10 = ZSoft .pcx */
  header[0] = 10;

  /*  1         Version      1      Version information 
                                    0 = Version 2.5 of PC Paintbrush 
                                    2 = Version 2.8 w/palette information 
                                    3 = Version 2.8 w/o palette information 
                                    4 = PC Paintbrush for Windows(Plus for
                                        Windows uses Ver 5) 
                                    5 = Version 3.0 and > of PC Paintbrush
                                        and PC Paintbrush +, includes
                                        Publisher's Paintbrush . Includes
                                        24-bit .PCX files */
  header[1] = 5;
 
  /*  2         Encoding      1     1 = .PCX run length encoding */
  header[2] = 1;

  /*  3         BitsPerPixel  1     Number of bits to represent a pixel
                                      (per Plane) - 1, 2, 4, or 8 */
  header[3] = 8;

  /*  4         Window        8     Image Dimensions: Xmin,Ymin,Xmax,Ymax */
  header[4] = 0;
  header[5] = 0;
  header[6] = 0;
  header[7] = 0;
  header[8] = (unsigned char)((width_ - 1) & 0x00FF);
  header[9] = (unsigned char)(((width_ - 1) >> 8) & 0x00FF);
  header[10] = (unsigned char)((height_ - 1) & 0x00FF);
  header[11] = (unsigned char)(((height_ - 1) >> 8) & 0x00FF);

  /* 12         HDpi          2     Horizontal Resolution of image in DPI* */
  header[12] = (unsigned char)(300 & 0x00FF);
  header[13] = (unsigned char)((300 >> 8) & 0x00FF);

  /* 14         VDpi          2     Vertical Resolution of image in DPI* */
  header[14] = (unsigned char)(300 & 0x00FF);
  header[15] = (unsigned char)((300 >> 8) & 0x00FF);

  /* 16         Colormap     48     Color palette setting, see text */

  /* 64         Reserved      1     Should be set to 0. */
  header[64] = 0;

  /* 65         NPlanes       1     Number of color planes */
  header[65] = 1;

  /* 66         BytesPerLine  2     Number of bytes to allocate for a scanline
                                      plane.  MUST be an EVEN number.  Do NOT
                                      calculate from Xmax-Xmin. */
  header[66] = (unsigned char)(width_ & 0x00FF);
  header[67] = (unsigned char)((width_ >> 8) & 0x00FF);

  /* 68         PaletteInfo   2     How to interpret palette- 1 = Color/BW,
                                      2 = Grayscale (ignored in PB IV/ IV +) */
  header[68] = 1;
  header[69] = 0;

  /* 70         HscreenSize   2     Horizontal screen size in pixels. New field
                                      found only in PB IV/IV Plus */
  header[70] = (unsigned char)(640 & 0x00FF);
  header[71] = (unsigned char)((640 >> 8) & 0x00FF);

  /* 72         VscreenSize   2     Vertical screen size in pixels. New field
                                      found only in PB IV/IV Plus */
  header[72] = (unsigned char)(480 & 0x00FF);
  header[73] = (unsigned char)((480 >> 8) & 0x00FF);

  /* 74         Filler       54     Blank to fill out 128 byte header.  Set all
                                      bytes to 0 */

  fwrite(header, 1, 128, f);
}

void PCX::ReadPalette(unsigned char *pcx_data, int size) {
  int pcx_offset;
  int palette_offset;

  if (size < (256 * 3 + 1)) {
    fprintf(stderr, "PCX file too small to contain palette data.\n");
    exit(-1);
  }

  pcx_offset = size - (256 * 3 + 1);
  if (pcx_data[pcx_offset] != 12) {
    fprintf(stderr, "PCX file does not contain valid palette data.\n");
    exit(-1);
  }
  ++pcx_offset;

  for (palette_offset = 0;
       pcx_offset < size;
       pcx_offset += 3, ++palette_offset) {
    if (palette_offset >= 256) {
      fprintf(stderr, "Tried to write past end of palette.\n");
      exit(-1);
    }

    if (pcx_offset + 2 >= size) {
      fprintf(stderr, "Tried to read palette data past end of pcx file.\n");
      exit(-1);
    }

    palette_[palette_offset][0] = pcx_data[pcx_offset + 0];
    palette_[palette_offset][1] = pcx_data[pcx_offset + 1];
    palette_[palette_offset][2] = pcx_data[pcx_offset + 2];
  }
}

void PCX::WritePalette(FILE* f) {
  int i;
  fputc(12, f);
  for (i = 0; i < 256; ++i) {
    fputc(palette_[i][0], f);
    fputc(palette_[i][1], f);
    fputc(palette_[i][2], f);
  }
}

void PCX::ReadImageData(unsigned char *pcx_data, unsigned int size) {
  unsigned int x, y;
  unsigned int count;
  unsigned int pcx_offset = 128;

  // Allocate the image buffer.
  image_ = new unsigned char[width_ * height_];
  if (image_ == NULL) {
    fprintf(stderr, "Unable to allocate memory for %dx%d image.\n",
            width_, height_);
    exit(-1);
  }

  pcx_offset = 128;
  for (y = 0; y < height_; ++y) {
    for (x = 0; x < bytes_per_line_; ) {
      if (pcx_offset >= size) {
        fprintf(stderr, "PCX file too small for image data.\n");
        exit(-1);
      }
      if ((pcx_data[pcx_offset] & 0xC0) == 0xC0) {
        count = (pcx_data[pcx_offset++] & 0x3F);
        if (pcx_offset >= size) {
          fprintf(stderr, "Error decoding PCX file image data (no count).\n");
          exit(-1);
        }
        while (count-- > 0) {
          if (x < width_) {
            image_[x + y * width_] = pcx_data[pcx_offset];
          }
          if (x > bytes_per_line_) {
            int total_count = pcx_data[pcx_offset - 1] & 0x3F;
            int current_count = total_count - count;
            fprintf(stderr,
                    "Error decoding PCX file image data (too many reps).\n"
                    "row: %d\n"
                    "byte: %d\n"
                    "count: %d of %d\n"
                    "bytes_per_line: %d\n",
                    y, x, current_count, total_count, bytes_per_line_);
            exit(-1);
          }
          ++x;
        }
      } else {
        if (x < width_) {
          image_[x + y * width_] = pcx_data[pcx_offset];
        }
        ++x;
      }
      ++pcx_offset;
    }
    if (x != bytes_per_line_) {
      fprintf(stderr, "Error decoding PCX file image data (line too long).\n");
      exit(-1);
    }
  }
}

void PCX::WriteImageData(FILE* f) {
  for (unsigned int row = 0; row < height_; ++row) {
    for (unsigned int column = 0; column < width_; ++column) {
      // first, figure out how many times this repeats.
      int count = 1;
      unsigned char color = image_[column + width_ * row];
      while ((count < 0x3F) &&
             ((column + 1) < width_) &&
             (image_[column + 1 + width_ * row] == color)) {
        ++count;
        ++column;
      }
      if ((count > 1) || ((color & 0xC0) == 0xC0)) {
        fputc(0xC0 | count, f);
      }
      fputc(color, f);
    }
  }
}

void PCX::Read(char *filename) {
  FILE *f;
  long size;

  image_ = NULL;

  /* Read the file into buffer. */
  f = fopen(filename, "rb");
  if (f == NULL) {
    fprintf(stderr, "Unable to open %s.\n", filename);
    exit(-1);
  }
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  /*if (lsize > 64000) {
    fprintf(stderr, "File is too huge: %s.\n", filename);
    exit(-1);
  }*/
  fseek(f, 0, SEEK_SET);
  unsigned char *buffer = new unsigned char[size];
  if (fread(buffer, 1, size, f) != size) {
    fprintf(stderr, "Unable to read image file %s.\n", filename);
    exit(-1);
  }
  fclose(f);

  /* Interpret the header. */
  ReadHeader(buffer, size);

  /* Read in the palette. */
  ReadPalette(buffer, size);

  /* Read in the image data. */
  ReadImageData(buffer, size);

  /* Clean up. */
  delete[] buffer;

  if (image_ == NULL) {
    fprintf(stderr, "Creating PCX for %s failed somehow.\n", filename);
    exit(-1);
  }
}

void PCX::Write(char *filename) {
  FILE *f = fopen(filename, "wb");
  WriteHeader(f);
  WriteImageData(f);
  WritePalette(f);
  fclose(f);
}

PCX::~PCX() {
  delete[] image_;
}

void DrawPCX(const PCX &pcx, const PCX *const mask, int x, int y, float direction) {
  for (unsigned int i = 0; i < pcx.width(); ++i) {
    for (unsigned int j = 0; j < pcx.height(); ++j) {
      int px = x + (pcx.width() - 1) - i;
      int py = y + (pcx.height() - 1) - j;
      unsigned char color = pcx.pixel(i, j);
      if (mask != NULL) {
        unsigned char mask_color = mask->pixel(i, j);
        if (mask_color == 0) {
          continue;
        }
      }
      if (direction < 45 || direction >= 315) {
        // down
      } else if (direction < 135) {
        // right
        px = x + (pcx.height() - 1) - j;
        py = y + i;
      } else if (direction < 225) {
        // up
        px = x + i;
        py = y + j;
      } else if (direction < 315) {
        // left
        px = x + j;
        py = y + (pcx.width() - 1) - i;
      } else {
        vga_setmode(TEXT);
        fprintf(stderr, "Bad direction: %f\n", direction);
        exit(-1);
      }
      PutPixel(px, py, color);
    }
  }
}


