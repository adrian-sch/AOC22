#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <memory>

using namespace std;
using namespace std::chrono;


class Directory : public enable_shared_from_this<Directory> {
public:

    struct File {
        string name;
        int size;
        shared_ptr<Directory> parent;

        File(const string& n, const int s, shared_ptr<Directory> p) : name(n), size(s), parent(p) {};
    };

    shared_ptr<Directory> parent;
    string name;
    vector<shared_ptr<Directory>> children;
    vector<shared_ptr<File>> files;

    Directory(const string& n) : name(n) {}
    Directory(const string& n, shared_ptr<Directory> p) : name(n), parent(p) {}

    bool isRoot(){
        return parent == nullptr;
    }

    // Add methods to add files/directories, search, print, etc.
    void addFile(const string& fileName, int size) {
        files.push_back(make_shared<File>(fileName, size, shared_from_this()));
    }

    void addDirectory(const string& dirName) {
        children.push_back(make_shared<Directory>(dirName, shared_from_this()));
    }

    shared_ptr<Directory> getDir(string& name) {
        for (auto dir : children){
            if (dir->name == name) {
                return dir;
            }
        }
        return nullptr;
    }

    vector<shared_ptr<Directory>> getAllDirs() {
        vector<shared_ptr<Directory>> dirs;
        dirs.push_back(shared_from_this());
        for (auto& dir : children) {
            auto subdirs = dir->getAllDirs();
            dirs.insert(dirs.end(), subdirs.begin(), subdirs.end());
        }
        return dirs;
    }

    void printTree(int depth = 0) const {
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        cout << "[D] " << name << endl;
        for (auto file : files){
            for (int i = 0; i < depth; ++i) std::cout << "  ";
            cout << "  [F] " << file->name << " " << file->size << endl;
        }
        for (auto child : children) {
            child->printTree(depth + 1);
        }
    }

    int getSize() const {
        int total = 0;
        // Add sizes of files in this directory
        for (const auto& file : files) {
            total += file->size;
        }
        // Add sizes of all child directories recursively
        for (const auto& dir : children) {
            total += dir->getSize();
        }
        return total;
    }

};

vector<string> split(const string& s, char delimiter){
    vector<string> tokens;
    string token;
    stringstream ss(s);

    while(getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool isNumber(const string& str){
    return !str.empty() && all_of(str.begin(), str.end(), isdigit);
}

shared_ptr<Directory> readInput(const string& filename) {
    ifstream inputFile(filename);
    string line;
    auto root = make_shared<Directory>("/", nullptr);
    shared_ptr<Directory> current = root;

    while (getline(inputFile, line)) {
        auto tokens = split(line, ' ');

        if (tokens[0] == "$" && tokens[1] == "cd"){
            if (tokens[2] == ".."){
                current = current->parent;
            } else if (tokens[2] != "/"){
                auto newDir = current->getDir(tokens[2]);
                if (newDir == nullptr){
                    root -> printTree();

                    cerr << "No directory found: " << tokens[2] << endl;
                    return nullptr;
                }
                current = current->getDir(tokens[2]);
            }
        } else if (tokens[0] == "dir") {
            current->addDirectory(tokens[1]);
        } else if (isNumber(tokens[0])){
            current->addFile(tokens[1], stoi(tokens[0]));
        }
    }

    root->printTree();

    return root;
}

void part1(shared_ptr<Directory> input) {
    int ans = 0;

    auto dirs = input->getAllDirs();

    for (auto dir : dirs) {
        int size = dir->getSize();
        if (size <= 100000){
            ans += size;
        }
    }

    cout << "\tAns: " << ans << endl;
}

void part2(shared_ptr<Directory> input) {
    int ans = 0;

    int sizeFs = 70000000;
    int sizeNeeded = 30000000;
    int sizeFree = sizeFs - input->getSize();
    int sizeToFree = sizeNeeded - sizeFree;

    int minOvershoot = -sizeFs;
    auto dirs = input->getAllDirs();

    for (auto dir : dirs) {
        int size = dir->getSize();
        if (sizeToFree - size <= 0 && sizeToFree - size > minOvershoot){
            minOvershoot = sizeToFree - size;
            ans = size;
        }
    }

    cout << "\tAns: " << ans << endl;
}

int main () {
    string filename = "input.txt";
    auto input = readInput(filename);

    if (input == nullptr){
        return -1;
    }

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