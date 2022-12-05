#include <list>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <iterator>

const std::regex INSTRUCTIONS_REGEX(R"regex(move ([0-9]+) from (\d+) to (\d+))regex");

std::vector<std::list<char>> read_stacks(std::fstream &f) {
    std::vector<std::list<char>> result;
    result.resize(9, {});
    std::string line;
    while (std::getline(f, line)) {
        if (std::string_view(line).starts_with(" 1")) {
            return result;
        }
        for (size_t i = 0; i < line.length(); i += 3) {
            if (line[i] == '[') { result[i / 4].push_front(line[i + 1]); }
            i++;
        }
    }
    return result;
}

void part_one() {
    std::fstream f("../input/day5.txt");
    auto stacks = read_stacks(f);
    std::string line;
    std::getline(f, line);
    std::smatch m;
    while (std::getline(f, line)) {
        if (std::regex_match(line, m, INSTRUCTIONS_REGEX)) {
            int count = std::stoi(std::string(m[1].str()));
            int src = std::stoi(std::string(m[2].str())) - 1;
            int dst = std::stoi(std::string(m[3].str())) - 1;
            while (count) {
                stacks[dst].push_back(stacks[src].back());
                stacks[src].pop_back();
                --count;
            }
        }
    }
    for (const auto &s: stacks) {
        std::cout << s.back();
    }
}

void part_two() {
    std::fstream f("../input/day5.txt");
    auto stacks = read_stacks(f);
    std::string line;
    std::getline(f, line);
    std::smatch m;
    while (std::getline(f, line)) {
        if (std::regex_match(line, m, INSTRUCTIONS_REGEX)) {
            int count = std::stoi(std::string(m[1].str()));
            int src = std::stoi(std::string(m[2].str())) - 1;
            int dst = std::stoi(std::string(m[3].str())) - 1;
            auto cnt = stacks[src].end();
            std::advance(cnt, -count);
            stacks[dst].splice(stacks[dst].end(), stacks[src], cnt, stacks[src].end());
        }
    }
    for (const auto &s: stacks) {
        std::cout << s.back();
    }
}

int main() {
    part_one();
    std::cout << std::endl;
    part_two();
}
