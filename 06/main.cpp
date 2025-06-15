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

string readInput(const string& filename) {
    ifstream inputFile(filename);
    string line;

    getline(inputFile, line);
    return line;
}

void part1(string input) {
    int ans = 0;

    for (int i = 0; i < input.length() - 3; i++){
        string sub = input.substr(i, 4);
        bool found = true;
        
        for (char c : sub){
            int cnt = count(sub.begin(), sub.end(), c); 
            if (cnt > 1){
                found = false;
                break;
            }
        }

        if (found){
            ans = i + 4;
            break;
        }
    }

    cout << "Part 1 Ans: " << ans << endl;
}

void part2(string input) {
    int ans = 0;

    for (int i = 0; i < input.length() - 3; i++){
        string sub = input.substr(i, 14);
        bool found = true;
        
        for (char c : sub){
            int cnt = count(sub.begin(), sub.end(), c); 
            if (cnt > 1){
                found = false;
                break;
            }
        }

        if (found){
            ans = i + 14;
            break;
        }
    }

    cout << "Part 2 Ans: " << ans << endl;
}

int main () {
    string filename = "input.txt";
    auto input = readInput(filename);

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