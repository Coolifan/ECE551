#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = malloc(len * sizeof(*outputName));
  snprintf(outputName, len, "%s%s", inputName, suffix);

  return outputName;
}
