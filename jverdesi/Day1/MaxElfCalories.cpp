#include <iostream>
#include <fstream>
#include <string>
#include <list>

std::list<std::string> readInputFile(const char *inputFileName) {
    std::list<std::string> stringList;
    std::ifstream inputFile;
    std::string line;
    inputFile.open(inputFileName);
    if (inputFile.is_open()) {
        while (inputFile) {
            std::getline(inputFile, line);
            stringList.push_back(line);
        }
    }
    return stringList;
}

int findMaxCal(const std::list<std::string> &inputStringList) {

    int calorieSum = 0;
    int maxCal = 0;

    for (const std::string &line: inputStringList) {
        if (!line.empty()) {
            calorieSum += std::stoi(line);
        } else {
            if (calorieSum > maxCal) {
                maxCal = calorieSum;
            }
            calorieSum = 0;
        }

    }
    return maxCal;
}

int findMaxCalTop3(const std::list<std::string> &inputStringList) {
    int calorieSum = 0;
    std::list<int> callList;
    for (const std::string &line: inputStringList) {
        if (!line.empty()) {
            calorieSum += std::stoi(line);
        } else {
            callList.push_back(calorieSum);
            calorieSum = 0;
        }
    }
    callList.sort();
    int max3 = 0;
    for (int i = 0; i < 3; ++i) {
        max3 += callList.back();
        callList.pop_back();
    }
    return max3;
}

int main() {
    std::list<std::string> inputStringList = readInputFile("../Day1/inputDay1.txt");
    int maxCal = findMaxCal(inputStringList);
    std::cout << "Max Calorie Elf: " << maxCal << '\n';
    int maxCal3 = findMaxCalTop3(inputStringList);
    std::cout << "Total Calories of 3 top Elfs: " << maxCal3 << '\n';

    return 0;
}
