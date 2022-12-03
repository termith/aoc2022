#include <vector>
#include <fstream>
#include <iostream>

void check_sum(int &cur_sum, int &max_sum) {
    if (cur_sum > max_sum) max_sum = cur_sum;
    cur_sum = 0;
}

int part_one() {
    int max_sum = 0;
    int cur_sum = 0;
    std::ifstream f("../input/day1.txt");
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) {
            check_sum(cur_sum, max_sum);
        } else {
            cur_sum += std::stoi(line);
        }
    }
    check_sum(cur_sum, max_sum);
    return max_sum;
}

int part_two() {
    std::vector<int> ccal;
    int cur_sum = 0;
    std::ifstream f("../input/day1.txt");
    for (std::string line; std::getline(f, line);) {
        if (line.empty()) ccal.push_back(cur_sum);
        cur_sum = line.empty() ? 0 : cur_sum + stoi(line);
    }
    ccal.push_back(cur_sum);
    std::sort(ccal.begin(), ccal.end(), std::greater<int>());
    return ccal[0] + ccal[1] + ccal[2];
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}
