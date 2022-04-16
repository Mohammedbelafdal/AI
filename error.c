#include "error.h"
#include <stdio.h>
char *getError(errorType error) {
  int errorValue = error;
  switch (errorValue) {
  case memory:
    return "memory error, malloc/free has failed";
  case file:
    return "file error, couldn't open/modify file";
  case image:
    return "image error, image loading failed";
  case success:
    return "Executed successfully, exiting";
  default:
    return "Unknown error";
  }
}
void logError(char *msg, FILE *file) {
  fprintf(file, "%s\n", msg);
  fflush(file);
}