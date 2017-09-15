//This file is for Step 2.
//You should do 
#include <stdio.h>
#include <stdlib.h>
//  Step 2 (A): write seq2
int seq2(int x) {
  return (x+1)*(x+1)+x;
}

//  Step 2 (C): write sumSeq2
int sumSeq2(int low, int high) {
  int sum = 0;
  if (high > low) {
    for (int i = low; i < high; i++) {
      sum += seq2(i);
    }
  }
  return sum;
}

//  Step 2 (B): write main to test seq2
int main(void)
{
  int result1 = seq2(-5);
  printf("seq2(%d) = %d\n", -5, result1);
  int result2 = seq2(0);
  printf("seq2(%d) = %d\n", 0, result2);
  int result3 = seq2(11);
  printf("seq2(%d) = %d\n", 11, result3);

  int sum1 = sumSeq2(0,2);
  printf("sumSeq2(0, 2) = %d\n", sum1);
  int sum2 = sumSeq2(3,6);
  printf("sumSeq2(3, 6) = %d\n", sum2);
  int sum3 = sumSeq2(9,7);
  printf("sumSeq2(9, 7) = %d\n", sum3);
  return EXIT_SUCCESS;
}
//  Step 2 (D): add test cases to main to test sumSeq2
// 
// Be sure to #include any header files you need!

