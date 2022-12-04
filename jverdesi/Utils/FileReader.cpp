//
// Created by jacob on 12/3/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "FileReader.h"

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
void printStringList(const std::list<std::string> &inputStringList){
    for (const std::string &line: inputStringList) {
        std::cout << line<<"\n";
    }
}
