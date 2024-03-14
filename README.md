# Command Parser System

This is a simple command parser system written in C++17. It provides a type-safe and extensible way to parse and execute commands in a game or application.

## Features

- **Type-Safe Command Parsing**: Utilizes `std::variant` and templates to ensure type safety across different command types.
- **Modern C++ Practices**: Incorporates modern C++17 and C++20 features for efficient and readable code.
- **Extensible Command Registration**: Easily extendable with new commands without modifying the core parsing logic.
- **Error Handling**: Provides a structured approach to error handling, avoiding exceptions in favor of result variants.

## Requirements

- C++17 compiler or newer
- Standard Template Library (STL)

## Example

Given the predefined `MoveCommand` and `AttackCommand`, you can execute commands like:

```
/move 10 15
/attack enemy_base
```

These commands will be parsed and executed, resulting in actions defined in their respective `execute` methods.

## Extending the System

To extend the system with more commands, follow the pattern established by `MoveCommand` and `AttackCommand`. Define the command structure, implement the parse and execute methods, put it into the `GameCommand` varient and register the command with the `CommandParser`.

## License

This project is open-sourced under the MIT License. See the LICENSE file for more details.