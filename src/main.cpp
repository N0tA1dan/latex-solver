#include "lexer.hpp"
#include "parser.hpp"

int main(){


    std::string source = "2 * 2";

    Lexer lexer(source);

    lexer.lex();
    lexer.printTokens();

    std::vector<Token> tokens = lexer.getTokens();

    Parser parser(tokens);
    parser.Parse();
}
