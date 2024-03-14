#pragma once

#include "command.h"
#include <charconv>
#include <iostream>
#include <vector>

struct MoveCommand {
  int x, y;
  static ParseResult<MoveCommand> parse(const std::vector<std::string> &args) {
    if (args.size() != 3)
      return ParseError{"Invalid number of arguments for MoveCommand"};
    int x, y;
    if (auto [p, ec] =
            std::from_chars(args[1].data(), args[1].data() + args[1].size(), x);
        ec != std::errc()) {
      return ParseError{"Invalid argument: non-integer value"};
    }
    if (auto [p, ec] =
            std::from_chars(args[2].data(), args[2].data() + args[2].size(), y);
        ec != std::errc()) {
      return ParseError{"Invalid argument: non-integer value"};
    }
    return MoveCommand{x, y};
  }
  void execute() const {
    std::cout << "Moving to (" << x << ", " << y << ")\n";
  }
};