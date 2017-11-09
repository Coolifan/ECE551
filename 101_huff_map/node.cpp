#include "node.h"
#include <iostream>

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert(left == NULL && right == NULL);
    theMap[sym] = b;
    return;
  }
  else {
    assert(left != NULL && right != NULL);

    BitString temp_lb = b.plusZero();
    left->buildMap(temp_lb, theMap);
    BitString temp_rb = b.plusOne();
    right->buildMap(temp_rb, theMap);
    
  }
}

