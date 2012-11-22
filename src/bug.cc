
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bug.h"
#include "graphics.h"
#include "pcx.h"

#define PI 3.14159265358979f

#ifndef min

int min(int x, int y) {
  return x < y ? x : y;
}

#endif

Bug::Bug(char *filename, int x, int y)
    : sprite_(filename, "images/bug_mask_hd.pcx", 80+x*3.5, y*3.5, randint(360)) {

  // Add a version to squash.
  sprite_.AddImage(filename, "images/bug_mask_hd.pcx");

  resurrection_time = 0;
  Squash();
}

void Bug::Move(unsigned long frame) {
  double r;
  int against_wall = 0;

  if (frame == resurrection_time) {
    Unsquash();
  }

  if (squashed_) {
    return;
  }

  sprite_.x -= 8 * sin(sprite_.direction * 2 * PI / 360.0f);
  sprite_.y -= 8 * cos(sprite_.direction * 2 * PI / 360.0f);

  if (sprite_.x < 0) {
    sprite_.x = 0;
    against_wall = 1;
  }
  if (sprite_.y < 0) {
    sprite_.y = 0;
    against_wall = 1;
  }
  if (sprite_.x > 1280 - sprite_.GetCurrentHeight()) {
    sprite_.x = 1280 - sprite_.GetCurrentHeight();
    against_wall = 1;
  }
  if (sprite_.y > 720 - sprite_.GetCurrentHeight()) {
    sprite_.y = 720 - sprite_.GetCurrentHeight();
    against_wall = 1;
  }

  if (against_wall) {
    sprite_.direction += 180;
  }

  r = randint(10000) / 10000.0;
  if (r < 0.4) {
    sprite_.direction -= 15.0;
  } else if (r > 0.6) {
    sprite_.direction += 15.0;
  }
  while (sprite_.direction >= 360.0) {
    sprite_.direction -= 360.0;
  }
}

void Bug::Squash() {
  int x1, y1, x2, y2;
  int radius = min(sprite_.GetCurrentWidth(),
                   sprite_.GetCurrentHeight()) / 2;
  unsigned char color, mask_color;
  int random_distance, random_angle;

  squashed_ = 1;

  sprite_.NextImage();

  PCX *image = sprite_.GetCurrentImage();
  PCX *mask = sprite_.GetCurrentMask();

  for (x1 = 0; x1 < sprite_.GetCurrentWidth(); ++x1) {
    for (y1 = 0; y1 < sprite_.GetCurrentHeight(); ++y1) {
      if (mask->pixel(x1, y1) != 0) {
        random_distance = randint(radius);
        random_angle = randint(360);
        x2 = radius + (int)(random_distance * cos((random_angle * 2 * PI) / 360.0));
        y2 = radius + (int)(random_distance * sin((random_angle * 2 * PI) / 360.0));

        if (x2 < 0) {
          vga_setmode(TEXT);
          fprintf(stderr, "x2 out of range: %d < 0\n", x2);
          exit(-1);
        }
        if (x2 >= sprite_.GetCurrentWidth()) {
          vga_setmode(TEXT);
          fprintf(stderr, "x2 out of range: %d >= %d\n", x2, sprite_.GetCurrentWidth());
          exit(-1);
        }
        if (y2 < 0) {
          vga_setmode(TEXT);
          fprintf(stderr, "y2 out of range: %d < 0\n", y2);
          fprintf(stderr, "radius: %d\n", radius);
          fprintf(stderr, "random distance: %d\n", random_distance);
          fprintf(stderr, "random angle: %d\n", random_angle);
          exit(-1);
        }
        if (y2 >= sprite_.GetCurrentHeight()) {
          vga_setmode(TEXT);
          fprintf(stderr, "y2 out of range: %d >= %d\n", y2, sprite_.GetCurrentHeight());
          fprintf(stderr, "radius: %d\n", radius);
          fprintf(stderr, "random distance: %d\n", random_distance);
          fprintf(stderr, "random angle: %d\n", random_angle);
          exit(-1);
        }

        color = image->pixel(x1, y1);;
        mask_color = mask->pixel(x1, y1);;

        image->SetPixel(x1, y1, image->pixel(x2, y2));
        mask->SetPixel(x1, y1, mask->pixel(x2, y2));

        image->SetPixel(x2, y2, color);
        mask->SetPixel(x2, y2, mask_color);
      }
    }
  }
}

void Bug::Unsquash() {
  squashed_ = 0;
  sprite_.NextImage();
}

void Bug::Draw() {
  sprite_.Draw();
}

