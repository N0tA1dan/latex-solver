#include "lexer.hpp"
#include "parser.hpp"
#include <bits/time.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {

  std::string source = "\\frac{d}{dx}x^2";

  Lexer lexer(source);
  lexer.lex();
  // lexer.printTokens();

  std::vector<Token> tokens = lexer.getTokens();

  Parser parser(tokens);
  parser.Parse();
}
