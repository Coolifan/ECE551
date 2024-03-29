#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file\n");
    exit(EXIT_FAILURE);
  }
  uint64_t * freqArray = new uint64_t [257];
  if (freqArray == NULL) {
    fprintf(stderr, "cannot allocate memory\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 257; i++) {
    freqArray[i] = 0;
  }
  int c;
  while ((c = fgetc(f)) != EOF) {
    int index = int(c);
    (freqArray[index])++;
  }
  freqArray[256] = 1;
  fclose(f);
  return freqArray;
}
