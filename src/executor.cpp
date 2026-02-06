#include "memo.h"
#include <dlfcn.h>

namespace {
using namespace memo;

void execute(const ExecutorShell& executor, const Command& cmd) {

  // std::string cmd = c.run;
  // for (const auto& [k, v] : kv) {
  //   std::string key = "{" + k + "}";
  //   size_t p = 0;
  //   while ((p = cmd.find(key, p)) != std::string::npos) {
  //     cmd.replace(p, key.size(), v);
  //     p += v.size();
  //   }
  // }

  (void)std::system(executor.script.c_str());
}

void execute(const ExecutorPlugin& executor, const Command& cmd) {
  auto* library = dlopen(executor.library.c_str(), RTLD_NOW);
  if (library == nullptr) {
    throw dlerror();
  }

  auto fn = (PluginFn)dlsym(library, executor.symbol.c_str());
  if (fn == nullptr) {
    throw dlerror();
  }

  fn(cmd);
}
} // namespace

namespace memo {
void execute(const Command& cmd) {
  std::visit(overloaded{[&](auto&& executor) { ::execute(executor, cmd); },
                        [](const size_t) {}},
             cmd.executor);
}
} // namespace memo
