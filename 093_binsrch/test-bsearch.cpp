#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstdio>
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};


class F1: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg;
  }
};
class F2: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    if (arg <= 0) {
      return -123;
    }
    else if (arg >= 1000) {
      return 1234;
    }
    else {
      return 0;
    }
  }
};
class F3: public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return -arg+1;
  }
};
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int n = (high > low) ? log2(high-low)+1 : 1;
  CountedIntFn count(n, f, mesg);
  int result = binarySearchForZero(&count , low, high);
  if (result != expected_ans) {
    std::cout << "When high = " << high << "and low = " << low << std::endl;
    std::cout << "ans != " << result << std::endl;
    exit(EXIT_FAILURE);
  }

}
int main(int argc, char ** argv) {
  F1 myf1;
  F2 myf2;
  F3 myf3;
  check(&myf1, -1, 3, 0, "myf1.0");
  // check(&myf1, -5, -1, -2, "myf1.1");
  //check(&myf1, 1, 5, 1, "myf1.2");
  //check(&myf1, 1, 1, 1, "myf1.3");
  //  check(&myf2, 0, 1000, 500 , "myf2.0");
  //check(&myf3, -1, 5,4, "myf3.0");
  return EXIT_SUCCESS;
}
