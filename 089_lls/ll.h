#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
  public:
    T data;
    Node * next;
    Node * prev;
  Node(const T & d) : data(d), next(NULL), prev(NULL) {}
  Node(const T & d, Node * n) : data(d), next(n), prev(NULL) {}
  Node(const T & d, Node * n, Node * p) : data(d), next(NULL), prev(p) {}
  };
  
  Node * head;
  Node * tail;
  int size;
  bool remove(const T & item, Node * current);
  void destroy() {
    while (head != NULL) {
    Node * temp = head->next;
    delete head;
    head = temp;
    }
  }
 public:
  LinkedList();
  void addFront(const T &item);
  void addBack(const T &item);
  bool remove(const T &item) {
    return remove(item, head);
  }
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T &item);
  LinkedList(const LinkedList<T> & rhs);
  LinkedList<T> & operator=(const LinkedList<T> & rhs);
  ~LinkedList();
  const int getSize() const;
  
};

class myException: public std::exception {
  virtual const char * what() const throw() {
    const char * str = "Invalid index";
    return str;
  }
};
//////method implementation
template<typename T>
LinkedList<T>::LinkedList() : head(NULL), tail(NULL), size(0) {}

template<typename T>
void LinkedList<T>::addFront(const T &item) {
  head = new Node(item, head);
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
void LinkedList<T>::addBack(const T &item) {
  tail = new Node(item, NULL, tail);
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item, Node * current) {
  if (current == NULL) {
    return false;
  }
  else if (current->data == item) {
    if (current->prev == NULL) {
      head = current->next;
    }
    else {
      current->prev->next = current->next;
    }
    
    if (current->next == NULL) {
      tail = current->prev;
    }
    else {
      current->next->prev = current->prev;
    }

    delete current;
    size--;
    return true;
  }
  else {
    return remove(item, current->next);
  }
}

template<typename T>
T & LinkedList<T>::operator[] (int index) {
  Node * temp1 = head;
  if (index < 0 || index > size-1) {
    throw myException();
  }
  for (int i = 0; i < index; i++) {
    temp1 = temp1->next;
  }
  return temp1->data;  
  
}

template<typename T>
const T & LinkedList<T>::operator[] (int index) const  {
  Node * temp1 = head;
  if (index < 0 || index > size-1) {
    throw myException();
  }
  for (int i = 0; i < index; i++) {
    temp1 = temp1->next;
  }
  return temp1->data;  
  
}
template<typename T>
int LinkedList<T>::find(const T & item) {
  Node * temp2 = head;
  for (int i = 0; i < size; i++) {
    if (temp2->data == item) {
      return i;
    }
    temp2 = temp2->next;
  }
  return -1;
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs) {
  if (this != &rhs) {
    destroy();
    head = NULL;
    tail = NULL;
    size = 0;
    
    Node * ptr = rhs.tail;
    while (ptr != NULL) {
      addFront(ptr->data);
      ptr = ptr->prev;
    }
    
    return *this;
}
}
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & rhs) : head(NULL), tail(NULL), size(0)  {
    //*this = rhs;
    Node * ptr = rhs.head;
    while (ptr != NULL) {
      addBack(ptr->data);
      ptr = ptr->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList() {
  destroy();
}

template<typename T>
const int LinkedList<T>::getSize() const {
  return size;
}
#endif
