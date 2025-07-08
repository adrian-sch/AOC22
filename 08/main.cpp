#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../utils/utils.h"

using namespace std;
using namespace std::chrono;


struct Tree {
    const int hight;
    bool visible;
    int score;
    Tree(int h): hight(h), visible(false), score(0){};
};

// Overload operator<< for Tree
std::ostream& operator<<(std::ostream& os, const Tree& t) {
    os << t.hight << (t.visible ? "v" : " ") << "s" << t.score;
    return os;
}

template <typename T>
class Grid {
public:
    vector<T> data;
    int rows, cols;

    Grid(vector<T> d, int r, int c) : data(d), rows(r), cols(r){};

    T* getData(int row, int col){
        return &data[row * cols + col];
    }

    void print() {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::cout << data[r * cols + c] << " ";
            }
            std::cout << std::endl;
        }
    }
};

Grid<Tree> parseInput(string& filename){
    vector<Tree> trees;
    int rows = 0;
    int cols = 0;

    ifstream inputFile(filename);
    vector<std::string> lines;
    string line;

    while (std::getline(inputFile, line)) {
        rows += 1;
        if (cols == 0){
            cols = line.length();
        }
        for (char c : line){
            Tree t(stoi(string(1, c))); //char to int
            trees.push_back(t);
        }
    }
    return Grid<Tree>(trees, rows, cols);
}

void part1(Grid<Tree> input) {
    int ans = 0;

    int maxCol = input.cols;
    int maxRow = input.rows;

    // check rows first
    for (int r = 0; r < input.rows; r++){
        int maxHl = -1;
        int maxHr = -1;
        for (int c = 0; c < input.cols; c++){
            // check from left
            Tree* left = input.getData(r,c); 
            bool visible = left->hight > maxHl;
            left->visible = left->visible || visible;
            if (visible){
                maxHl = left->hight;
            }

            //check from right
            Tree* right = input.getData(r, maxCol-(c+1));
            visible = right->hight > maxHr;
            right->visible = right->visible || visible;
            if (visible) {
                maxHr = right->hight;
            }
        }
    }

    // check cols now
    for (int c = 0; c < input.cols; c++){
        int maxHt = -1;
        int maxHb = -1;
        for (int r = 0; r < input.rows; r++){
            // check from top
            Tree* top = input.getData(r,c); 
            bool visible = top->hight > maxHt;
            top->visible = top->visible || visible;
            if (visible){
                maxHt = top->hight;
            }

            //check from bottom
            Tree* bot = input.getData(maxRow - (r+1), c);
            visible = bot->hight > maxHb;
            bot->visible = bot->visible || visible;
            if (visible) {
                maxHb = bot->hight;
            }
        }
    }

    // input.print();

    for (auto tree : input.data){
        if (tree.visible){
            ans+=1;
        }
    }

    cout << "\tAns: " << ans << endl;
}

void part2(Grid<Tree> input) {
    int ans = 0;

    for (int r = 0; r < input.rows; r++){
        for (int c = 0; c < input.cols; c++){

            Tree* t = input.getData(r,c);
            int h = t->hight;

            //look up
            int scoreUp = 0;
            for (int i = (r-1); i >= 0; i--){
                scoreUp +=1;
                if (input.getData(i,c)->hight >= h){
                    break; // cant look past trees that are sae height or higer
                }
            }
            
            //look down
            int scoreDown = 0;
            for (int i = (r+1); i < input.rows; i++){
                scoreDown +=1;
                if (input.getData(i,c)->hight >= h){
                    break; // cant look past trees that are sae height or higer
                }
            }

            //look left
            int scoreLeft = 0;
            for (int i = (c-1); i >= 0; i--){
                scoreLeft +=1;
                if (input.getData(r,i)->hight >= h){
                    break; // cant look past trees that are sae height or higer
                }
            }
            
            //look right
            int scoreRight = 0;
            for (int i = (c+1); i < input.cols; i++){
                scoreRight +=1;
                if (input.getData(r,i)->hight >= h){
                    break; // cant look past trees that are sae height or higer
                }
            }

            t->score = scoreUp * scoreDown * scoreLeft * scoreRight;

            if (t->score > ans){
                ans = t->score;
            }
        }
    }

    cout << "\tAns: " << ans << endl;
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