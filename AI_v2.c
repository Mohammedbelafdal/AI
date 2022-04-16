#include "loadImg.c"
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *dataFile = fopen("images_data.csv", "r");
  dataFile==NULL?abort():0;
  imgData imgDataBuffer;
  char *lineBuffer;
  lineBuffer = fgetline(dataFile);
  lineBuffer == NULL ? abort() : 0;
  
  puts(lineBuffer);
  free(lineBuffer);
  for (int l = 0; l < 30000; l++) {
    lineBuffer = fgetline(dataFile);
    // puts(lineBuffer);
    imgDataBuffer = loadImg(lineBuffer);
    //printImgData(imgDataBuffer);
    free(lineBuffer);
    lineBuffer = calloc(20, 1);
    lineBuffer == NULL ? abort() : 0;
    sprintf(lineBuffer, "images/n%d_%d.bmp", imgDataBuffer.number, l);
    saveImg(imgDataBuffer.img, lineBuffer);
    free(lineBuffer);
  }
  fclose(dataFile);
  return EXIT_SUCCESS;
}
