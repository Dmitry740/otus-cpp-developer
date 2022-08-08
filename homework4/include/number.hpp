#pragma once

#include <string>

#include "astnode.hpp"

class Number : public ASTNode {
  public:
    Number(int val) : ASTNode(std::to_string(val)), val_(val) {}

    int value() const { 
      return val_; 
    }

    Number(const Number& other) = delete;
    Number& operator=(const Number& other) = delete;
    ~Number();

  private:
    int val_;
};