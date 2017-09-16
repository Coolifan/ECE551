#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int decipher(FILE *f, int *array) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      ++array[c];
    }
  }

  int temp = array[97] > array[98] ? array[97] : array[98];
  int ptr = array[97] > array[98] ? 97 : 98;
  for (int i = 99; i < 128; i++) {
    if (temp < array[i]) {
      ptr = i;
      temp = array[i];
    }
  }
  int key = ptr - 'a' - ('e' - 'a');
  return key < 0 ? 26+key : key;
 
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage, inputFilename\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    return EXIT_FAILURE;
  }

  int array[128] = {0};
  int key = decipher(f, array);
  fprintf(stdout, "%d\n", key);
  fclose(f);
  return EXIT_SUCCESS;
}
