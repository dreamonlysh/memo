#include "memo.h"
#include <deque>
#include <filesystem>
#include <iostream>
#include <stack>
#include <yaml-cpp/yaml.h>

namespace {
namespace fs = std::filesystem;
using namespace memo;

// Combine multiple config files into one
YAML::Node loadAllEntrySubCommands(const fs::path& rootCfgFilePath) {
  if (!fs::exists(rootCfgFilePath)) {
    std::cerr << "warning: missing the root config file: " << rootCfgFilePath
              << "\n";
    return {};
  }

  fs::path rootCfgPath = rootCfgFilePath.parent_path();

  YAML::Node rst;
  std::deque<fs::path> cfgFiles;
  cfgFiles.emplace_back(rootCfgFilePath);
  auto curor = cfgFiles.begin();
  while (curor != cfgFiles.end()) {
    const fs::path& cfgFile = *(curor++);
    YAML::Node root = YAML::LoadFile(cfgFile.string());
    if (!root.IsMap()) {
      std::cerr << "warning: invalid config file: " << cfgFile << "\n";
      continue;
    }

    for (auto it : root) {
      if (it.first.Scalar() != "include") {
        rst[it.first.Scalar()] = it.second;
        continue;
      }

      for (auto inc : it.second) {
        if (fs::exists(inc.Scalar())) {
          cfgFiles.emplace_back(inc.Scalar());
        } else if (fs::path relative = cfgFile.parent_path() / inc.Scalar();
                   fs::exists(relative)) {
          cfgFiles.emplace_back(std::move(relative));
        } else {
          std::cerr << "warning: missing config: " << inc.Scalar() << '\n';
          std::cerr << "warning: try best effort... missing config" << relative
                    << '\n';
        }
      }
    }
  }
  return rst;
}

struct CommandWrapper {
  YAML::Node cfg;
  Command* cmd;
};

void parseCommandOptions(const YAML::Node& options, Command& cmd) {
  for (auto option : options) {
    const std::string& opt = option["option"].Scalar();
    YAML::Node desc = option["description"];
    cmd.options.emplace_back(opt, desc ? desc.Scalar() : "");

    if (YAML::Node shortName = option["short"]; shortName) {
      cmd.options.back().shortName = shortName.as<char>();
    }

    auto& value = cmd.options.back().value;
    const std::string& optType = option["type"].Scalar();
    if (optType == "int") {
      value = 0ll;
    } else if (optType == "bool") {
      value = false;
    } else if (optType == "string") {
      value = std::string();
    } else {
      std::cerr << "warning: unknown option type: " << optType << "\n";
    }
  }
}

void parseCommandExecutor(const YAML::Node& executor, Command& cmd) {
  const std::string& execType = executor["type"].Scalar();
  if (execType == "shell") {
    cmd.executor = ExecutorShell{executor["command"].Scalar()};
  } else if (execType == "plugin") {
    cmd.executor = ExecutorPlugin{executor["library"].Scalar(),
                                  executor["symbol"].Scalar()};
  } else {
    std::cerr << "warning: unknown executor type: " << execType << "\n";
  }
}

void parseCommands(const YAML::Node& top, std::deque<Command>& cmds) {
  std::stack<CommandWrapper> stack;
  stack.push({top, nullptr});
  while (!stack.empty()) {
    CommandWrapper cur = stack.top();
    stack.pop();

    for (auto it : cur.cfg) {
      const std::string& key = it.first.Scalar();
      YAML::Node val = it.second;
      if (key == "description") {
        cur.cmd->description = val.Scalar();
        continue;
      }

      if (key == "options") {
        parseCommandOptions(val, *cur.cmd);
      } else if (key == "executor") {
        parseCommandExecutor(val, *cur.cmd);
      } else {
        if (!val.IsMap()) {
          std::cerr << "warning: invalid command format: " << key << "\n";
          continue;
        }

        cmds.emplace_back();
        Command& cmd = cmds.back();
        cmd.name = key;
        if (cur.cmd != nullptr) {
          cmd.parent = cur.cmd;
          cur.cmd->subCommands.push_back(&cmd);
        }
        stack.push({val, &cmd});
      }
    }
  }
}
} // namespace

namespace memo {
std::deque<Command> loadConfig(const std::string& path) {
  YAML::Node top = loadAllEntrySubCommands(path);

  std::deque<Command> cmds;
  parseCommands(top, cmds);
  return cmds;
}
} // namespace memo
