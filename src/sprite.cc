
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "sprite.h"
#include "graphics.h"
#include "pcx.h"

/* Image List */

void InitImageList(ImageList *list) {
  *list = NULL;
}

void AddImage_(ImageList *list, char *filename, char *mask_filename) {
  while (*list != NULL) {
    list = &((*list)->next);
  }
  *list = new ImageNode(filename, mask_filename);
}

void FreeImageList(ImageList *list) {
  if (*list != NULL) {
    FreeImageList(&((*list)->next));
    delete *list;
    *list = NULL;
  }
}

/* Sprite */

Sprite::Sprite(char *filename, char *mask_filename,
               float x_, float y_, float direction_)
    : x(x_), y(y_), direction(direction_) {
  InitImageList(&images_);
  AddImage_(&images_, filename, mask_filename);

  current_image_ = images_;
}

void Sprite::Draw() {
  DrawPCX(*GetCurrentImage(),
          GetCurrentMask(),
          (int)(x + 0.5),
          (int)(y + 0.5),
          direction);
}

Sprite::~Sprite() {
  FreeImageList(&images_);
}

PCX *Sprite::GetCurrentImage() {
  return &(current_image_->image);
}

PCX *Sprite::GetCurrentMask() {
  return &(current_image_->mask);
}

int Sprite::GetCurrentWidth() {
  return GetCurrentImage()->width();
}

int Sprite::GetCurrentHeight() {
  return GetCurrentImage()->height();
}

void Sprite::NextImage() {
  current_image_ = current_image_->next;
  if (current_image_ == NULL) {
    current_image_ = images_;
  }
}

void Sprite::FirstImage() {
  current_image_ = images_;
}


