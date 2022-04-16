#include "loadImg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void saveBMP(unsigned char data[], int rows, int cols, const char *filename) {
  int width = rows, height = cols;
  int pad = (4 - (3 * width) % 4) % 4;
  int filesize = 54 + (3 * width + pad) * height;
  unsigned char header[54] = {'B', 'M', 0, 0, 0,  0, 0, 0, 0,  0,
                              54,  0,   0, 0, 40, 0, 0, 0, 0,  0,
                              0,   0,   0, 0, 0,  0, 1, 0, 24, 0};
  char padding[3] = {0, 0, 0};
  unsigned char *img;
  FILE *file;
  int i;
  for (i = 0; i < 4; i++) {
    header[2 + i] = (unsigned char)((filesize >> (8 * i)) & 255);
    header[18 + i] = (unsigned char)((width >> (8 * i)) & 255);
    header[22 + i] = (unsigned char)((height >> (8 * i)) & 255);
  }
  img = (unsigned char *)malloc(sizeof(char) * 3 * (size_t)width *
                                (size_t)height);
  if (img == NULL)
    printf("Error could not allocate memory !\n");
  else {
    for (i = 0; i < width * height; i++) {
      int color = data[i];
      img[3 * i + 2] = img[3 * i + 1] = img[3 * i] =
          (unsigned char)(color & 0xFF);
    }
    file = fopen(filename, "wb");
    if (file == NULL)
      printf("Error: could not open file '%s' !\n", filename);
    else {
      fwrite(header, 54, 1, file);
      for (i = height - 1; i >= 0; i--) {
        fwrite((char *)(img + 3 * width * i), 3 * (size_t)width, 1, file);
        fwrite(padding, (unsigned int)pad, 1, file);
      }
      fclose(file);
    }
    free(img);
  }
}
imgData loadImg(char *str) {
  // return value
  imgData imgDataBuffer = {
      0,
  };
  // buffers
  if (str == NULL) {
    printf("Loading image failed!\n");
    imgDataBuffer.number = -1;
    return imgDataBuffer;
  }
  char *start = str;
  char *wordBuffer = 0;
  char *comma = NULL;
  // find the number
  wordBuffer = strtok(start, ";");
  imgDataBuffer.number = atoi(wordBuffer);
  // fill image
  llu pixelCount = 0;
  llu n = 0;
  luma u;
  while (wordBuffer != NULL && *start != '\0') {
    // checks if compressed
    comma = NULL;
    comma = strpbrk(wordBuffer, ",");
    if (comma != NULL) {
      // comma detected
      n = 0;
      sscanf(wordBuffer, "%hhu,%llu",&u, &n);
      // printf("%llu\n",n);
      while (n > 0 && pixelCount < 28 * 28) {
        imgDataBuffer.img.pixel[pixelCount / 28][pixelCount % 28] = u;
        pixelCount++;
        n--;
      }
    } else {
      imgDataBuffer.img.pixel[pixelCount / 28][pixelCount % 28] =
          (luma)atoi(wordBuffer);
      pixelCount++;
    }

    wordBuffer = strtok(NULL, ";");
  }
  return imgDataBuffer;
}
void printImgData(imgData input) {
  printf("\nnumber %d:\n", input.number);
  for (int y = 0; y < 28; y++) {
    for (int x = 0; x < 28; x++) {
      (input.img.pixel)[y][x] < 127 ? printf("X") : printf(" ");
    }
    printf("\n");
  }
}
void saveImg(img image, char *name) {
  luma pixels[28 * 28];
  for (int y = 0; y < 28; y++) {
    for (int x = 0; x < 28; x++) {
      pixels[y * 28 + x] = image.pixel[y][x];
    }
  }
  saveBMP(pixels, 28, 28, name);
}
char *fgetline(FILE *file) {
  if (feof(file) == 1) {
    return NULL;
  }
  unsigned int total = 0;
  char *lineBuffer = calloc(1, sizeof(char));
  lineBuffer == NULL ? abort() : 0;
  char charBuffer = 0;
  do {
    charBuffer = getc(file);
    if (charBuffer == '\n')
      goto closeLabel;
    total++;
    lineBuffer = realloc(lineBuffer, total);
    lineBuffer == NULL ? abort() : 0;
    lineBuffer[total - 1] = charBuffer;
  } while (charBuffer != '\n' && !feof(file));
  if (feof(file) == 1) {
    puts("End of file reached");
  }
closeLabel:
  lineBuffer = realloc(lineBuffer, total + 1);
  lineBuffer[total] = '\0';
  return lineBuffer;
}