/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
 */

/// @file diff_test.cc

#include <gtest/gtest.h>
#include <filesystem>

#include "../caviar.h"

TEST(caviar, diff_tests) {
  const auto dir = std::filesystem::path{"../tests/fsd"};
  for (const auto& it : std::filesystem::directory_iterator{dir}) {
    std::string filename = it.path().string();
    caviar::truncate(filename);
    caviar::summarize(std::move(filename));
  }
}
