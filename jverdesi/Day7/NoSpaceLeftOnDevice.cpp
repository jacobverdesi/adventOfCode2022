//
// Created by jacob on 12/7/2022.
//
#include <string>
#include <list>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include "../Utils/InitDay.h"
#include "NoSpaceLeftOnDevice.h"

using namespace std;

map<string, int> getDirectorySizeMapping(const list<string> &inputStringList) {
    map<string, int> dirs;
    vector<string> current_path;
    for (string line: inputStringList) {
        if (!line.empty()) {
            switch (line[0]) {
                case '$': {
                    if (line[2] == 'c') {
                        if (line[5] != '.') {
                            string cd_into = strrchr(line.c_str(), ' ') + 1;
                            while (dirs.find(cd_into) != dirs.end()) {
                                cd_into.append("*"); //avoid collisions
                            }
                            current_path.push_back(cd_into);
                        } else {
                            current_path.pop_back();
                        }
                    } else {
                        continue;
                    }
                    break;
                }
                case 'd': {
                    string new_dir = strrchr(line.c_str(), ' ') + 1;
                    while (dirs.find(new_dir) != dirs.end()) {
                        new_dir.append("*"); //avoid collisions
                    }
                    dirs[new_dir] = 0;
                    break;
                }
                default:
                    int file_size = stoi(strtok(line.data(), " "));

                    for (const string &dir: current_path) {
                        dirs[dir] += file_size;
                    }
            }
        }
    }
    return dirs;
}

void day7Part1(const list<string> &inputStringList) {
    map<string, int> dirs = getDirectorySizeMapping(inputStringList);
    int sumOfDirsLessThanOneHunderedThousand = 0;
    for (auto const &tup: dirs) {

        if (tup.second < 100000) {
            sumOfDirsLessThanOneHunderedThousand += tup.second;
        }
    }
    cout << "Sum of total sizes of directories less than 100000: " << sumOfDirsLessThanOneHunderedThousand << "\n";


}

void day7Part2(const list<string> &inputStringList) {
    map<string, int> dirs = getDirectorySizeMapping(inputStringList);
    int totalDiskSpace = 70000000;
    int unusedDiskSpace = totalDiskSpace - dirs["/"];
    int minDeleted = 30000000 - unusedDiskSpace;
    int smallestDeleted = totalDiskSpace;
    for (auto const &tup: dirs) {

        if (tup.second > minDeleted and tup.second < smallestDeleted) {
            smallestDeleted = tup.second;
        }
    }
    cout << "Sum of total sizes of directories less than 100000: " << smallestDeleted << "\n";
}

int mainDay7() {
    initDay(7, &day7Part1, &day7Part2);
    return 0;
}