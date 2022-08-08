#pragma once

#include <string>

#include "astnode.hpp"

class Variable : public ASTNode {
  public:
    Variable(std::string name) : ASTNode{std::string(name)}, name_{name} {}

    std::string num() const { 
      return name_; 
    }

    Variable(const Variable& other) = delete;
    Variable& operator=(const Variable& other) = delete;
    ~Variable();

  private:
    std::string name_;
};