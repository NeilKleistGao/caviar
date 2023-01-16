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

/// @file fsd.h

#ifndef CAVIAR_FSD_H
#define CAVIAR_FSD_H

#include <iostream>
#include <utility>
#include <variant>
#include <vector>
#include <fstream>

class fsd {
private:
  struct Account {
    std::string name;
    std::string unit;
    float value;

    Account(std::string p_n, std::string p_u, float p_v): name(std::move(p_n)), unit(std::move(p_u)), value(p_v) {}
  };
  struct Plan {
    std::string unit;
    float value;

    Plan(std::string p_u, float p_v): unit(std::move(p_u)), value(p_v) {}
  };
  struct Transaction {
    std::string name;
    std::string category;
    std::string unit;
    float value;
  };
public:
  explicit fsd(const std::string& p_filename);

  Plan get_rest_plan() const;
  std::vector<Account> get_balances() const;
private:
  using dataline = std::variant<Account, Plan, Transaction>;
  std::vector<dataline> m_data;

  void parse(std::ifstream& p_fp);
};

#endif //CAVIAR_FSD_H
