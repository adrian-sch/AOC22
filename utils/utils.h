#pragma once
#include <string>
#include <vector>

namespace aoc_utils{
    std::vector<std::string> split_string(const std::string& s, char delimiter);
    bool isNumber(const std::string& str);
    std::vector<std::string> read_lines_from_file(const std::string& filename);
}
