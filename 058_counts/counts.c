#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  
  c->onecntsize = 0; 
  c->cntary = NULL; //malloc(sizeof(*c->cntary));
  //c->cntary[0] = malloc(sizeof(*(c->cntary[0])));
  //(c->cntary[0])->freq = 0;
  //(c->cntary[0])->str = NULL;
  
  c->unknown = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  
    if (name == NULL) {
      c->unknown++;
      return;
    }
    
    else {
      int i;
      for (i = 0; i < c->onecntsize; i++) {
	if ( strcmp(name, (c->cntary[i])->str) == 0) { 
	  (c->cntary[i])->freq++;
	  return;
	}
      }
      c->cntary = realloc(c->cntary, (1+i) * sizeof(*c->cntary));
      c->cntary[i] = malloc(sizeof(*(c->cntary[i])));
      c->cntary[i]->freq = 0;
      c->cntary[i]->str = calloc((strlen(name)+1), sizeof(*(c->cntary[i]->str)));
      
      
      strncpy((c->cntary[i])->str, name, strlen(name));
      (c->cntary[i])->freq++;
	  ///
      
      c->onecntsize++;
     
      
      
      return;
    }

}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->onecntsize; i++) {
    fprintf(outFile, "%s: %d\n", (c->cntary[i])->str, (c->cntary[i])->freq);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown);
  }
  
}
void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = c->onecntsize - 1; i >= 0; i--) {
    free((c->cntary[i])->str);
    free(c->cntary[i]);
  }
  free(c->cntary);
  free(c);
}
