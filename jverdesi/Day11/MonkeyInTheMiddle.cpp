//
// Created by jverdesi on 12/12/22.
//
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <deque>
#include "../Utils/InitDay.h"

#include "MonkeyInTheMiddle.h"


using namespace std;

class Monkey {
public:
    int id{};
    vector<long long> items;
    string rOperator;
    char operation;
    int testDivisible;
    int throwToTrue;
    int throwToFalse;

    explicit Monkey(vector<string> input) {
        id = input[0][7] - 48;
        size_t pos;
        string token;
        string subLine = input[1].substr(18);
        while ((pos = subLine.find(',')) < string::npos) {
            items.push_back(stoi(subLine.substr(0, pos)));
            subLine.erase(0, pos + 1);
        }
        items.push_back(stoi(subLine.substr(0, pos)));
        int lastDelimiterIndex = (int) input[2].rfind(' ');
        operation = input[2].substr(lastDelimiterIndex - 1, 1)[0];
        rOperator = input[2].substr(lastDelimiterIndex + 1);
        testDivisible = stoi(input[3].substr(input[3].rfind(' ') + 1));
        throwToTrue = stoi(input[4].substr(input[4].rfind(' ') + 1));
        throwToFalse = stoi(input[5].substr(input[5].rfind(' ') + 1));
    }
};

void printMonkeys(vector<Monkey> &monkeyList) {
    for(const auto& monkey:monkeyList) {
        cout << "\tMonkey " << monkey.id << ": ";
        for (const auto &items: monkey.items)
            cout << items << ", ";
        cout << "\n";
    }
}

void parseInput(const list<string> &inputStringList, vector<Monkey> &monkeyList) {
    int rowIdx = 0;
    vector<string> monkeyInput;
    for (const string& line: inputStringList) {

        if(rowIdx%7==6) {
            Monkey newMonkey=Monkey(monkeyInput);
            monkeyList.push_back(newMonkey);
            monkeyInput.clear();
        }
        else
            monkeyInput.push_back(line);
        rowIdx++;
    }
}


void evalWorryLevel(long long&monkeyItem, char operation, const string &rOperator,int divisorProduct,bool divide) {
    long long rVal;
    if (rOperator == "old")
        rVal = monkeyItem;
    else
        rVal = stoi(rOperator);
    if(operation=='+')
            monkeyItem = monkeyItem + rVal;
    if(operation=='*') {

        if (divide)
            monkeyItem = monkeyItem * rVal;
        else
            monkeyItem = (monkeyItem * rVal) % divisorProduct;
    }

}

void monkeyRound(vector<Monkey> &monkeyList, vector<long long> &monkeyInspectionTimes,int divisorProduct, bool divide) {
    for (auto &currMonkey: monkeyList) {
        for (auto monkeyItem: currMonkey.items) {
            monkeyInspectionTimes[currMonkey.id]++;

            evalWorryLevel(monkeyItem, currMonkey.operation, currMonkey.rOperator,divisorProduct,divide);
            if (divide)
                monkeyItem = floor(monkeyItem / 3);
            int throw_to;
            if (monkeyItem% currMonkey.testDivisible==0) {
                throw_to = currMonkey.throwToTrue;
            } else
                throw_to = currMonkey.throwToFalse;

            //  cout << "Current worry level is " << isDivisibleStr << " divisible by " << currMonkey.testDivisible << ".\n";
            monkeyList[throw_to].items.push_back(monkeyItem);

            //   cout << "Item with worry level " << monkeyItem << " is thrown to monkey "<<throw_to<<".\n";
        }
        currMonkey.items.clear();
    }
}

long long getInspectionTimes(int maxRounds, vector<Monkey> &monkeyList, bool divide) {
    int currRound = 1;
    vector<long long> monkeyInspectionTimes(monkeyList.size(), 0);
    int divisorProduct=1;
    for(const auto& monkay:monkeyList)
        divisorProduct*=monkay.testDivisible;

    while (currRound < maxRounds + 1) {
        monkeyRound(monkeyList, monkeyInspectionTimes,divisorProduct, divide);
       // printMonkeys(monkeyList);
        currRound++;

    }
    sort(monkeyInspectionTimes.begin(), monkeyInspectionTimes.end(), greater<>());
    long long m1 = monkeyInspectionTimes[0];
    long long m2 = monkeyInspectionTimes[1];
    return m1 * m2;
}

void day11Part1(const list<string> &inputStringList) {
    int max_rounds = 20;
    vector<Monkey> monkeyList;
    parseInput(inputStringList, monkeyList);
    long long score = getInspectionTimes(max_rounds, monkeyList, true);
    cout << "Monkey buissness score:" << score << "\n";

}

void day11Part2(const list<string> &inputStringList) {

    int max_rounds = 10000;
    vector<Monkey> monkeyList;
    parseInput(inputStringList, monkeyList);
    long long score = getInspectionTimes(max_rounds, monkeyList, false);
    cout << "Monkey buissness score:" << score << "\n";

}


int mainDay11() {
    initDay(11, &day11Part1, &day11Part2);
    return 0;
}