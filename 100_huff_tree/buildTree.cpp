#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node* dequed1 = pq.top();
    pq.pop();
    Node* dequed2 = pq.top();
    pq.pop();
    pq.push(new Node(dequed1, dequed2));
  }
  return pq.top();
}  
