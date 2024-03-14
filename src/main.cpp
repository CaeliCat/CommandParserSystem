
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "commands/attack.h"
#include "commands/move.h"

using GameCommand = std::variant<MoveCommand, AttackCommand, ParseError>;

template <class... Ts> struct overload : Ts... {
  using Ts::operator()...;
};

template <class... Ts> overload(Ts...) -> overload<Ts...>;

void executeCommand(const ParseResult<GameCommand> &result) {
  std::visit(overload{[](const GameCommand &cmd) {
                        auto executeCommand = [](const GameCommand &command) {
                          std::visit(
                              overload{[](const auto &cmd) { cmd.execute(); },
                                       [](const ParseError &error) {
                                         std::cerr << "Error: " << error.message
                                                   << std::endl;
                                       }},
                              command);
                        };
                        executeCommand(cmd);
                      },
                      [](const ParseError &error) {
                        std::cerr << "Error: " << error.message << std::endl;
                      }},
             result);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

class CommandParser {
private:
  std::unordered_map<std::string, std::function<ParseResult<GameCommand>(
                                      const std::vector<std::string> &)>>
      parsers;

public:
  void registerCommand(
      const std::string &commandName,
      std::function<ParseResult<GameCommand>(const std::vector<std::string> &)>
          parser) {
    parsers[commandName] = parser;
  }

  ParseResult<GameCommand> parseCommand(const std::string &input) {
    auto tokens = split(input, ' ');
    if (tokens.empty())
      return ParseError{"Empty command"};

    auto it = parsers.find(tokens[0]);
    if (it == parsers.end())
      return ParseError{"Unknown command"};

    return it->second(tokens);
  }
};

int main() {
  CommandParser parser;

  parser.registerCommand(
      "/move",
      [](const std::vector<std::string> &args) -> ParseResult<GameCommand> {
        auto parseResult = MoveCommand::parse(args);
        return std::visit(
            overload{
                [](const MoveCommand &cmd) -> GameCommand { return cmd; },
                [](const ParseError &error) -> GameCommand { return error; }},
            parseResult);
      });

  parser.registerCommand(
      "/attack",
      [](const std::vector<std::string> &args) -> ParseResult<GameCommand> {
        auto parseResult = AttackCommand::parse(args);
        return std::visit(
            overload{
                [](const AttackCommand &cmd) -> GameCommand { return cmd; },
                [](const ParseError &error) -> GameCommand { return error; }},
            parseResult);
      });

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "exit")
      break;
    auto result = parser.parseCommand(line);
    executeCommand(result);
  }
  return 0;
}
