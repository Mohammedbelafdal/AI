#include <stdio.h>
typedef enum _errorType
{
  unknownError,
  file,
  memory,
  image,
  success,

}errorType;
char *getError(errorType error);
void logError(char* msg,FILE * file);