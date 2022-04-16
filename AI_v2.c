
#include "error.c"
#include "loadImg.c"
#include <stdio.h>
#include <stdlib.h>
#define LOGFILE "logFile.log"
FILE *gdataFile = NULL;
FILE *glogFile = NULL;
void init() {
  glogFile = fopen(LOGFILE, "w");
  if (glogFile == NULL) {
    logError(getError(file), stderr);
    exit(EXIT_FAILURE);
  }
  gdataFile = fopen("images_data.csv", "r");
  if (gdataFile == NULL) {
    logError(getError(file), stderr);
    exit(EXIT_FAILURE);
  }
}
void close(int status,errorType error) {
  logError(getError(error), glogFile);
  fclose(gdataFile);
  fclose(glogFile);
  exit(status);
}
int main(int argc, char **argv) {
  init();
  imgData imgDataBuffer;
  char *lineBuffer;
  llu height = 0, width = 0, images = 0, parsedImages = 0;
  lineBuffer = fgetline(gdataFile);
  lineBuffer == NULL ? close(EXIT_FAILURE,memory) : 0;
  sscanf(lineBuffer, "%llu;%llu;%llu", &images, &width, &height);
  free(lineBuffer);
  fprintf(glogFile,
          "Successfully loaded file containing %llu images of %llux%llu\n",
          images, width, height);

  for (llu l = 0; l < 100; l++) {
    lineBuffer = fgetline(gdataFile);
    // puts(lineBuffer);
    imgDataBuffer = loadImg(lineBuffer);
    (imgDataBuffer.number != unknown) ? parsedImages++ : 0;
    // printImgData(imgDataBuffer);
    free(lineBuffer);
    lineBuffer = calloc(60, 1);
    lineBuffer == NULL ? close(EXIT_FAILURE,memory) : 0;
    sprintf(lineBuffer, "images/n%d_%llu.bmp", imgDataBuffer.number, l);
    // saveImg(imgDataBuffer.img, lineBuffer);
    free(lineBuffer);
  }
  lineBuffer = calloc(60, 1);
  lineBuffer == NULL ? close(EXIT_FAILURE,memory) : 0;
  sprintf(lineBuffer, "loaded %llu images successfully",parsedImages);
  logError(lineBuffer, glogFile);
  free(lineBuffer);
  close(EXIT_SUCCESS,success);
  return EXIT_SUCCESS;
}
