#include <stdio.h>
#include <stdlib.h>


void rotate(FILE *f) {
  int output[10][11];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      if (feof(f)) {
	fprintf(stderr, "improper line read\n");
	exit(EXIT_FAILURE);
      }
      output[i][j] = fgetc(f);
      if ((output[i][j] == '\n') && (j != 10)) {
	fprintf(stderr,"improper line read\n");
	exit(EXIT_FAILURE);
      }
      
    }
  }

  int c;
  if ((c=fgetc(f)) != EOF) {
    fprintf(stderr, "Matrix is too large to handle\n");
    exit(EXIT_FAILURE);
  }

  for (int y = 0; y < 10; y++) {
    for (int x = 9; x >= 0; x--) {
      fprintf(stdout,"%c", output[x][y]);
      if (x == 0)
	fprintf(stdout, "\n");
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Incorrect number of arguments\n");
    exit(EXIT_FAILURE);
  }
  
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  rotate(f);
  fclose(f);
  return EXIT_SUCCESS;
}
