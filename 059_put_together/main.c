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
  //  char ** valuearray = NULL;
  char * onekey = NULL;
  size_t sz;
  size_t i = 0;
  FILE * f = fopen(filename, "r");
  counts_t * c = createCounts();

  while (getline(&onekey, &sz, f) >= 0) {

    //valuearray = realloc(valuearray, (i+1) * sizeof(*valuearray));
    stripNewline(onekey);
    
    addCount(c,lookupValue(kvPairs, onekey));
    free(onekey);
    onekey = NULL;
    i++;
  }
  free(onekey);
  fclose(f);
 
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
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
