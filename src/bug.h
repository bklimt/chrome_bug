
#ifndef __BUG_H__
#define __BUG_H__

#include "sprite.h"

class Bug {
 public:
  Bug(char *filename, int x, int y);
  ~Bug() {}

  void Move(unsigned long frame);
  void Squash();
  void Unsquash();
  void Draw();

  int x() { return sprite_.x; }
  int y() { return sprite_.y; }

  unsigned long resurrection_time;
 private:
  Sprite sprite_;
  int squashed_;
};

#endif

