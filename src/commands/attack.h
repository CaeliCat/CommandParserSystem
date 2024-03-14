#pragma once

#include "command.h"
#include <iostream>
#include <vector>

struct AttackCommand {
  std::string target;
  static ParseResult<AttackCommand>
  parse(const std::vector<std::string> &args) {
    if (args.size() != 2)
      return ParseError{"Invalid number of arguments for AttackCommand"};
    return AttackCommand{args[1]};
  }
  void execute() const { std::cout << "Attacking " << target << "\n"; }
};