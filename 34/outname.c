#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outPutFileName = malloc((strlen(inputName) + 8) * sizeof(*inputName));
  strcpy(outPutFileName, inputName);
  strcat(outPutFileName, ".counts");

  return outPutFileName;
}
