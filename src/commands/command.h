#pragma once

#include <string>
#include <variant>

struct ParseError {
  std::string message;
};

template <typename T> using ParseResult = std::variant<T, ParseError>;