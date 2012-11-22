
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "pcx.h"

/* Image List */

struct ImageNode {
  ImageNode(char *filename, char *mask_filename)
    : image(filename), mask(mask_filename), next(NULL) {}

  PCX image;
  PCX mask;
  ImageNode *next;
};

typedef ImageNode *ImageList;

void InitImageList(ImageList *list);
void AddImage_(ImageList *list, char *filename, char *mask_filename);
void FreeImageList(ImageList *list);

/* Sprite */

class Sprite {
 public:
  Sprite(char *filename, char *mask_filename,
         float x, float y, float direction);
  ~Sprite();

  void Draw();
  void NextImage();
  void FirstImage();
  void AddImage(char *filename, char *mask_filename) {
    AddImage_(&images_, filename, mask_filename);
  }

  PCX *GetCurrentImage();
  PCX *GetCurrentMask();
  int GetCurrentWidth();
  int GetCurrentHeight();

  float x;
  float y;
  float direction;  /* in degrees from down, ccw */

 private:
  ImageList images_;
  ImageNode *current_image_;
};

#endif
