#include "lexer.hpp"
#include "parser.hpp"

int main(){


    std::string source = "\\sum_";

    Lexer lexer(source);

    lexer.lex();
    lexer.printTokens();
}
