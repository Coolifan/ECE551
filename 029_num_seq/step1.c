//This file is for Step 1.
//You should do 
#include <stdio.h>
#include <stdlib.h>
//  Step 1 (A): write seq1
int seq1(int x) {
  return 4*x-3;
}

//  Step 1 (C): write printSeq1Range
void printSeq1Range(int low, int high) {
  if (high > low) {
    for (int i = low; i < high; i++) {
      printf("%d", seq1(i));
      if (i < high-1)
	printf(",");
    }
    printf("\n");
  }
  else {
    printf("\n");
  }
}

//  Step 1 (B): write main to test seq1
int main(void)
{
  int result1 = seq1(-5);
  printf("seq1(%d) = %d\n", -5, result1);
  int result2 = seq1(0);
  printf("seq1(%d) = %d\n", 0, result2); 
  int result3 = seq1(11);
  printf("seq1(%d) = %d\n", 11, result3);

  printf("printSeq1Range(%d,%d)\n",0,4);
  printSeq1Range(0,4);
  printf("printSeq1Range(%d,%d)\n",-2,6);
  printSeq1Range(-2,6);
  printf("printSeq1Range(%d,%d)\n",7,3);
  printSeq1Range(7,3);
  
  return EXIT_SUCCESS;
}
//  Step 1 (D): add test cases to main to test printSeq1Range
// 
// Be sure to #include any header files you need!

