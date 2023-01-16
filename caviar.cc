/**
 * MIT License
 * Copyright (c) 2023 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
