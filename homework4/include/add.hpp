#pragma once

#include <string>

#include "astnode.hpp"

class Add : public ASTNode {
    public:
        Add(ASTNode *lhs, ASTNode *rhs) : ASTNode{"+", lhs, rhs} {}
        Add(const Add& other) = delete;
        Add& operator=(const Add& other) = delete;
        ~Add();
};