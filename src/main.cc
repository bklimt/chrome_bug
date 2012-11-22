// Copyright 2009 Google Inc. All Rights Reserved.
// Author: klimt@google.com (Bryan Klimt)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bug.h"
#include "graphics.h"
#include "pcx.h"

#include <vector>

/* Global State */

PCX background("images/back_hd.pcx");

std::vector<Bug*> bugs;

Sprite left_hand("images/lh_hd.pcx", "images/lh_hd_mask.pcx", 0, 600, 180);
Sprite right_hand("images/rh_hd.pcx", "images/rh_hd_mask.pcx", 1200, 600, 180);

Sprite logo("images/logo_hd.pcx", "images/logo_hd_mask.pcx", 187, 46, 180);
Sprite motto("images/motto_hd.pcx", "images/motto_hd_mask.pcx", 326, 433, 180);

int left_hand_bug;
int right_hand_bug;

void CreateBug(char *filename, int x, int y) {
  bugs.push_back(new Bug(filename, x, y));
}

#define LOGO_FRAMES   2 * 30
#define INTRO_FRAMES  6 * 30
#define NUM_FRAMES   30 * 30
#define OUTRO_FRAMES  5 * 30

/* End Global State */

void Init() {
  left_hand.AddImage("images/lhc_hd.pcx", "images/lhc_hd_mask.pcx");
  right_hand.AddImage("images/rhc_hd.pcx", "images/rhc_hd_mask.pcx");

  CreateBug("images/bug4_hd.pcx", 103,  21);
  CreateBug("images/bug4_hd.pcx", 105,  32);
  CreateBug("images/bug4_hd.pcx", 116,  46);
  CreateBug("images/bug4_hd.pcx", 215,  55);
  CreateBug("images/bug4_hd.pcx", 230,  58);
  CreateBug("images/bug4_hd.pcx", 196,  63);
  CreateBug("images/bug4_hd.pcx", 211,  64);
  CreateBug("images/bug4_hd.pcx", 226,  67);

  CreateBug("images/bug2_hd.pcx", 122,  40);
  CreateBug("images/bug2_hd.pcx", 138,  38);
  CreateBug("images/bug2_hd.pcx", 148,  32);
  CreateBug("images/bug2_hd.pcx", 161,  33);
  CreateBug("images/bug2_hd.pcx", 175,  38);
  CreateBug("images/bug2_hd.pcx", 189,  53);
  CreateBug("images/bug2_hd.pcx", 158,  38);
  CreateBug("images/bug2_hd.pcx", 176,  44);

  CreateBug("images/bug3_hd.pcx", 116,  14);
  CreateBug("images/bug3_hd.pcx", 131,   8);
  CreateBug("images/bug3_hd.pcx", 147,   5);
  CreateBug("images/bug3_hd.pcx", 163,   5);
  CreateBug("images/bug3_hd.pcx", 178,   7);
  CreateBug("images/bug3_hd.pcx", 194,  12);
  CreateBug("images/bug3_hd.pcx", 194,  12);
  CreateBug("images/bug3_hd.pcx", 206,  20);
  CreateBug("images/bug3_hd.pcx", 217,  28);
  CreateBug("images/bug3_hd.pcx", 225,  41);

  CreateBug("images/bug1_hd.pcx", 210,  36);
  CreateBug("images/bug1_hd.pcx", 201,  34);
  CreateBug("images/bug1_hd.pcx", 191,  30);
  CreateBug("images/bug1_hd.pcx", 178,  22);
  CreateBug("images/bug1_hd.pcx", 165,  18);
  CreateBug("images/bug1_hd.pcx", 148,  18);
  CreateBug("images/bug1_hd.pcx", 134,  22);
  CreateBug("images/bug1_hd.pcx", 121,  26);
  CreateBug("images/bug1_hd.pcx", 115,  26);
  CreateBug("images/bug1_hd.pcx", 156,  11);
  CreateBug("images/bug1_hd.pcx", 186,  17);
  CreateBug("images/bug1_hd.pcx", 197,  40);

  CreateBug("images/bug8_hd.pcx", 245,  72);
  CreateBug("images/bug8_hd.pcx", 245,  91);
  CreateBug("images/bug8_hd.pcx", 232,  85);
  CreateBug("images/bug8_hd.pcx", 229, 108);
  CreateBug("images/bug8_hd.pcx", 241, 109);
  CreateBug("images/bug8_hd.pcx", 236, 127);
  CreateBug("images/bug8_hd.pcx", 221, 126);
  CreateBug("images/bug8_hd.pcx", 209, 131);
  CreateBug("images/bug8_hd.pcx", 214, 139);
  CreateBug("images/bug8_hd.pcx", 227, 139);
  CreateBug("images/bug8_hd.pcx", 197, 150);
  CreateBug("images/bug8_hd.pcx", 209, 158);
  CreateBug("images/bug8_hd.pcx", 195, 162);
  CreateBug("images/bug8_hd.pcx", 167, 171);
  CreateBug("images/bug8_hd.pcx", 238,  98);
  CreateBug("images/bug8_hd.pcx", 184, 166);
  CreateBug("images/bug8_hd.pcx", 155, 170);

  CreateBug("images/bug7_hd.pcx", 204,  91);
  CreateBug("images/bug7_hd.pcx", 215,  96);
  CreateBug("images/bug7_hd.pcx", 212, 108);
  CreateBug("images/bug7_hd.pcx", 196, 114);
  CreateBug("images/bug7_hd.pcx", 182, 117);
  CreateBug("images/bug7_hd.pcx", 168, 122);
  CreateBug("images/bug7_hd.pcx", 152, 125);
  CreateBug("images/bug7_hd.pcx", 197, 133);
  CreateBug("images/bug7_hd.pcx", 184, 138);
  CreateBug("images/bug7_hd.pcx", 170, 140);
  CreateBug("images/bug7_hd.pcx", 158, 141);
  CreateBug("images/bug7_hd.pcx", 158, 141);
  CreateBug("images/bug7_hd.pcx", 141, 140);
  CreateBug("images/bug7_hd.pcx", 130, 149);
  CreateBug("images/bug7_hd.pcx", 178, 148);
  CreateBug("images/bug7_hd.pcx", 160, 157);
  CreateBug("images/bug7_hd.pcx", 145, 160);
  CreateBug("images/bug7_hd.pcx", 217,  81);
  CreateBug("images/bug7_hd.pcx", 205,  76);
  CreateBug("images/bug7_hd.pcx", 198,  98);
  CreateBug("images/bug7_hd.pcx", 195,  86);
  CreateBug("images/bug7_hd.pcx", 216,  86);
  CreateBug("images/bug7_hd.pcx", 192, 106);
  CreateBug("images/bug7_hd.pcx", 206, 121);
  CreateBug("images/bug7_hd.pcx", 166, 115);
  CreateBug("images/bug7_hd.pcx", 181, 127);
  CreateBug("images/bug7_hd.pcx", 199, 140);
  CreateBug("images/bug7_hd.pcx", 162, 120);
  CreateBug("images/bug7_hd.pcx", 148, 149);
  CreateBug("images/bug7_hd.pcx", 180, 155);

  CreateBug("images/bug6_hd.pcx", 183,  85);
  CreateBug("images/bug6_hd.pcx", 180,  96);
  CreateBug("images/bug6_hd.pcx", 170, 102);
  CreateBug("images/bug6_hd.pcx", 155, 101);
  CreateBug("images/bug6_hd.pcx", 143, 100);
  CreateBug("images/bug6_hd.pcx", 135,  92);
  CreateBug("images/bug6_hd.pcx", 127,  84);
  CreateBug("images/bug6_hd.pcx", 119,  72);
  CreateBug("images/bug6_hd.pcx", 136,  40);
  CreateBug("images/bug6_hd.pcx", 162,  47);
  CreateBug("images/bug6_hd.pcx", 183,  70);

  CreateBug("images/bug5_hd.pcx", 137,  58);
  CreateBug("images/bug5_hd.pcx", 128,  62);
  CreateBug("images/bug5_hd.pcx", 140,  70);
  CreateBug("images/bug5_hd.pcx", 157,  67);
  CreateBug("images/bug5_hd.pcx", 149,  79);
  CreateBug("images/bug5_hd.pcx", 164,  81);
  CreateBug("images/bug5_hd.pcx", 170,  72);
  CreateBug("images/bug5_hd.pcx", 149,  51);
  CreateBug("images/bug5_hd.pcx", 165,  60);
  CreateBug("images/bug5_hd.pcx", 174,  57);
  CreateBug("images/bug5_hd.pcx", 128,  57);
  CreateBug("images/bug5_hd.pcx", 153,  59);
  CreateBug("images/bug5_hd.pcx", 144,  81);
  CreateBug("images/bug5_hd.pcx", 158,  88);
  CreateBug("images/bug5_hd.pcx", 171,  91);

  CreateBug("images/bug0_hd.pcx", 100, 156);
  CreateBug("images/bug0_hd.pcx",  88, 144);
  CreateBug("images/bug0_hd.pcx",  92, 135);
  CreateBug("images/bug0_hd.pcx",  73, 130);
  CreateBug("images/bug0_hd.pcx", 101, 124);
  CreateBug("images/bug0_hd.pcx", 113, 118);
  CreateBug("images/bug0_hd.pcx", 103, 104);
  CreateBug("images/bug0_hd.pcx", 103, 104);
  CreateBug("images/bug0_hd.pcx",  90, 111);
  CreateBug("images/bug0_hd.pcx",  78, 103);
  CreateBug("images/bug0_hd.pcx",  64, 106);
  CreateBug("images/bug0_hd.pcx",  94,  86);
  CreateBug("images/bug0_hd.pcx",  81,  81);
  CreateBug("images/bug0_hd.pcx",  65,  81);
  CreateBug("images/bug0_hd.pcx",  70,  61);
  CreateBug("images/bug0_hd.pcx",  85,  61);
  CreateBug("images/bug0_hd.pcx",  97,  59);
  CreateBug("images/bug0_hd.pcx",  70,  49);
  CreateBug("images/bug0_hd.pcx",  70,  70);
  CreateBug("images/bug0_hd.pcx",  82,  73);
  CreateBug("images/bug0_hd.pcx",  95,  71);
  CreateBug("images/bug0_hd.pcx",  77,  89);
  CreateBug("images/bug0_hd.pcx",  91,  97);
  CreateBug("images/bug0_hd.pcx",  70, 119);
  CreateBug("images/bug0_hd.pcx",  89, 125);
  CreateBug("images/bug0_hd.pcx", 117, 124);
  CreateBug("images/bug0_hd.pcx", 104, 138);

  CreateBug("images/bug9_hd.pcx", 141, 117);
  CreateBug("images/bug9_hd.pcx", 132, 129);
  CreateBug("images/bug9_hd.pcx", 118, 141);
  CreateBug("images/bug9_hd.pcx", 111, 160);
  CreateBug("images/bug9_hd.pcx", 125, 165);
  CreateBug("images/bug9_hd.pcx", 137, 171);

  CreateBug("images/buga_hd.pcx",  92,  29);
  CreateBug("images/buga_hd.pcx",  83,  38);
  CreateBug("images/buga_hd.pcx",  93,  42);
  CreateBug("images/buga_hd.pcx", 106,  54);
  CreateBug("images/buga_hd.pcx", 107,  68);
  CreateBug("images/buga_hd.pcx", 111,  81);
  CreateBug("images/buga_hd.pcx", 114,  90);
  CreateBug("images/buga_hd.pcx", 120, 100);
  CreateBug("images/buga_hd.pcx", 130, 110);
  CreateBug("images/buga_hd.pcx",  82,  49);
  CreateBug("images/buga_hd.pcx", 102,  46);
  CreateBug("images/buga_hd.pcx", 127,  93);
  CreateBug("images/buga_hd.pcx", 139, 106);

  for (unsigned int i = 0; i < bugs.size(); ++i) {
    unsigned int j = randint(bugs.size());
    Bug *other = bugs[j];
    bugs[j] = bugs[i];
    bugs[i] = other;
  }

  for (unsigned int i = 0; i < bugs.size(); ++i) {
    bugs[i]->resurrection_time =
        LOGO_FRAMES + INTRO_FRAMES + ((((bugs.size() - i) - 1) * NUM_FRAMES) / bugs.size());
  }

  left_hand_bug = bugs.size() - 1;
  right_hand_bug = bugs.size() - 2;
}

void Move(unsigned long frame) {
  if (frame < LOGO_FRAMES) {
    return;
  }

  if (frame < LOGO_FRAMES + INTRO_FRAMES) {
    int time_left = (LOGO_FRAMES + INTRO_FRAMES / 2) - frame;
    logo.y += ((-logo.GetCurrentHeight()) - logo.y) / time_left;
    motto.y += (background.height() - motto.y) / time_left;
  }

  while (left_hand_bug >= 0 &&
         bugs[left_hand_bug]->resurrection_time < frame) {
    left_hand_bug--;
    if (left_hand_bug == right_hand_bug) {
      left_hand_bug--;
    }
  }

  if (left_hand_bug >= 0) {
    int time_left = bugs[left_hand_bug]->resurrection_time - frame;
    if (time_left > 0) {
      left_hand.x += (bugs[left_hand_bug]->x() - left_hand.x) / time_left;
      left_hand.y += (bugs[left_hand_bug]->y() - left_hand.y) / time_left;
    }
    if (time_left == 0 || time_left == 10) {
      left_hand.NextImage();
    }
  }

  while (right_hand_bug >= 0 &&
         bugs[right_hand_bug]->resurrection_time < frame) {
    right_hand_bug--;
    if (right_hand_bug == left_hand_bug) {
      right_hand_bug--;
    }
  }

  if (right_hand_bug >= 0) {
    int time_left = bugs[right_hand_bug]->resurrection_time - frame;
    if (time_left > 0) {
      right_hand.x += (bugs[right_hand_bug]->x() - right_hand.x) / time_left;
      right_hand.y += (bugs[right_hand_bug]->y() - right_hand.y) / time_left;
    }
    if (time_left == 0 || time_left == 10) {
      right_hand.NextImage();
    }
  }

  if (left_hand_bug < 0) {
    left_hand.FirstImage();
    int time_left = (NUM_FRAMES + LOGO_FRAMES + INTRO_FRAMES + OUTRO_FRAMES) - frame;
    left_hand.x += (0 - left_hand.x) / time_left;
    left_hand.y += (600 - left_hand.y) / time_left;
  }

  if (right_hand_bug < 0) {
    right_hand.FirstImage();
    int time_left = (NUM_FRAMES + LOGO_FRAMES + INTRO_FRAMES + OUTRO_FRAMES) - frame;
    right_hand.x += (1200 - right_hand.x) / time_left;
    right_hand.y += (600 - right_hand.y) / time_left;
  }

  for (unsigned int i = 0; i < bugs.size(); ++i) {
    bugs[i]->Move(frame);
  }
}

void Draw(unsigned long frame) {
  DrawPCX(background, NULL, 0, 0, 180);

  for (unsigned int i = 0; i < bugs.size(); ++i) {
    bugs[i]->Draw();
  }

  left_hand.Draw();
  right_hand.Draw();

  if (frame <= LOGO_FRAMES + INTRO_FRAMES) {
    logo.Draw();
    motto.Draw();
  }
}

void Destroy() {
  for (unsigned int i = 0; i < bugs.size(); ++i) {
    delete bugs[i];
  }
  bugs.clear();
}

int main() {
  unsigned long i;
  /*
  clock_t start_time;
  clock_t end_time;
  unsigned long ticks_per_frame = CLOCKS_PER_SEC / 30;
  */

  srand((unsigned int)time(NULL));

  vga_init();

  Init();

  if (vga_setmode(G320x200x256)) {
    fprintf(stderr, "Unable to set vga mode 320x200x256.\n");
    exit(-1);
  }
  background.LoadPalette();

  // start_time = clock();
  for (i = 0; i < LOGO_FRAMES + INTRO_FRAMES + NUM_FRAMES + OUTRO_FRAMES; ++i) {
    Move(i);
    Draw(i);
    Flip();
    /*
    do {
      end_time = clock();
    } while ((end_time - start_time) < ticks_per_frame);
    start_time = end_time;
    */
  }

  vga_setmode(TEXT);

  Destroy();

  return 0;
}
