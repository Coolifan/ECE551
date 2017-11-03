#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "set.h"

template<typename T>
  class BstSet : public Set<T> {
  class Node {
  public:
    T nodekey;
    Node * left;
    Node * right;
  Node(const T & t) : nodekey(t), left(NULL), right(NULL) {}
  };

  Node * root;
  
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  void copyhelper(Node * ptr) {
    if (ptr != NULL) {
      add(ptr->nodekey);
      copyhelper(ptr->left);
      copyhelper(ptr->right);
    }
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet<T> & rhs): root(NULL) {
    copyhelper(rhs.root);
  }
  
  BstSet<T> & operator= (const BstSet<T> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = NULL;
      copyhelper(rhs.root);
    }
    return *this;
  }
 
  void add(const T & key);
  bool contains(const T & key) const;
  void remove(const T & key);
  ~BstSet<T>();
  void printInorder(Node * current) {
    if (current != NULL) {
      printInorder(current->left);
      std::cout << current->nodekey << std::endl;
      printInorder(current->right);
    }
  }
  void print() {
    printInorder(this->root);
  }
};


//////implementation
template<typename T>
  void BstSet<T>::add(const T & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->nodekey) {
      current = &(*current)->left;
    }
    else if (key > (*current)->nodekey) {
      current = &(*current)->right;
    }
    else if (key == (*current)->nodekey) {
      return;
    }
  }

  *current = new Node(key);
}


template<typename T>
bool BstSet<T>::contains(const T & key) const {
  Node * current = root;
  while (current != NULL) {
    if (key == current->nodekey) {
      return true;
    }
    else if (key < current->nodekey) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  return false;
}

template<typename T>
void BstSet<T>::remove(const T & key) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->nodekey) {
      current = &((*current)->left);
      continue;
    }
    else if (key > (*current)->nodekey) {
      current = &((*current)->right);
      continue;
    }
    else {
      if ((*current)->left == NULL) {
	Node * tempR = (*current)->right;
	delete *current;
	*current = tempR;
	return;
      }
      else if ((*current)->right == NULL) {
	Node * tempL = (*current)->left;
	delete *current;
	*current = tempL;
	return;
      }
      else {
	Node * replacement = (*current)->left;
	Node ** rep = &(*current)->left;
	if (replacement->right != NULL) {
	  while (replacement->right != NULL) {
	    if (replacement->right->right == NULL) {
	      break;
	    }
	    rep = &(*rep)->right;
	    replacement = replacement->right;
	  }
	  T tempkey = replacement->right->nodekey;     
	  Node * remainleft = replacement->right->left;
	  delete replacement->right;
	  (*rep)->right = remainleft;
	  (*current)->nodekey = tempkey;
	  return;
	}
	else {
	  T tempkey = replacement->nodekey;
	  Node * remainleft = replacement->left;
	  delete replacement;
	  (*current)->left = remainleft;
	  (*current)->nodekey = tempkey;
	  return;
	}
      }
    }
  }

}

template<typename T>
  BstSet<T>::~BstSet<T> () {
  destroy(root);
}
