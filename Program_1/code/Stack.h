#ifndef STACK_H
#define STACK_H

template <class T>
class Stack{
private:
  class node{
    T value;
    node* next;
  };
  node* topNode;
public:
  Stack();
  void push(T input);
  bool isEmpty();
  void pop();
  T top();

};
#endif
