#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

void stripNewline(char *str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
    

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  char * onekey = NULL;
  size_t sz;
  size_t i = 0;
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open input file %s\n", filename);
    return NULL;
  }
  counts_t * c = createCounts(); //initialize c
  // read keys from file, strip \n
  while (getline(&onekey, &sz, f) >= 0) {
    stripNewline(onekey);
    addCount(c,lookupValue(kvPairs, onekey)); // pair values, add to count
    free(onekey);
    onekey = NULL;
    i++; //repeat till EOF
  }
  free(onekey); //free when jump out of loop
  fclose(f);
 
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "insufficient input arguments\n");
    return EXIT_FAILURE;
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    fprintf(stderr, "cannot read kv pairs\n");
    freeKVs(kv);
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    if (c == NULL) {
      fprintf(stderr, "cannot open file %s\n", argv[i]);
      freeCounts(c);
      freeKVs(kv);
      return EXIT_FAILURE;
    }
    char * outName = computeOutputFileName(argv[i]);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    //compute the output file name from argv[i] (call this outName)

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
