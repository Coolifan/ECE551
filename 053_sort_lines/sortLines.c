#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortandprint(FILE* f) {
  char ** line2 = NULL;
  char * curr2  = NULL;
  size_t sz2;
  size_t i2 = 0;
    // ssize_t len1 = 0;
  while ((getline(&curr2, &sz2, f)) >= 0) {
      line2 = realloc(line2, (i2+1) * sizeof(*line2));
      line2[i2] = curr2;
      curr2 = NULL;
      i2++;
    }
    free(curr2);
    sortData(line2, i2);
    for (size_t j = 0; j < i2; j++) {
      printf("%s", line2[j]);
      free(line2[j]);
    }
    
    free(line2);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char ** line1 = NULL;
    char * curr  = NULL;
    size_t sz1;
    size_t i = 0;
    // ssize_t len1 = 0;
    while ((getline(&curr, &sz1, stdin)) >= 0) {
      line1 = realloc(line1, (i+1) * sizeof(*line1));
      line1[i] = curr;
      curr = NULL;
      i++;
    }
    free(curr);
    sortData(line1, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", line1[j]);
      free(line1[j]);
    }
    free(line1);
  }
  
  else {
    for (int i = 1; i < argc; i++) {
      FILE *f  = fopen(argv[i],"r");
      if (f == NULL) {
	fprintf(stderr,"cannot open file\n");
	exit(EXIT_FAILURE);
      }
      sortandprint(f);
      fclose(f);
    }
  }
  return EXIT_SUCCESS;
}
