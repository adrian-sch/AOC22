#include "utils.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>

namespace aoc_utils{
    std::vector<std::string> split_string(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(s);
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    bool is_number(const std::string& str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }

    std::vector<std::string> read_lines_from_file(const std::string& filename) {
        std::ifstream inputFile(filename);
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            lines.push_back(line); // include all lines, even if empty
        }
        return lines;
    }
}

