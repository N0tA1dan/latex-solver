#include "lexer.hpp"
#include "parser.hpp"
#include "solver.hpp"
#include <bits/time.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

int main() {

  std::string source = "-x^2 + 2x - 2";

  Lexer lexer{source};
  lexer.lex();
  // lexer.printTokens();

  std::vector<Token> tokens = lexer.getTokens();

  Parser parser{tokens};
  parser.Parse();

  auto expr = parser.Expression();

  Solver solver{std::move(expr)};
}
