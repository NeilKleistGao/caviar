/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
 */

/// @file caviar.cc

#include "caviar.h"

#include <filesystem>
#include <fstream>
#include <cstdio>
#include <unordered_map>
#include <cstring>

namespace caviar {
  void summarize(std::string&& p_filename) {
    const auto data = fsd(p_filename);
    const auto balances = data.get_balances();
    const auto transactions = data.group_transactions_by_account();
    std::unordered_map<std::string, float> delta; // TODO: add unit

    for (const auto& [account, trans] : transactions) {
      for (const auto& t : trans) {
        delta[account] += t.value;
      }
    }

    std::ofstream fp{p_filename, std::ios::app};
    fp.precision(2);
    fp << "---" << std::endl;

    for (const auto& balance : balances) {
      float d = (delta.find(balance.name) == delta.end()) ? 0.0f : delta[balance.name];
      fp << "Balance[" << balance.name << "]: " <<
        std::fixed << balance.value + d << balance.unit << std::endl;
    }

    auto rest = data.get_rest_plan();
    if (rest.has_value()) {
      const auto& plan = rest.value();
      fp << "Plan': " <<  std::fixed << plan.value << plan.unit << std::endl;
    }

    fp.close();
  }

  void truncate(const std::string& p_filename) {
    FILE* fp = fopen(p_filename.c_str(), "r");
    if (fp == nullptr) {
      std::cerr << "can't open file " << p_filename << std::endl;
      return;
    }

    unsigned int size = 0;
    char buffer[1024];
    while (true) {
      std::memset(buffer, 0, sizeof(buffer));
      fread(buffer, sizeof(buffer) - 1, 1, fp);
      const std::string s = buffer;
      unsigned int real_size = s.length();
      if (real_size == 0) {
        break;
      }

      const int pos = s.find("---");
      if (pos != -1) {
        size += pos;
        break;
      }
      else {
        size += real_size;
      }

      std::cout << s << ", " << size << std::endl;
    }

    fclose(fp);
    using namespace std::filesystem;
#if WIN32
    resize_file(path{ p_filename }, size + 3);
#else
    resize_file(path{p_filename}, size);
#endif
  }
} // namespace caviar
