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
#include <unordered_map>

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
    fp << "Plan': " <<  std::fixed << rest.value << rest.unit << std::endl;

    fp.close();
  }

  void truncate(const std::string& p_filename) {
    std::ifstream fp{p_filename};
    if (fp.fail() || fp.bad()) {
      std::cerr << "can't open file " << p_filename << std::endl;
      return;
    }

    unsigned int size = 0;
    char buffer[1024];
    while (!fp.eof()) {
      unsigned int real_size = fp.readsome(buffer, sizeof(buffer));
      const std::string s = buffer;
      const int pos = s.find("---");
      if (pos != -1) {
        size += pos;
        break;
      }
      else {
        size += real_size;
      }
    }

    fp.close();
    using namespace std::filesystem;
    resize_file(path{p_filename}, size);
  }
} // namespace caviar
