#include "Stack.h"
#include <stdio.h>

template<class T>
Stack<T>::Stack(){
  topNode = NULL;
}

template <class T>
bool Stack<T>::isEmpty(){
  if (top() == NULL){
    return true;
  }
  else{
    return false;
  }
}

template <class T>
void Stack<T>::push(T input){
  if (isEmpty()){
    node* newNode = new node();
    newNode->value = input;
    topNode = newNode;
  }
  else{
    node* newNode = new node();
    newNode->value = input;
    newNode->next = top;
    top = newNode;
  }
}

template <class T>
void Stack<T>::pop(){
  if (isEmpty() == false){
    node* temp = top;
    topNode = topNode->next;
    delete(temp);
  }
}

template <class T>
T Stack<T>::top(){
  return topNode->value;
}
