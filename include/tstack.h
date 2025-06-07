// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int SIZE>
class TStack {
private:
    T data[SIZE];
    int top;
public:
    TStack() : top(-1) {}
    void push(const T& value) {
        if (top < SIZE - 1) {
            data[++top] = value;
        }
    }
    T pop() {
        if (top >= 0) {
            return data[top--];
        }
        return T(); // Возвращаем значение по умолчанию, если стек пуст
    }
    T peek() const {
        if (top >= 0) {
            return data[top];
        }
        return T();
    }
    bool isEmpty() const {
        return top == -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
