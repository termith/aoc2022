#include <set>
#include <vector>
#include <fstream>
#include <utility>
#include <iostream>

std::vector<std::vector<int>> build_matrix() {
    std::fstream f("../input/day8.txt");
    std::string line;
    std::vector<std::vector<int>> matrix;
    while (std::getline(f, line)) {
        matrix.emplace_back();
        for (char c: line) {
            matrix.back().push_back(c - '0');
        }
    }
    return matrix;
}

int part_one() {
    auto forrest = build_matrix();
    std::set<std::pair<int, int>> visible;

    for (int i = 0; i < forrest.size(); ++i) {
        for (int j = 0; j < forrest[i].size(); ++j) {
            if (i == 0 || i == forrest.size() - 1 || j == 0 || j == forrest[i].size() - 1) {
                visible.insert({i, j});
                continue;
            }
            for (int k = j - 1; k != -1; --k) {
                if (forrest[i][k] >= forrest[i][j]) {
                    break;
                }
                if (k == 0) {
                    visible.insert({i, j});
                }
            }
            for (int k = j + 1; k != forrest[i].size(); ++k) {
                if (forrest[i][k] >= forrest[i][j]) {
                    break;
                }
                if (k == forrest[i].size() - 1) {
                    visible.insert({i, j});
                }
            }
            for (int k = i - 1; k != -1; --k) {
                if (forrest[k][j] >= forrest[i][j]) {
                    break;
                }
                if (k == 0) {
                    visible.insert({i, j});
                }
            }
            for (int k = i + 1; k != forrest.size(); ++k) {
                if (forrest[k][j] >= forrest[i][j]) {
                    break;
                }
                if (k == forrest.size() - 1) {
                    visible.insert({i, j});
                }
            }
        }
    }
    return visible.size();
}

int part_two() {
    auto forrest = build_matrix();
    std::set<int> scores;

    for (int i = 1; i < forrest.size() - 1; ++i) {
        for (int j = 1; j < forrest[i].size() - 1; ++j) {
            int score = 1;
            int k = j - 1;
            while (k > 0) {
                if (forrest[i][k] >= forrest[i][j]) {
                    break;
                }
                --k;
            }
            score *= (j-k);

            k = j + 1;
            while (k != forrest[i].size() - 1) {
                if (forrest[i][k] >= forrest[i][j]) {
                    break;
                }
                ++k;
            }
            score *= (k - j);

            k = i - 1;
            while (k > 0) {
                if (forrest[k][j] >= forrest[i][j]) {
                    break;
                }
                --k;
            }
            score *= (i-k);

            k = i + 1;
            while (k != forrest.size() - 1) {
                if (forrest[k][j] >= forrest[i][j]) {
                    break;
                }
                ++k;
            }
            score *= (k - i);

        scores.insert(score);
        }
    }
    return *std::max_element(scores.begin(), scores.end());
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}