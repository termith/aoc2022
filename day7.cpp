#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Directory {
    Directory *parent = nullptr;
    std::vector<Directory *> children;
    int size = 0;

    int GetSize() {
        int result = size;
        for (auto d: children) {
            result += d->GetSize();
        }
        return result;
    }
};

void calculate(Directory* d, int& result) {
    if (d->GetSize() < 100000) {
        result += d->GetSize();
    }
    for (auto c: d->children) {
        calculate(c, result);
    }
}

void calculate_full_size(Directory* d, int& result) {
    result += d->size;
    for (auto c: d->children) {
        calculate_full_size(c, result);
    }
}

void find_smallest_dir(Directory* d, int& result, int threshold) {
    if (d->GetSize() >= threshold && d->GetSize() < result) {
        result = d->GetSize();
    }
    for (auto c : d->children) {
        find_smallest_dir(c, result, threshold);
    }
}

Directory* build_tree() {
    std::fstream f("../input/day7.txt");
    std::string line;
    Directory *cur_dir = nullptr;
    Directory *root;
    while (std::getline(f, line)) {
        if (line == "$ cd ..") {
            cur_dir = cur_dir->parent;
        } else if (std::string_view(line).starts_with("$ cd")) {
            Directory *old_cur_dir = cur_dir;
            cur_dir = new Directory;
            cur_dir->parent = old_cur_dir;
            if (old_cur_dir) {
                old_cur_dir->children.push_back(cur_dir);
            } else {
                root = cur_dir;
            }
        } else if (line == "$ ls" || std::string_view(line).starts_with("dir")) {
            continue;
        } else {
            auto p = line.find(' ');
            cur_dir->size += std::stoi(line.substr(0, p));
        }
    }
    return root;
}


int part_one() {
    auto root = build_tree();
    int result;
    calculate(root, result);
    return result;
}

int part_two() {
    auto root = build_tree();
    int full_size = 0;
    calculate_full_size(root, full_size);
    int required_space = 30000000 - (70000000 - full_size);
    int result = 70000000;
    find_smallest_dir(root, result, required_space);
    return result;
}

int main() {
    std::cout << part_one() << std::endl;
    std::cout << part_two() << std::endl;
}
