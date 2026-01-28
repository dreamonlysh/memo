#include <CLI/CLI.hpp>
#include <cstdlib>
#include <string>
#include <variant>

namespace {

using OptionValue = std::variant<bool, uint64_t, std::string>;
using Options = std::unordered_map<std::string, OptionValue>;
using AppOptions = std::map<CLI::App*, Options>;

bool option_git_log_authors = false;
bool option_git_log_tree = false;
bool option_git_log_tree2 = false;
int option_git_log_count_days = 0;

std::string option_git_log_since;
std::string option_git_log_until;

static AppOptions appOptions;
static std::unordered_map<std::string, CLI::App *> appCache;

CLI::App* add_subcomand(CLI::App& parent, const std::string& name) {
  auto *sub = parent.add_subcommand(name);
  appCache[name] = sub;
  return sub;
}

CLI::Option_group* add_option_group(CLI::App& parent, const std::string& name) {
  auto *grp = parent.add_option_group(name);
  appCache[name] = grp;
  return grp;
}

template <typename T, typename AppT>
T &get_option(AppT* app, const std::string& name) {
  auto &oneline = appOptions[app][name];
  oneline = T{};
  return std::get<T>(oneline);
}

void configure(CLI::App& app) {
  CLI::App* git = add_subcomand(app, "git");
  CLI::App* gitLog = add_subcomand(*git, "log");

  auto &since = appOptions[gitLog]["--since"];
  since = "";
  gitLog->add_option("--since", std::get<std::string>(since),
                  "Folder to keep the disassembled");

  auto *grp = add_option_group(*gitLog, "log_grp");
  grp->add_flag("--oneline", get_option<bool>(grp, "--oneline"),
                  "Folder to keep the disassembled");
  grp->add_flag("--authors", option_git_log_authors,
                  "Folder to keep the disassembled");
  grp->add_flag("--tree", option_git_log_tree,
                  "Folder to keep the disassembled");
  grp->add_flag("--tree2", option_git_log_tree2,
                  "Folder to keep the disassembled");
  grp->add_option("--count", option_git_log_count_days,
                  "Folder to keep the disassembled");
}
}

int main(int argc, char* argv[]) {
  CLI::App app{"fish"};
  configure(app);
  CLI11_PARSE(app, argc, argv);
  std::string s;

  if (std::get<bool>(appOptions[appCache["log_grp"]]["--oneline"])) {
    std::system("git log --oneline");
  }
  if (option_git_log_authors) {
    std::system("git shortlog -sn --since=\"2025-04-03 23:59:59\"");
  }
  if (option_git_log_count_days > 0) {
    std::system("git log --since=\"2025-04-03 00:00:00\" --until=\"2025-06-04 23:59:59\" --pretty=tformat: --numstat");
    // std::system("git log --since=\"2025-04-03 23:59:59\" --until=\"2025-06-04 23:59:59\" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2 } END { printf \"added lines: %s, removed lines: %s\n\", add, subs }'");
  }
  if (option_git_log_tree) {
    std::system("git log --since=\"2025-04-03 00:00:00\" --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(auto)%d%C(reset)' --all");
  }
  if (option_git_log_tree2) {
    std::system("git log --since=\"2025-04-03 00:00:00\" --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(auto)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)'");
  }
}
