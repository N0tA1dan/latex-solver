#pragma once

#include "lexer.hpp"
#include <memory>
#include <variant>
#include <vector>

enum class OpType {
  ADD,
  SUB,
  MULTIPLY,
  DIVIDE,
  POWER,
};

struct VariableLit {
  Token val;
};

struct NumberLit {
  Token val;
};

struct ExpressionNode;

struct OpNode {
  OpType type;

  std::unique_ptr<ExpressionNode> left;
  std::unique_ptr<ExpressionNode> right;
};

struct ExpressionNode {
  std::variant<std::unique_ptr<OpNode>, std::unique_ptr<VariableLit>,
               std::unique_ptr<NumberLit>, std::unique_ptr<ExpressionNode>>
      var;
};

class Parser {
private:
  size_t m_index = 0;
  std::vector<Token> m_tokens;

  std::unique_ptr<ExpressionNode> m_expression;

  Token eat() { return m_tokens.at(m_index++); }

  std::optional<Token> peek(size_t offset = 0) {
    if (m_index + offset >= m_tokens.size()) {
      return std::nullopt;
    } else {
      return m_tokens.at(m_index + offset);
    }
  }

public:
  Parser() = default;

  Parser(const std::vector<Token> &tokens) : m_tokens(tokens) {}

  ~Parser() = default;

  void TryEat(TokenType type);

  std::unique_ptr<ExpressionNode> ParseAtomic();
  std::unique_ptr<ExpressionNode> ParsePower();
  std::unique_ptr<ExpressionNode> ParseFactor();
  std::unique_ptr<ExpressionNode> ParseTerm();
  std::unique_ptr<ExpressionNode> ParseExpression();

  void Parse();
};
