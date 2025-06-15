#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


std::vector<std::vector<int>> readInput(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::vector<int>> elfs;
    std::vector<int> currentElf;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            if (!currentElf.empty()) {
                elfs.push_back(currentElf);
                currentElf.clear();
            }
        } else {
            currentElf.push_back(std::stoi(line));
        }
    }

    // Add the last elf if not empty
    if (!currentElf.empty()) {
        elfs.push_back(currentElf);
    }

    return elfs;
}

void part1(std::vector<std::vector<int>> elfs) {

  std::vector<int> sums;

  for (const auto& elf : elfs) {
    int sum = 0;
    for (int value : elf) {
        sum += value;
    }
    sums.push_back(sum);
  }

  auto maxSum = std::max_element(sums.begin(), sums.end());
  std::cout << *maxSum << std::endl;

}

void part2(std::vector<std::vector<int>> elfs) {

    std::vector<int> sums;

    for (const auto& elf : elfs) {
    int sum = 0;
    for (int value : elf) {
        sum += value;
    }
    sums.push_back(sum);
    }

    std::sort(sums.begin(), sums.end(), std::greater<int>());

    int ans = sums[0] + sums[1] + sums[2];
    std::cout << ans << std::endl;
}

int main () {
    std::string filename = "input.txt";
    auto elfs = readInput(filename);

    std::cout << "Part 1:" << std::endl;
    part1(elfs);

    std::cout << "Part 2:" << std::endl;
    part2(elfs);

    return 0;

}