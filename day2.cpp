#include <map>
#include <fstream>
#include <iostream>

std::map<char, int> choice_scores = {
        {'X', 1}, {'Y', 2}, {'Z', 3}
};

int part_one() {
    int score = 0;
    std::ifstream f("../input/day2.txt");
    for (std::string line; std::getline(f, line);) {
        char op = line[0];
        char yours = line[2];
        score += choice_scores[yours];
        switch (op) {
            case 'A':
                score += yours == 'Y' ? 6 : yours == 'X' ? 3 : 0;
                break;
            case 'B':
                score += yours == 'Z' ? 6 : yours == 'Y' ? 3 : 0;
                break;
            case 'C':
                score += yours == 'X' ? 6 : yours == 'Z' ? 3 : 0;
                break;
        }
    }
    return score;
}

int part_two() {
    int score = 0;
    std::ifstream f("../input/day2.txt");
    for (std::string line; std::getline(f, line);) {
        char op = line[0];
        char yours = line[2];
        switch (yours) {
            case 'X':
                score += op == 'A' ? 3 : op == 'B' ? 1 : 2;
                break;
            case 'Y':
                score += 3;
                score += op == 'A' ? 1 : op == 'B' ? 2 : 3;
                break;
            case 'Z':
                score += 6;
                score += op == 'A' ? 2 : op == 'B' ? 3 : 1;
                break;
        }
    }
    return score;
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
    return 0;
}

