typedef unsigned char luma;
typedef long long unsigned llu;
typedef enum number {
  zero,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine
} number;
typedef struct _IMG {
  luma pixel[28][28];
} img;

typedef struct _IMGDATA {
  struct _IMG img;
  enum number number;
} imgData;
imgData loadImg(char *str);