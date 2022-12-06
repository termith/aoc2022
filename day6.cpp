#include <set>
#include <fstream>
#include <iostream>

int find_message_start(const std::string& input, int length) {
    std::set<char> group;
    for (int i = 0; i < input.length() - (length - 1); ++i) {
        for (int j = i; j < i + length; ++j) {
            if (!group.insert(input[j]).second) {
                group.clear();
                break;
            }
        }
        if (group.size() == length) {
            return i + length;
        }
    }
    return 0;
}

int part_one() {
    std::fstream f("../input/day6.txt");
    std::string input;
    std::getline(f, input);
    return find_message_start(input, 4);
}

int part_two() {
    std::fstream f("../input/day6.txt");
    std::string input;
    std::getline(f, input);
    return find_message_start(input, 14);
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}