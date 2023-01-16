/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
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
      auto plan = std::get<Plan>(data);
      return Plan{plan.unit, plan.value + m_all_negative};
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

std::unordered_map<std::string, std::vector<fsd::Transaction>> fsd::group_transactions_by_account() const {
  std::unordered_map<std::string, std::vector<fsd::Transaction>> groups;
  for (const auto& data : m_data) {
    if (data.index() == 2) {
      auto trans = std::get<Transaction>(data);
      groups[trans.name].push_back(trans);
    }
  }

  return groups;
}

void fsd::parse(std::ifstream& p_fp) {
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
    else {
      int pos = head.find(':');
      if (pos != -1) {
        std::string account = head.substr(0, pos);
        std::string category = head.substr(pos + 1);

        float value = 0.0f;
        p_fp >> value;
        std::string unit;
        p_fp >> unit;

        if (value < 0.0f) {
          m_all_negative += value;
        }

        m_data.emplace_back(Transaction{account, category, unit, value});
      }
      else if (head.find("---") != -1) {
        break;
      }
    }
  }

  p_fp.close();
}
