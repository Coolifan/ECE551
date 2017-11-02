#include<cstdlib>
#include<iostream>
#include"function.h"
#include<cstdio>

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  /* if (f->invoke(low) < 0 && f->invoke(high) < 0) {
    return high-1;
  }
  if (f->invoke(low) > 0 && f->invoke(high) > 0) {
    return low;
  }
  */
  int mid = low + (high - low) / 2;
  if (low == mid) {
    return low;
  }
  if (f->invoke(mid) > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else{ //if (f->invoke(mid) < 0) {
    return binarySearchForZero(f, mid, high);
  }
//else{
//   return mid;
// }
}
