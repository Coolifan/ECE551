#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "map.h"

template<typename K, typename V>
  class BstMap : public Map<K, V> {
  class Node {
  public:
    K nodekey;
    V nodevalue;
    Node * left;
    Node * right;
  Node(const K & k, const V & v) : nodekey(k), nodevalue(v), left(NULL), right(NULL) {}
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
      add(ptr->nodekey, ptr->nodevalue);
      copyhelper(ptr->left);
      copyhelper(ptr->right);
    }
  }
  
 public:
 BstMap() : root(NULL) {}
 BstMap(const BstMap<K, V> & rhs): root(NULL) {
    Node * ptr = rhs.root;
    copyhelper(ptr);
  }
  BstMap<K, V> & operator= (const BstMap<K,V> & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = NULL;
      copyhelper(rhs.root);
      
    }
    return *this;
  }
  void add(const K & key, const V & value);
  const V & lookup(const K & key) const throw (std::invalid_argument);
  void remove(const K & key);
  ~BstMap<K, V>();
  void printInorder(Node * current) {
    if (current != NULL) {
      printInorder(current->left);
      std::cout << current->nodekey << "<->" << current->nodevalue << std::endl;
      printInorder(current->right);
    }
  }
  void print() {
    printInorder(this->root);
  }
};


//////implementation
template<typename K, typename V>
  void BstMap<K,V>::add(const K & key, const V & value) {
  Node ** current = &root;
  while (*current != NULL) {
    if (key < (*current)->nodekey) {
      current = &(*current)->left;
    }
    else if (key > (*current)->nodekey) {
      current = &(*current)->right;
    }
    else if (key == (*current)->nodekey) {
      (*current)->nodevalue = value;
      return;
    }
  }
  
  *current = new Node(key, value);
}


template<typename K, typename V>
  const V & BstMap<K,V>::lookup(const K & key) const throw (std::invalid_argument) {
  Node * current = root;
  while (current != NULL) {
    if (key == current->nodekey) {
      return current->nodevalue;
    }
    else if (key < current->nodekey) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  throw std::invalid_argument("the key is not found");
}

template<typename K, typename V>
  void BstMap<K, V>::remove(const K & key) {
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
	  K tempkey = replacement->right->nodekey;
	  V tempvalue = replacement->right->nodevalue;
	  Node * remainleft = replacement->right->left;
	  delete replacement->right;
	  (*rep)->right = remainleft;
	  (*current)->nodekey = tempkey;
	  (*current)->nodevalue = tempvalue;
	  return;
	}
	else {
	  K tempkey = replacement->nodekey;
	  V tempvalue = replacement->nodevalue;
	  Node * remainleft = replacement->left;
	  delete replacement;
	  (*current)->left = remainleft;
	  (*current)->nodekey = tempkey;
	  (*current)->nodevalue = tempvalue;
	  return;
	}	
      }
    }
  }  
}

template<typename K, typename V>
  BstMap<K, V>::~BstMap<K, V> () {
  destroy(root);
}
