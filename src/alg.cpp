// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

namespace {
int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::stringstream output;
  bool prevWasDigit = false;

  for (char ch : inf) {
    if (isspace(ch)) continue;

    if (isdigit(ch)) {
      if (prevWasDigit) {
        output << ch;
      } else {
        if (!output.str().empty()) output << ' ';
        output << ch;
      }
      prevWasDigit = true;
    } else {
      prevWasDigit = false;
      if (ch == '(') {
        stack.push(ch);
      } else if (ch == ')') {
        while (!stack.isEmpty() && stack.peek() != '(') {
          output << ' ' << stack.pop();
        }
        stack.pop(); // Удаляем '(' из стека
      } else {
        while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
          output << ' ' << stack.pop();
        }
        stack.push(ch);
      }
    }
  }

  while (!stack.isEmpty()) {
    output << ' ' << stack.pop();
  }

  return output.str();
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int right = stack.pop();
      int left = stack.pop();
      switch (token[0]) {
        case '+': stack.push(left + right); break;
        case '-': stack.push(left - right); break;
        case '*': stack.push(left * right); break;
        case '/': stack.push(left / right); break;
      }
    }
  }
  return stack.pop();
}
