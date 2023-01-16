/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
 */

/// @file main.cc

#include "third-parties/cxxopts/include/cxxopts.hpp"
#include "caviar.h"

int main(int argc, char* argv[]) {
  cxxopts::Options options("caviar",
                           "A simple tool that helps you keep track of your personal expenses in Emacs.");
  options.add_options()
    ("s,summarize", "Summarize your current expenses.", cxxopts::value<std::string>());
  // TODO: add more params

  auto result = options.parse(argc, argv);
  if (result.count("summarize") > 0) {
    std::string filename = result["summarize"].as<std::string>();
    caviar::truncate(filename);
    caviar::summarize(std::move(filename));
  }

  return 0;
}
