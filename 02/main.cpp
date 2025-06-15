#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


std::vector<std::string> readInput(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::string> rounds;
    std::string line;

    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            rounds.push_back(line);
        }
    }
    return rounds;
}

void part1(std::vector<std::string> rounds) {

    int score = 0;
    // Scoring system:
    // Rock (X) = 1 point
    // Paper (Y) = 2 points
    // Scissors (Z) = 3 points
    // Win = 6 points
    // Draw = 3 points
    // Loss = 0 points
    for (const auto& round : rounds) {
        char opponentMove = round[0];
        char playerMove = round[2];

        if (playerMove == 'X') {
            score += 1; // Rock
            if (opponentMove == 'C') {
                score += 6; // Win
            } else if (opponentMove == 'A') {
                score += 3; // Draw
            }
        } else if (playerMove == 'Y') {
            score += 2; // Paper
            if (opponentMove == 'A') {
                score += 6; // Win
            } else if (opponentMove == 'B') {
                score += 3; // Draw
            }
        } else if (playerMove == 'Z') {
            score += 3; // Scissors
            if (opponentMove == 'B') {
                score += 6; // Win
            } else if (opponentMove == 'C') {
                score += 3; // Draw
            }
        }
    }

    std::cout << "Total score: " << score << std::endl;
}

void part2(std::vector<std::string> rounds) {
    int score = 0;

    // Scoring system:
    // Loose (X) = 0 point
    // Draw (Y) = 3 points
    // Win (Z) = 6 points
    // Rock (A) = 1 points
    // Paper (B) = 2 points
    // Scissors (C) = 3 points
    for (const auto& round : rounds) {
        char opponentMove = round[0];
        char playerMove = round[2];

        if (playerMove == 'X') { // Lose
            score += 0; // No points for losing
            if (opponentMove == 'A') { // Rock = Scissors to loose
                score += 3;
            } else if (opponentMove == 'B') { // Paper = Rock to loose
                score += 1; 
            } else if (opponentMove == 'C') { // Scissors = Paper to loose
                score += 2; 
            }
        } else if (playerMove == 'Y') { // Draw
            score += 3; // points for draw
            if (opponentMove == 'A') { // Rock => Rock
                score += 1;
            } else if (opponentMove == 'B') { // Paper => Paper 
                score += 2; 
            } else if (opponentMove == 'C') { // Scissors => Scissors
                score += 3; 
            }
        } else if (playerMove == 'Z') { // Win
            score += 6; // points for win
            if (opponentMove == 'A') { // Rock => Stone
                score += 2;
            } else if (opponentMove == 'B') { // Paper => Scissors 
                score += 3; 
            } else if (opponentMove == 'C') { // Scissors => Rock
                score += 1; 
            }
        }
    }

    std::cout << "Total score: " << score << std::endl;
}

int main () {
    std::string filename = "input.txt";
    auto input = readInput(filename);

    std::cout << "Part 1:" << std::endl;
    part1(input);

    std::cout << "Part 2:" << std::endl;
    part2(input);

    return 0;

}