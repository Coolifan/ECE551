#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "bstmap.h"

/*void printInorder(Node * current) {
  if (current != NULL) {
    printInorder(current->left);
    std::cout << current->nodekey << "<->" << current->nodevalue << std::endl;
    printInorder(current-<right);
  }
}
*/
int main(int argc, char ** argv) {
  BstMap<int, int> tree1;
  tree1.add(7,70);
  tree1.add(2,20);
  tree1.add(5,50);
  tree1.add(6,60);
  //  tree1.add(0,0);
  tree1.add(9,90);
  tree1.add(3,30);
  tree1.add(1,10);
  tree1.add(1,666);
  tree1.remove(7);
  try{
    int lookvalue = tree1.lookup(888);
    std::cout<<lookvalue<<std::endl;
  }
  catch (const std::invalid_argument & e) {
    std::cout<<"catched"<<std::endl;
  }
  BstMap<int, int> tree2(tree1);
  BstMap<int, int> tree3 = tree2;
  tree2.print();
  tree3.remove(5);
  tree3.print();

  
  tree1.print();
  
  return EXIT_SUCCESS;
  
}
