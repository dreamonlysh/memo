#include "memo.h"
#include <CLI/CLI.hpp>
#include <chrono>
#include <iostream>

namespace {
using namespace memo;

bool g_trace = false;

struct TraceScope {
  std::string name;
  std::chrono::high_resolution_clock::time_point t0;
  TraceScope(std::string n)
      : name(std::move(n)), t0(std::chrono::high_resolution_clock::now()) {
    if (g_trace) {
      std::cerr << "[trace] start " << name << "\n";
    }
  }
  ~TraceScope() {
    if (g_trace) {
      auto t1 = std::chrono::high_resolution_clock::now();
      std::cerr << "[trace] end " << name << " "
                << std::chrono::duration_cast<std::chrono::milliseconds>(t1 -
                                                                         t0)
                       .count()
                << " ms\n";
    }
  }
};

std::string genOptionName(const Option& option) {
  std::string name;
  name.reserve(option.name.size() + 8);
  if (option.shortName != '\0') {
    name += "-";
    name += option.shortName;
    name += ",";
  }
  name += "--";
  name += option.name;
  return name;
}

void buildCli(CLI::App& app, Command& cmd) {
  CLI::App* subApp = app.add_subcommand(cmd.name, cmd.description);
  for (auto& c : cmd.subCommands) {
    buildCli(*subApp, *c);
  }

  for (auto& option : cmd.options) {
    std::visit(overloaded{[&option, subApp](std::string& s) {
                            subApp->add_option(genOptionName(option), s,
                                               option.description);
                          },
                          [&option, subApp](int64_t& v) {
                            subApp->add_option(genOptionName(option), v,
                                               option.description);
                          },
                          [&option, subApp](bool& v) {
                            subApp->add_flag(genOptionName(option), v,
                                             option.description);
                          }},
               option.value);
  }

  if (cmd.executor.index() != 0) {
    subApp->callback([&cmd]() { execute(cmd); });
  }
}
} // namespace

int main(int argc, char** argv) {
  auto yaml =
      std::filesystem::path(std::getenv("HOME")) / ".memo" / "memo.yaml";
  std::deque<memo::Command> cmds = memo::loadConfig(yaml.string());

  CLI::App app{"memo is a memo to keep commands instead of in mind"};
  app.add_flag("--trace", g_trace, "trace execution");
  for (auto& c : cmds) {
    if (c.parent == nullptr) {
      buildCli(app, c);
    }
  }

  CLI11_PARSE(app, argc, argv);
  return 0;
}
