#ifndef __MEMO_CONFIG_MODEL_H__
#define __MEMO_CONFIG_MODEL_H__
#include <string>
#include <variant>
#include <vector>

namespace memo {

struct Option {
  Option() = default;
  Option(std::string name, std::string description)
      : name(std::move(name)), description(std::move(description)) {}

  std::string name;
  std::string description;
  char shortName = '\0';
  std::variant<int64_t, bool, std::string> value;
};

struct ExecutorShell {
  std::string script;
};

struct ExecutorPlugin {
  std::string library;
  std::string symbol;
};
using Executor = std::variant<size_t, ExecutorShell, ExecutorPlugin>;

struct Command {
  std::string name;
  std::string description;
  std::vector<Option> options;
  Executor executor;

  Command* parent = nullptr;
  std::vector<Command*> subCommands;
};

using PluginFn = void (*)(const Command&);

} // namespace memo
#endif
