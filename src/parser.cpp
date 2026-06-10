#include "parser.hpp"


void Parser::TryEat(TokenType type){
  if(peek().has_value() and peek().value().type == type) eat();
  else{
    std::cerr << "error trying to eat token" << std::endl;
    exit(EXIT_FAILURE);
  }
}

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

      case TokenType::OPEN_PAREN:
        {
          eat(); // eat open parentheses;
          auto expr = std::make_unique<ExpressionNode>();
          expr = ParseExpression();
          eat(); // eats closing parentheses 
          primary->var = std::move(expr);

          break;
        }

      case TokenType::OPEN_BRACE:
        {
          eat(); // eat open brace
          auto expr = std::make_unique<ExpressionNode>();
          expr = ParseExpression();
          eat(); // eats closing brace 
          primary->var = std::move(expr);

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

      // handles x/2
      case TokenType::FORWARD_SLASH:
        {
          eat(); // eat / symbol
          auto rhs = ParsePrimaryExpression();
          auto rhsexpr = std::make_unique<ExpressionNode>();
          rhsexpr->var = std::move(rhs);

          auto opnode = std::make_unique<OpNode>();

          opnode->type = OpType::DIVIDE;

          opnode->left = std::move(lhsexpr);
          opnode->right = std::move(rhsexpr);

          auto newexpression = std::make_unique<ExpressionNode>();
          newexpression->var = std::move(opnode);

          lhsexpr = std::move(newexpression);

          break;
        }


      default:
        {
          break;
        }
    }

  }

  return lhsexpr;


}

std::unique_ptr<ExpressionNode> Parser::ParseTerm(){
  auto lhs = ParseFactor();

  if(peek().has_value()){
    switch(peek().value().type){
      case TokenType::PLUS:
        {
          eat(); // eat the symbol
          auto rhs = ParsePrimaryExpression();
          auto rhsexpr = std::make_unique<ExpressionNode>();
          rhsexpr->var = std::move(rhs);

          auto opnode = std::make_unique<OpNode>();

          opnode->type = OpType::ADD;

          opnode->left = std::move(lhs);
          opnode->right = std::move(rhsexpr);

          auto newexpression = std::make_unique<ExpressionNode>();
          newexpression->var = std::move(opnode);

          lhs = std::move(newexpression);

          break;
        }

      case TokenType::MINUS:
        {

          eat(); // eat the symbol
          auto rhs = ParsePrimaryExpression();
          auto rhsexpr = std::make_unique<ExpressionNode>();
          rhsexpr->var = std::move(rhs);

          auto opnode = std::make_unique<OpNode>();

          opnode->type = OpType::SUB;

          opnode->left = std::move(lhs);
          opnode->right = std::move(rhsexpr);

          auto newexpression = std::make_unique<ExpressionNode>();
          newexpression->var = std::move(opnode);

          lhs = std::move(newexpression);

          break;
        }

      default: 
        {
          break;
        }

    }

  }


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
