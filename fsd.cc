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

/// @file fsd.cc

#include "fsd.h"

fsd::fsd(const std::string& p_filename) {
  std::ifstream fp{p_filename};
  if (fp.fail() || fp.bad()) {
    std::cerr << "can't open file " << p_filename << std::endl;
    return;
  }

  parse(fp);
}

fsd::Plan fsd::get_rest_plan() const {
  for (const auto& data : m_data) {
    if (data.index() == 1) {
      return std::get<Plan>(data);
    }
  }

  return Plan{"CNY", 0.0f}; // TODO: Add a default unit.
}

std::vector<fsd::Account> fsd::get_balances() const {
  std::vector<fsd::Account> accounts;
  for (const auto& data : m_data) {
    if (data.index() == 0) {
      accounts.push_back(std::get<Account>(data));
    }
  }

  return accounts;
}

void fsd::parse(std::ifstream& p_fp) {
  int size = 0;
  while (!p_fp.eof()) {
    std::string head;
    p_fp >> head;

    if (head.find("Account") != -1) {
      const int start = head.find('[');
      const int end = head.find(']');
      std::string name = head.substr(start + 1, end - start - 1);
      float value = 0.0f;
      p_fp >> value;
      std::string unit;
      p_fp >> unit;

      m_data.emplace_back(Account{name, unit, value});
    }
    else if (head.find("Plan") != -1) {
      float value = 0.0f;
      p_fp >> value;
      std::string unit;
      p_fp >> unit;

      m_data.emplace_back(Plan{unit, value});
    }
    else if (head.find("---")) {
      break;
    }
  }

  p_fp.close();
}
