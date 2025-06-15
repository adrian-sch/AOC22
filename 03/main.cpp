#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

    string priority = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int ans = 0;

    for (const auto& line : input) {

        int len = line.length();

        string firstHalf = line.substr(0, len / 2);
        string secondHalf = line.substr(len / 2, len / 2);

        string charsSearched = "";

        for (const auto& c: firstHalf) {
            if (charsSearched.find(c) == string::npos){
                // not seachred yet
                charsSearched += c;
                if (secondHalf.find(c) != string::npos) {
                    ans += priority.find(c) + 1;
                    break;
                }
            }
        }

    }

    cout << "Part 1 Ans: " << ans << endl;
}

bool charInString(string str, char c){
    return str.find(c) != string::npos;
}

void part2(vector<string> input) {
        
    string priority = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int ans = 0;

    vector<vector<string>> groups;

    for (int i = 0; i < input.size(); i+=3 ) {
        vector<string> group(input.begin() + i, input.begin() + i + 3);
        groups.push_back(group);
    }

    for (const auto& group : groups){

        string charsSearched = "";

        for (const auto& c : group[0]){
            if (!charInString(charsSearched, c)){
                charsSearched += c;
                if (charInString(group[1], c) && charInString(group[2], c)){
                    ans += priority.find(c) + 1;
                    break;
                }
            }
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