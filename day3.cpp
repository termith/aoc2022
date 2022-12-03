#include <fstream>
#include <iostream>
#include <string_view>

int score(char c) {
    return c > 'Z' ? (c - 96) : c - 38;
}

int get_duplicate(std::string_view s) {
    for (size_t i = 0; i < s.length() / 2; ++i) {
        if (s.substr(s.length() / 2).find(s[i]) != std::string_view::npos) {
            return score(s[i]);
        }
    }
    return 0;
}

int get_common_badge(std::string_view first, std::string_view second, std::string_view third) {
    for (char c: first) {
        if (second.find(c) != std::string_view::npos && third.find(c) != std::string_view::npos) {
            return score(c);
        }
    }
    return 0;
}


int part_one() {
    int result = 0;
    std::fstream f("../input/day3.txt");
    std::string line;
    while (std::getline(f, line)) {
        result += get_duplicate(line);
    }
    return result;
}

int part_two() {
    int result = 0;
    std::fstream f("../input/day3.txt");
    std::string line;
    while (std::getline(f, line)) {
        std::string second_line, third_line;
        std::getline(f, second_line);
        std::getline(f, third_line);
        result += get_common_badge(line, second_line, third_line);
    }
    return result;
}

int main() {

    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}