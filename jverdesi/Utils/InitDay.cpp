//
// Created by jacob on 12/3/2022.
//
#include <string>
#include <list>
#include <iostream>
#include "FileReader.h"
#include "InitDay.h"
using namespace std;

void initDay(int day,void (*part1)(const list<string>&),void (*part2)(const list<string>&)) {
    string filepathPrompt="../adventPrompts/day"+std::to_string(day)+".txt";
    list<string> promptStringList = readInputFile(filepathPrompt.c_str());

    string filepathInputData="../Data/inputDay"+std::to_string(day)+".txt";
    const list<string> inputStringList = readInputFile(filepathInputData.c_str());
    cout<<promptStringList.front()<<'\n';
    //printStringList(inputStringList);
    cout<<"-Part One-\n";
    part1(inputStringList);
    cout<<"-Part Two-\n";
    part2(inputStringList);
    cout<<'\n';
}