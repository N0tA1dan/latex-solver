#include "lexer.hpp"

void Lexer::lex() {
  std::string buffer;
  while (peek().has_value()) {

    // handles symbols and whatever
    if (peek().value() == '\\') {
      eat(); // eats backslash

      while (peek().has_value() and std::isalpha(peek().value())) {
        buffer.push_back(eat());
      }

      if (m_map.find(buffer) != m_map.end()) {
        m_tokens.push_back({m_map.at(buffer), std::nullopt});
      }

      buffer.clear();
      continue;

    }

    // handles numbers
    else if (std::isdigit(peek().value())) {
      buffer.push_back(eat()); // eats first digit and adds to buffer

      while (peek().has_value() and std::isdigit(peek().value())) {
        buffer.push_back(eat());
      }

      m_tokens.push_back({TokenType::NUMBER, buffer});
      buffer.clear();
      continue;

    }

    // lexes variables
    else if (std::isalpha(peek().value())) {

      buffer.push_back(eat());

      m_tokens.push_back({TokenType::VARIABLE, buffer});
      buffer.clear();
      continue;

    }

    else if (std::isspace(peek().value())) {
      eat();
      continue;
    }

    else if (peek().value()) {
      TokenType type;

      switch (peek().value()) {
      case '=':
        type = TokenType::EQUALS;
        break;

      case '+':
        type = TokenType::PLUS;
        break;

      case '-':
        type = TokenType::MINUS;
        break;

      case '*':
        type = TokenType::ASTERISK;
        break;

      case '^':
        type = TokenType::CARET;
        break;

      case '{':
        type = TokenType::OPEN_BRACE;
        break;

      case '}':
        type = TokenType::CLOSE_BRACE;
        break;

      case '(':
        type = TokenType::OPEN_PAREN;
        break;

      case ')':
        type = TokenType::CLOSE_PAREN;
        break;

      case '_':
        type = TokenType::UNDERSCORE;
        break;

      case '/':
        type = TokenType::FORWARD_SLASH;
        break;

      default:
        std::cerr << "error: unknown operator or symbol '" << peek().value()
                  << std::endl;
        break;
      }

      m_tokens.push_back({type, std::nullopt});
      eat(); // eats the symbol

      continue;
    }

    else {
      std::cerr << "ERROR: Unknown character detected" << std::endl;
      eat();
    }
  }
}

std::vector<Token> Lexer::getTokens() { return m_tokens; }

void Lexer::printTokens() {
  for (const auto &token : m_tokens) {
    switch (token.type) {
    case TokenType::INTEGRAL:
      std::cout << "INTEGRAL TOKEN" << std::endl;
      break;

    case TokenType::FRAC:
      std::cout << "FRAC TOKEN" << std::endl;
      break;

    case TokenType::LIMIT:
      std::cout << "LIMIT TOKEN" << std::endl;
      break;

    case TokenType::SUM:
      std::cout << "SUM TOKEN" << std::endl;
      break;

    case TokenType::NUMBER:
      std::cout << "NUMBER TOKEN WITH VALUE: " << token.value.value()
                << std::endl;
      break;

    case TokenType::VARIABLE:
      std::cout << "VARIABLE TOKEN WITH VALUE: " << token.value.value()
                << std::endl;
      break;

    case TokenType::INFTY:
      std::cout << "INFTY TOKEN" << std::endl;
      break;

    case TokenType::EQUALS:
      std::cout << "EQUALS TOKEN" << std::endl;
      break;

    case TokenType::PLUS:
      std::cout << "PLUS TOKEN" << std::endl;
      break;

    case TokenType::MINUS:
      std::cout << "MINUS TOKEN" << std::endl;
      break;

    case TokenType::CDOT:
      std::cout << "CDOT TOKEN" << std::endl;
      break;

    case TokenType::ASTERISK:
      std::cout << "ASTERISK TOKEN" << std::endl;
      break;

    case TokenType::CARET:
      std::cout << "CARETOKEN" << std::endl;
      break;

    case TokenType::OPEN_BRACE:
      std::cout << "OPEN_BRACE TOKEN" << std::endl;
      break;

    case TokenType::CLOSE_BRACE:
      std::cout << "CLOSE_BRACE TOKEN" << std::endl;
      break;

    case TokenType::OPEN_PAREN:
      std::cout << "OPEN_PAREN TOKEN" << std::endl;
      break;

    case TokenType::CLOSE_PAREN:
      std::cout << "CLOSE_PAREN TOKEN" << std::endl;
      break;

    case TokenType::UNDERSCORE:
      std::cout << "UNDERSCORE TOKEN" << std::endl;
      break;

    case TokenType::FORWARD_SLASH:
      std::cout << "FORWARD_SLASH TOKEN" << std::endl;
      break;

    default:
      std::cout << "Unknown token found" << std::endl;
      break;
    }
  }
}
