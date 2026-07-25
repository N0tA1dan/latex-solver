#include "parser.hpp"
#include <memory>

class Solver {
private:
  std::vector<std::string> m_steps;
  std::unique_ptr<ExpressionNode> m_expression;

public:
  Solver(std::unique_ptr<ExpressionNode> expr)
      : m_expression(std::move(expr)) {}
};
