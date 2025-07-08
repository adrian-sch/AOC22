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

    int x = 1; // register x
    int cycle = 0; // cycle count
    int ans = 0; //signal strength
    int next = 20; //next signal update

    for (auto line : input){

        if (cycle > 220){
            break;
        }
        
        if (line == "noop"){
            cycle += 1;
        
            if (cycle >= next){
                cout << "Inc while noop: Cycle: " << cycle << " Register: " << x << " Signal Strengh: " << cycle * x << endl;
                ans += cycle * x;
                next += 40;
            }
        } else {
            vector<string> inst = aoc_utils::split_string(line, ' ');
            int inc = stoi(inst[1]);

            cycle += 2;
            
            // cout << "Cycle: " << cycle << " Increment: " << inc << " Register: " << x << endl;
            
            if (cycle >= next){
                cout << "Inc after or while add: Cycle: " << next << " Register: " << x << " Signal Strengh: " << next * x << endl;
                ans += next * x;
                next += 40;
            }
            x += inc;
        }

    }

    cout << "Ans: " << ans << endl;

}

void drawCRT(const vector<bool> pixel){
    int idx = 0;
    int width = 40;
    for (auto p : pixel){
        if (p) {
            cout << "#";
        } else {
            cout << ".";
        }

        idx ++;
        if (idx % width == 0){
            cout << endl;
        }
    }
    cout << endl;
}

void part2(const vector<string>& input) {

    int x = 1; // register x
    int cycle = 0; // cycle count

    int width = 40;
    int height = 6;

    vector<bool> pixel(width * height, false);

    auto draw_pixel = [&](int cycle, int x) {
        int col = cycle % width;
        pixel[cycle] = (col >= x - 1 && col <= x + 1);
    };

    for (auto line : input) {
        if (cycle >= width * height) break;

        if (line == "noop") {
            draw_pixel(cycle, x);
            ++cycle;
        } else {
            vector<string> inst = aoc_utils::split_string(line, ' ');
            int inc = stoi(inst[1]);

            draw_pixel(cycle, x);
            ++cycle;
            if (cycle >= width * height) break;

            draw_pixel(cycle, x);
            ++cycle;

            x += inc;
        }
    }

    drawCRT(pixel);
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