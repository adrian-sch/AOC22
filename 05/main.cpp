#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <stack>

using namespace std;
using namespace std::chrono;

struct Instruction {
    int count, from, to;
};

void parseInput(const std::string& filename,
                std::vector<std::stack<char>>& stacks,
                std::vector<Instruction>& instructions) {
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> stackLines;

    // 1. Read stack lines
    while (std::getline(file, line) && !line.empty()) {
        stackLines.push_back(line);
    }

    // 2. Determine number of stacks from the last line with numbers
    int numStacks = (stackLines.back().length() + 1) / 4;
    stacks.resize(numStacks);

    // 3. Parse stacks from bottom to top
    for (int i = stackLines.size() - 2; i >= 0; --i) {
        for (int s = 0; s < numStacks; ++s) {
            char c = stackLines[i][1 + s * 4];
            if (c != ' ' && c != '[' && c != ']') {
                stacks[s].push(c);
            }
        }
    }

    // 4. Parse instructions
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string tmp;
        Instruction instr;
        iss >> tmp >> instr.count >> tmp >> instr.from >> tmp >> instr.to;
        // Convert to zero-based index if needed
        instr.from--;
        instr.to--;
        instructions.push_back(instr);
    }
}

vector<string> split(const string& s, char delimiter){
    vector<string> tokens;
    string token;
    stringstream ss(s);

    while(getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<string> readInput(const string& filename) {
    ifstream inputFile(filename);
    vector<string> lines;
    string line;

    while (getline(inputFile, line)) {
        cout << "Read Line: " << line << endl;
        
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}



void part1(std::vector<std::stack<char>> stacks,
                std::vector<Instruction> instructions) {

    for (auto inst : instructions){

        for (int i = 0; i < inst.count; i++){
            stacks[inst.to].push(stacks[inst.from].top());
            stacks[inst.from].pop();
        }

    }

    cout << "Part 1 Ans: ";

    for (auto stack : stacks){
        cout << stack.top();
    }

    cout << endl;
}

void part2(std::vector<std::stack<char>> stacks,
                std::vector<Instruction> instructions) {

    for (auto inst : instructions){

        stack<char> tmp;

        for (int i = 0; i < inst.count; i++){
            tmp.push(stacks[inst.from].top());
            stacks[inst.from].pop();
        }
        
        for (int i = 0; i < inst.count; i++){
            stacks[inst.to].push(tmp.top());
            tmp.pop();
        }

    }

    cout << "Part 2 Ans: ";

    for (auto stack : stacks){
        cout << stack.top();
    }

    cout << endl;
}

int main () {
    string filename = "input.txt";

    vector<Instruction> inst;
    vector<stack<char>> stacks;

    parseInput(filename, stacks, inst);

    cout << "Part 1:" << endl;
    auto start = high_resolution_clock::now();
    part1(stacks, inst);
    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<duration<double>>(stop - start);
    cout << "Runtime Part 1: " << dur.count() << " seconds" << endl;

    cout << "Part 2:" << endl;
    start = high_resolution_clock::now();
    part2(stacks, inst);
    stop = high_resolution_clock::now();
    dur = duration_cast<duration<double>>(stop - start);
    cout << "Runtime Part 1: " << dur.count() << " seconds" << endl;

    return 0;

}