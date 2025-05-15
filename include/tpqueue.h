// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <stdexcept>
struct SYM {
  char ch;
  int prior;
};

template<typename T>
class TPQueue {
private:
  struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
  };

  Node* head;

public:
  TPQueue() : head(nullptr) {}
  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  bool isEmpty() const {
    return head == nullptr;
  }

  void push(const T& val) {
    Node* newNode = new Node(val);
    if (isEmpty() || head->data.prior < val.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->data.prior >= val.prior) {
      cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
  }

  T pop() {
    if (isEmpty()) {
      throw std::out_of_range("Queue is empty");
    }

    Node* temp = head;
    T val = head->data;
    head = head->next;
    delete temp;

    return val;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
