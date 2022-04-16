typedef unsigned char luma;
typedef long long unsigned llu;
typedef enum number {
  unknown=-1,
  zero=0,
  one=1,
  two=2,
  three=3,
  four=4,
  five=5,
  six=6,
  seven=7,
  eight=8,
  nine=9
} number;
typedef struct _IMG {
  luma pixel[28][28];
} img;

typedef struct _IMGDATA {
  struct _IMG img;
  enum number number;
} imgData;
imgData loadImg(char *str);