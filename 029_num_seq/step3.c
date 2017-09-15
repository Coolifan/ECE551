//This file is for Step 3.
//You should do 
#include <stdio.h>
#include <stdlib.h>
//  Step 3 (A): write seq3
int seq3(int x, int y) {
  return y*(x+2)-3*x;
}

//  Step 3 (C): write countEvenInSeq3Range
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int cnt = 0;
  if (xLow < xHi && yLow < yHi) {
    for (int i = xLow; i < xHi; i++) {
      for (int j = yLow; j < yHi; j++) {
	if (seq3(i,j) % 2 == 0)
	  cnt++;
      }
    }
  }
  return cnt;
}
//  Step 3 (B): write main to test seq3
int main(void)
{
  int result1 = seq3(-4,-5);
  printf("seq3(-4, -5) = %d\n", result1);
  int result2 = seq3(5,5);
  printf("seq3(5, 5) = %d\n", result2);
  int result3 = seq3(6,-6);
  printf("seq3(6, -6) = %d\n", result3);

  int evencnt1 = countEvenInSeq3Range(0,2,0,3);
  printf("countEvenInSeg3Range(0, 2, 0, 3) = %d\n", evencnt1);
  int evencnt2 = countEvenInSeq3Range(-5,0,0,5);
  printf("countEvenInSeg3Range(-5, 0, 0, 5) = %d\n", evencnt2);  
  int evencnt3 = countEvenInSeq3Range(3,1,1,3);
  printf("countEvenInSeg3Range(3, 1, 1 ,3) = %d\n", evencnt3);

  return EXIT_SUCCESS;
}
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
// 
// Be sure to #include any header files you need!

