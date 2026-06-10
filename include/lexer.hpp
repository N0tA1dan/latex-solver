#pragma once 
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

enum class TokenType{
  FRAC,
  INTEGRAL,
  LIMIT,
  SUM,
  INFTY,
  VARIABLE,
  UDELTA,
  NUMBER,
  EQUALS,
  PLUS,
  MINUS,
  CDOT,
  ASTERISK,
  OPEN_BRACE,
  CLOSE_BRACE,
  OPEN_PAREN,
  CLOSE_PAREN,
  UNDERSCORE,
  FORWARD_SLASH,
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

class Lexer{
  private:
    std::string m_source;
    size_t m_index = 0;

    std::vector<Token> m_tokens;

    std::unordered_map<std::string, TokenType> m_map{
      {"int", TokenType::INTEGRAL},
      {"lim", TokenType::LIMIT},
      {"frac", TokenType::FRAC},
      {"infty", TokenType::INFTY},
      {"Delta", TokenType::UDELTA},
      {"cdot", TokenType::CDOT},
      {"sum", TokenType::SUM},
    };

    char eat(){
      return m_source.at(m_index++);
    }

    std::optional<char> peek(size_t offset = 0){
      if(m_index + offset >= m_source.length()){
        return std::nullopt;
      } else{
        return m_source.at(m_index + offset);

      }
    }


  public:
    Lexer() = default;
    Lexer(const std::string& source) : m_source(source) {}
    ~Lexer() = default;

    void lex();
    void printTokens();
    std::vector<Token> getTokens();



};
