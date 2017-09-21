#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


kvpair_t * readAPair(FILE* f) {
  kvpair_t * kv = malloc(sizeof(*kv));
  size_t sz = 0;
  char * line = NULL;
  ssize_t len = getline(&line, &sz, f);
  int equalsign = 0;
  kv->key = calloc((len+1), sizeof(*kv->key));
  kv->value = calloc((len+1), sizeof(*kv->value));
  for (int i = 0; i < len - 1; i++) {
    if (line[i] == '=' && equalsign == 0) {
      equalsign = i;
    }
    else if (line[i] != '=' && equalsign == 0) {
      kv->key[i] = line[i];
    }
    else if (equalsign != 0) {
      kv->value[i-equalsign-1] = line[i];
    }
  }
  free(line);
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
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      paircnt++;
    }
  }
  fseek(f, 0, SEEK_SET);
  kvarray_t *kvary = malloc(sizeof(*kvary));
  kvary->length = paircnt;
  kvary->pair = malloc(kvary->length * sizeof(*kvary->pair));

  for (int i = 0; i < kvary->length; i++) {
    kvary->pair[i] = readAPair(f);
  }
  
  fclose(f);
  return kvary; 
  
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->length; i++) {
    free((pairs->pair[i])->key);
    free((pairs->pair[i])->value);
    free(pairs->pair[i]);
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
  int j;
  for (int i = 0; i < pairs->length; i++) {
    if ((j = strcmp(key, (pairs->pair[i])->key)) == 0) {
      return (pairs->pair[i])->value;
    }
  }
  return NULL;
}
