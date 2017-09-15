#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

void helper(int * array, size_t n, size_t ans) {
  
  if (maxSeq(array,n) != ans){
    //    printf("error\n");
    exit(EXIT_FAILURE);
  }
}

int main (void)
{
  int array1[0] = {};
  helper(array1, 0, 0);
  int array2[5] = {0,2,1,2,3};
  helper(array2, 5, 3);
  int array3[2] = {1,1};
  helper(array3, 2, 1);
  int array4[6] = {1,2,3,-3,-2,-1};
  helper(array4, 6, 3);
  return EXIT_SUCCESS;
}
