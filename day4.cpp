#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <string_view>

struct Range {
    int a, b;

    [[nodiscard]] bool include(const Range &other) const noexcept {
        return (a - other.a <= 0 && b - other.b >= 0);
    }

    [[nodiscard]] bool intersect(const Range &other) const noexcept {
        return (a >= other.a) && (a <= other.b);
    }
};

std::pair<Range, Range> parse_range(std::string_view s) {
    std::pair<Range, Range> result;
    auto i = s.find('-');
    result.first.a = std::stoi(std::string(s.substr(0, i)));
    s = s.substr(i + 1);
    i = s.find(',');
    result.first.b = std::stoi(std::string(s.substr(0, i)));
    s = s.substr(i + 1);
    i = s.find('-');
    result.second.a = std::stoi(std::string(s.substr(0, i)));
    result.second.b = std::stoi(std::string(s.substr(i + 1)));
    return result;
}

int part_one() {
    std::fstream f("../input/day4.txt");
    std::string line;
    int counter = 0;
    while (std::getline(f, line)) {
        auto r = parse_range(line);
        if (r.first.include(r.second) || r.second.include(r.first)) {
            ++counter;
        }
    }
    return counter;
}

int part_two() {
    std::fstream f("../input/day4.txt");
    std::string line;
    int counter = 0;
    while (std::getline(f, line)) {
        auto r = parse_range(line);
        if (r.first.intersect(r.second) || r.second.intersect(r.first)) {
            ++counter;
        }
    }
    return counter;
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}