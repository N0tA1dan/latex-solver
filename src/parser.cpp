#include "parser.hpp"
#include "lexer.hpp"
#include <memory>

void Parser::TryEat(TokenType type) {
  if (peek().has_value() and peek().value().type == type)
    eat();
  else {
    std::cerr << "error trying to eat token" << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::unique_ptr<ExpressionNode> Parser::ParseAtomic() {
  auto atomic = std::make_unique<ExpressionNode>();

  if (peek().has_value()) {
    switch (peek().value().type) {
    case TokenType::NUMBER: {

      auto num = std::make_unique<NumberLit>();
      num->val = eat();
      atomic->var = std::move(num);

      break;
    }

    case TokenType::VARIABLE: {
      auto variable = std::make_unique<VariableLit>();
      variable->val = eat();
      atomic->var = std::move(variable);

      break;
    }

    case TokenType::OPEN_PAREN: {
      eat(); // eat open parentheses;
      auto expr = ParseExpression();
      TryEat(TokenType::CLOSE_PAREN); // eats closing parentheses
      atomic = std::move(expr);
      break;
    }

    case TokenType::FRAC: {
      eat(); // eats frac token
      auto opNode = std::make_unique<OpNode>();
      opNode->type = OpType::DIVIDE;

      TryEat(TokenType::OPEN_BRACE);
      opNode->left = ParseExpression();
      TryEat(TokenType::CLOSE_BRACE);

      TryEat(TokenType::OPEN_BRACE);
      opNode->right = ParseExpression();
      TryEat(TokenType::CLOSE_BRACE);

      atomic->var = std::move(opNode);

      break;
    }

    default: {
      std::cerr << "error: unknown error in ParsePrimaryExpression()"
                << std::endl;
      break;
    }
    }
  }

  return atomic;
}

std::unique_ptr<ExpressionNode> Parser::ParseFactor() {

  auto lhsexpr = ParseAtomic();

  while (peek().has_value()) {
    switch (peek().value().type) {
    // handles multiplication
    case TokenType::ASTERISK:
    case TokenType::CDOT: {
      eat(); // eat the symbol
      auto rhsexpr = ParseAtomic();

      auto opnode = std::make_unique<OpNode>();

      opnode->type = OpType::MULTIPLY;

      opnode->left = std::move(lhsexpr);
      opnode->right = std::move(rhsexpr);

      auto newexpression = std::make_unique<ExpressionNode>();
      newexpression->var = std::move(opnode);

      lhsexpr = std::move(newexpression);

      break;
    }

    // handles cases like 2x or 2(expr)
    case TokenType::VARIABLE:
    case TokenType::OPEN_PAREN:
    case TokenType::FRAC: {
      auto rhsexpr = ParseAtomic();

      auto opnode = std::make_unique<OpNode>();

      opnode->type = OpType::MULTIPLY;

      opnode->left = std::move(lhsexpr);
      opnode->right = std::move(rhsexpr);

      auto newexpression = std::make_unique<ExpressionNode>();
      newexpression->var = std::move(opnode);

      lhsexpr = std::move(newexpression);

      break;
    }

    // handles x/2
    case TokenType::FORWARD_SLASH: {
      eat(); // eat / symbol
      auto rhsexpr = ParseAtomic();

      auto opnode = std::make_unique<OpNode>();

      opnode->type = OpType::DIVIDE;

      opnode->left = std::move(lhsexpr);
      opnode->right = std::move(rhsexpr);

      auto newexpression = std::make_unique<ExpressionNode>();
      newexpression->var = std::move(opnode);

      lhsexpr = std::move(newexpression);

      break;
    }

    default: {
      return lhsexpr;
    }
    }
  }

  return lhsexpr;
}

std::unique_ptr<ExpressionNode> Parser::ParseTerm() {
  auto lhsexpr = ParseFactor();

  while (peek().has_value()) {
    switch (peek().value().type) {
    case TokenType::PLUS: {
      eat(); // eat the symbol
      auto rhsexpr = ParseFactor();

      auto opnode = std::make_unique<OpNode>();

      opnode->type = OpType::ADD;

      opnode->left = std::move(lhsexpr);
      opnode->right = std::move(rhsexpr);

      auto newexpression = std::make_unique<ExpressionNode>();
      newexpression->var = std::move(opnode);

      lhsexpr = std::move(newexpression);

      break;
    }

    case TokenType::MINUS: {

      eat(); // eat the symbol
      auto rhsexpr = ParseFactor();

      auto opnode = std::make_unique<OpNode>();

      opnode->type = OpType::SUB;

      opnode->left = std::move(lhsexpr);
      opnode->right = std::move(rhsexpr);

      auto newexpression = std::make_unique<ExpressionNode>();
      newexpression->var = std::move(opnode);

      lhsexpr = std::move(newexpression);

      break;
    }

    default: {
      return lhsexpr;
    }
    }
  }

  return lhsexpr;
}

std::unique_ptr<ExpressionNode> Parser::ParseExpression() {
  auto expression = ParseTerm();

  return expression;
}

void Parser::Parse() {

  auto expression = std::make_unique<ExpressionNode>();

  expression = ParseExpression();

  m_expression = std::move(expression);
}
