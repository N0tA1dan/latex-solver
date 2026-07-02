#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>

int main() {

  std::string source = "2 \\frac{x}{y}";

  Lexer lexer(source);

  lexer.lex();
  // lexer.printTokens();

  std::vector<Token> tokens = lexer.getTokens();

  Parser parser(tokens);
  parser.Parse();
}
