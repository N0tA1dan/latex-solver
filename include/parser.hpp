#pragma once

#include "lexer.hpp"
#include <variant>
#include <memory>
#include <iostream>
#include <vector>

enum class OpType{
  ADD,
  SUB,
  MULTIPLY,
  DIVIDE,
};

struct VariableLit{
  Token val;
};

struct NumberLit{
  Token val;
};

struct PrimaryExpression{
  std::variant<std::unique_ptr<VariableLit>, std::unique_ptr<NumberLit>> var;

};

struct ExpressionNode;

struct OpNode{
  OpType type;

  std::unique_ptr<ExpressionNode> left;
  std::unique_ptr<ExpressionNode> right;

};

struct ExpressionNode{
  std::variant<std::unique_ptr<OpNode>, std::unique_ptr<PrimaryExpression>> var;
};

class Parser{
  private:
    size_t m_index = 0;
    std::vector<Token> m_tokens;

    std::unique_ptr<ExpressionNode> m_expression;

    Token eat(){
      return m_tokens.at(m_index++);
    }

    std::optional<Token> peek(size_t offset = 0){
      if(m_index + offset >= m_tokens.size()){
        return std::nullopt;
      } else{
        return m_tokens.at(m_index + offset);

      }
    }

  public:
    Parser() = default;

    Parser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

    ~Parser() = default;


    std::unique_ptr<PrimaryExpression> ParsePrimaryExpression();
    std::unique_ptr<ExpressionNode> ParseFactor();
    std::unique_ptr<ExpressionNode> ParseTerm();
    std::unique_ptr<ExpressionNode> ParseExpression();

    void Parse();



};


