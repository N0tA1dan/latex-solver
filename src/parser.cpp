#include "parser.hpp"

std::unique_ptr<PrimaryExpression> Parser::ParsePrimaryExpression(){
  auto primary = std::make_unique<PrimaryExpression>();

  if(peek().has_value()){
    switch(peek().value().type){
      case TokenType::NUMBER:
        {

          auto num = std::make_unique<NumberLit>();
          num->val = eat();
          primary->var = std::move(num);

          break;
        }

      case TokenType::VARIABLE:
        {
          auto variable = std::make_unique<VariableLit>();
          variable->val = eat();
          primary->var = std::move(variable);

          break;
        }

      default:
        {
          std::cerr << "error: unknown error in ParsePrimaryExpression()" << std::endl;
          break;
        }

    }

  }

  return primary;

}

std::unique_ptr<ExpressionNode> Parser::ParseFactor(){
  auto lhsexpr = std::make_unique<ExpressionNode>();

  auto lhs = ParsePrimaryExpression();

  lhsexpr->var = std::move(lhs);

  if(peek().has_value()){
    switch(peek().value().type){
      // handles multiplication 
      case TokenType::ASTERISK: case TokenType::CDOT:
        {
          eat(); // eat the symbol
          auto rhs = ParsePrimaryExpression();
          auto rhsexpr = std::make_unique<ExpressionNode>();
          rhsexpr->var = std::move(rhs);

          auto opnode = std::make_unique<OpNode>();

          opnode->type = OpType::MULTIPLY;

          opnode->left = std::move(lhsexpr);
          opnode->right = std::move(rhsexpr);

          auto newexpression = std::make_unique<ExpressionNode>();
          newexpression->var = std::move(opnode);

          lhsexpr = std::move(newexpression);

          break;
        }

      // handles cases like 2x
      case TokenType::VARIABLE:
        {

          break;
        }

      // handles x/2
      case TokenType::FORWARD_SLASH:
        {
          break;
        }

      // fraction division
      case TokenType::FRAC:
        {

          break;
        }


      default:
        {
          break;
        }
    }

  }

  std::cout <<"done parsing factor"<<std::endl;
  return lhsexpr;


}

std::unique_ptr<ExpressionNode> Parser::ParseTerm(){
  auto lhs = ParseFactor();
  return lhs;
}

std::unique_ptr<ExpressionNode> Parser::ParseExpression(){
  auto expression = ParseTerm();

  return expression;

}

void Parser::Parse(){

  auto expression = std::make_unique<ExpressionNode>();

  expression = ParseExpression();

  m_expression = std::move(expression);


}
