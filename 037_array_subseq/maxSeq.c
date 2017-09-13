#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n)
{
  size_t count = 0;
  size_t result1 = 0;
  size_t result2 = 0;
  for (int i=0; i<n-1; i++) {
    if (array[i] < array[i+1]){
      count++;
      result2 = count;
    }
    else {
      if (count > result1) {
	result1 = count;
	count = 0;
      }
    }
  }
  return result2>result1 ? result2+1 : result1+1;
}
