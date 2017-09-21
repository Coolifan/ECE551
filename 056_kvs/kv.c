#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvpair_t * readAPair(FILE* f) {
  kvpair_t * kv = malloc(sizeof(*kv)); // the ptr to return kvpair struct
  size_t sz = 0;
  char * line = NULL; //buffer
  ssize_t len = getline(&line, &sz, f); // read one line and save to buffer
  int equalsign = 0; // use to check if encounter the first = sign
  kv->key = calloc((len+1), sizeof(*kv->key)); // not sure if len w/ +1
  kv->value = calloc((len+1), sizeof(*kv->value));
  // allocate space for key and value
  for (int i = 0; i < len - 1; i++) {
    if (line[i] == '=' && equalsign == 0) {
      equalsign = i; // if encounter 1st = sign, set counter, no write
    }
    else if (line[i] != '=' && equalsign == 0) {
      kv->key[i] = line[i]; // if haven't seen 1st =, keep writing to key
    }
    else if (equalsign != 0) { 
      kv->value[i-equalsign-1] = line[i];
    } // if passed 1st = sign, write everything to value
  }
  free(line); //free mem allocated by getline
  return kv;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr,"cannot open file\n");
    return NULL;
  }
  int paircnt = 0;
  int c; // to count total # of lines(kv pairs) by counting \n
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      paircnt++;
    }
  }
  fseek(f, 0, SEEK_SET); //IMPORTANT
  kvarray_t *kvary = malloc(sizeof(*kvary)); //the return kvarray
  kvary->length = paircnt;
  kvary->pair = malloc(kvary->length * sizeof(*kvary->pair)); 
  //allocate mem for (length) kvpair 's
  for (int i = 0; i < kvary->length; i++) {
    kvary->pair[i] = readAPair(f); // call fxn to read kv 's
  }
  
  fclose(f);
  return kvary; 
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free((pairs->pair[i])->key);
    free((pairs->pair[i])->value);
    free(pairs->pair[i]); //after freeing key&value, FILO
  }
  free(pairs->pair);
  free(pairs);
  
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pair[i]->key, pairs->pair[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    if ((strcmp(key, (pairs->pair[i])->key)) == 0) {
      return (pairs->pair[i])->value;
    }
  } // it match, return value. Return NULL otherwise.
  return NULL;
}
