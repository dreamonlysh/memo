#ifndef __MEMO_SRC_MEMO_H__
#define __MEMO_SRC_MEMO_H__
#include "config_model.h"
#include <deque>

namespace memo {

std::deque<Command> loadConfig(const std::string& path);

void execute(const Command& cmd);

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}
#endif
