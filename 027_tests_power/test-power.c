#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);
void checkhelper(unsigned x, unsigned y, unsigned ans) {
  if(y < 0)
    exit(EXIT_FAILURE);
  unsigned result = power(x,y);
  if (result != ans)
    exit(EXIT_FAILURE);
}
int main(void)
{
   checkhelper(0,0,1);
   checkhelper(2,32,0);
   checkhelper(-1,32,1);
   checkhelper(-1,1,4294967295);

  return EXIT_SUCCESS;

}
