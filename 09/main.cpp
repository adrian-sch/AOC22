#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../utils/utils.h"

using namespace std;
using namespace std::chrono;

vector<string> parseInput(string& filename){
    ifstream inputFile(filename);
    vector<std::string> lines;
    string line;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    return lines;
}

void part1(const vector<string>& input) {

    int xh = 0; // head
    int yh = 0;
    int xt = 0; // tail
    int yt = 0;

    vector<pair<int, int>> visited; // to track visited positions
    visited.push_back(make_pair(xt, yt)); // start position

    for (const auto& line : input) {

        auto instructions = aoc_utils::split_string(line, ' ');
        auto dir = instructions[0];
        auto steps = stoi(instructions[1]);

        for (int i = 0; i < steps; ++i) {
            int xh_old = xh;
            int yh_old = yh;
            if (dir == "R") {
                xh += 1;
            } else if (dir == "L") {
                xh -= 1;
            } else if (dir == "U") {
                yh += 1;
            } else if (dir == "D") {
                yh -= 1;
            }

            // Move tail
            if (abs(xh - xt) > 1 || abs(yh - yt) > 1) {
                xt = xh_old; // tail follows head
                yt = yh_old;
            }

            // Check if tail position is already visited
            auto pos = make_pair(xt, yt);
            if (find(visited.begin(), visited.end(), pos) == visited.end()) {
                visited.push_back(pos);
            }
        }
    }

    cout << "Visited positions: " << visited.size() << endl;
}

void part2(const vector<string>& input) {

    int length = 10; // length of the rope
    vector<pair<int, int>> rope(length, make_pair(0, 0)); // initialize rope positions

    vector<pair<int, int>> visited; // to track visited positions
    visited.push_back(make_pair(0, 0)); // start position

    for (const auto& line : input) {

        auto instructions = aoc_utils::split_string(line, ' ');
        auto dir = instructions[0];
        auto steps = stoi(instructions[1]);

        for (int i = 0; i < steps; ++i) {

            // Move head
            pair<int, int> &head = rope[0];
            if (dir == "R") {
                head.first += 1;
            } else if (dir == "L") {
                head.first -= 1;
            } else if (dir == "U") {
                head.second += 1;
            } else if (dir == "D") {
                head.second -= 1;
            }

            // Move tail
            for (int j = 1; j < length; ++j) {
                pair<int, int> &tail = rope[j];
                pair<int, int> &prev = rope[j - 1];

                // if tail is more than 1 step in one direction from previous segment move it in this direction
                if (abs(prev.first - tail.first) > 1 && abs(prev.second - tail.second) == 0) {
                    tail.first += (prev.first > tail.first) ? 1 : -1; // move in x direction
                } else if (abs(prev.second - tail.second) > 1 && abs(prev.first - tail.first) == 0) {
                    tail.second += (prev.second > tail.second) ? 1 : -1; // move in y direction
                } else if (abs(prev.first - tail.first) > 1 || abs(prev.second - tail.second) > 1) {
                    // move diagonally
                    tail.first += (prev.first > tail.first) ? 1 : -1;
                    tail.second += (prev.second > tail.second) ? 1 : -1;
                }
            }

            // Check if tail position is already visited
            auto pos = make_pair(rope[length - 1].first, rope[length - 1].second);
            if (find(visited.begin(), visited.end(), pos) == visited.end()) {
                visited.push_back(pos);
            }
        }
    }

    cout << "Visited positions: " << visited.size() << endl;
}

int main(int argc, char* argv[]) {
    string filename = "input.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    auto input = parseInput(filename);

    cout << "Part 1:" << endl;
    auto start = high_resolution_clock::now();
    part1(input);
    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<duration<double>>(stop - start);
    cout << "\tRuntime: " << dur.count() << " seconds" << endl;

    cout << "Part 2:" << endl;
    start = high_resolution_clock::now();
    part2(input);
    stop = high_resolution_clock::now();
    dur = duration_cast<duration<double>>(stop - start);
    cout << "\tRuntime: " << dur.count() << " seconds" << endl;

    return 0;
}