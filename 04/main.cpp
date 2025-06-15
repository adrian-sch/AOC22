#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

vector<string> split(const string& s, char delimiter){
    vector<string> tokens;
    string token;
    stringstream ss(s);

    while(getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

class Range{
public:
    int start, end;

    Range(int s, int e) : start(s), end(e) {}
    Range(string str) {
        auto parts = split(str, '-');
        start = stoi(parts[0]);
        end = stoi(parts[1]);
    }

    bool contains(Range r) const {
        return (start <= r.start && r.end <= end) || (r.start <= start && end <= r.end);
    }

    bool overlap(Range r) const {
        return end >= r.start && start <= r.end;
    }
};

vector<string> readInput(const string& filename) {
    ifstream inputFile(filename);
    vector<string> lines;
    string line;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

void part1(vector<string> input) {
    int ans = 0;

    for (const auto& line : input){
        auto ranges = split(line, ',');

        Range rangeA(ranges[0]);
        Range rangeB(ranges[1]);

        if (rangeA.contains(rangeB)){
            ans++;
        }
    }

    cout << "Part 1 Ans: " << ans << endl;
}

void part2(vector<string> input) {
    int ans = 0;

    for (const auto& line : input){
        auto ranges = split(line, ',');

        Range rangeA(ranges[0]);
        Range rangeB(ranges[1]);

        if (rangeA.overlap(rangeB)){
            ans++;
        }
    }

    cout << "Part 2 Ans: " << ans << endl;
}

int main () {
    string filename = "input.txt";
    auto input = readInput(filename);

    for (const auto& line : input) {
        cout << line << endl;
    }

    cout << "Part 1:" << endl;
    auto start = high_resolution_clock::now();
    part1(input);
    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<duration<double>>(stop - start);
    cout << "Runtime Part 1: " << dur.count() << " seconds" << endl;

    cout << "Part 2:" << endl;
    start = high_resolution_clock::now();
    part2(input);
    stop = high_resolution_clock::now();
    dur = duration_cast<duration<double>>(stop - start);
    cout << "Runtime Part 1: " << dur.count() << " seconds" << endl;

    return 0;

}