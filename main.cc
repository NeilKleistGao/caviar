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
