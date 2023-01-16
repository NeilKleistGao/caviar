/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
 */

/// @file fsd.h

#ifndef CAVIAR_FSD_H
#define CAVIAR_FSD_H

#include <iostream>
#include <utility>
#include <variant>
#include <vector>
#include <fstream>
#include <unordered_map>

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

    Transaction(std::string p_n, std::string p_c, std::string p_u, float p_v):
      name(std::move(p_n)), category(std::move(p_c)), unit(std::move(p_u)), value(p_v) {}
  };
public:
  explicit fsd(const std::string& p_filename);

  [[nodiscard]] Plan get_rest_plan() const;
  [[nodiscard]] std::vector<Account> get_balances() const;
  [[nodiscard]] std::unordered_map<std::string, std::vector<Transaction>> group_transactions_by_account() const;
private:
  using dataline = std::variant<Account, Plan, Transaction>;
  std::vector<dataline> m_data;
  float m_all_negative = 0.0f; // TODO: add unit.

  void parse(std::ifstream& p_fp);
};

#endif //CAVIAR_FSD_H
