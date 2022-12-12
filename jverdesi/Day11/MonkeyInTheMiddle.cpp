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
    vector<int> items;
    string r_operator;
    char operation{};
    int test_divisible{};
    int throw_to_true{};
    int throw_to_false{};
};

void printMonkey(Monkey &monkey) {
    cout << "\tMonkey " << monkey.id << ": ";
    for (auto items: monkey.items)
        cout << items << ", ";
    cout << "\n";
}

void parseInput(const list<string> &inputStringList, vector<Monkey> &monkeyList) {
    int rowIdx = 0;
    Monkey tempMonkey;
    for (string line: inputStringList) {
        switch (rowIdx % 7) {
            case 0: {
                tempMonkey.id = line[7] - 48;
                break;
            }
            case 1: {
                size_t pos;
                string token;
                string sub_line = line.substr(18);
                while ((pos = sub_line.find(',')) < string::npos) {
                    tempMonkey.items.push_back(stoi(sub_line.substr(0, pos)));
                    sub_line.erase(0, pos + 1);
                }
                tempMonkey.items.push_back(stoi(sub_line.substr(0, pos)));
                break;
            }
            case 2: {
                int last_delimiter_index = (int) line.rfind(' ');
                tempMonkey.operation = line.substr(last_delimiter_index - 1, 1)[0];
                tempMonkey.r_operator = line.substr(last_delimiter_index + 1);

                break;
            }
            case 3:
                tempMonkey.test_divisible = stoi(line.substr(line.rfind(' ') + 1));
                break;
            case 4:
                tempMonkey.throw_to_true = stoi(line.substr(line.rfind(' ') + 1));
                break;
            case 5:
                tempMonkey.throw_to_false = stoi(line.substr(line.rfind(' ') + 1));
                break;
            case 6: {
                Monkey monkey = tempMonkey;
                monkeyList.push_back(monkey);
                tempMonkey = Monkey();
                break;
            }
            default:
                break;
        }
        rowIdx++;
    }
}

void evalWorryLevel(int &monkey_item, char operation, const string &r_operator) {
    int r_val;
    if (r_operator == "old")
        r_val = monkey_item;
    else
        r_val = stoi(r_operator);

    switch (operation) {
        case '+':
            monkey_item = monkey_item + r_val;
            break;
        case '*':
            monkey_item = monkey_item * r_val;
            break;
        default:
            break;
    }

}

void monkeyRound(vector<Monkey> &monkeyList) {
    for (auto &curr_monkey: monkeyList) {
      //  cout << "Monkey " << curr_monkey.id << ":\n";
        for (auto monkey_item: curr_monkey.items) {
         //   cout << "Monkey inspects an item with a worry level of " << monkey_item << ".\n";
            evalWorryLevel(monkey_item, curr_monkey.operation, curr_monkey.r_operator);
          //  cout << "New item value: " << monkey_item << ".\n";
            monkey_item = floor(monkey_item / 3);
          //  cout << "New item value /3: " << monkey_item << ".\n";

            string isDivisible;
            int throw_to;
            if (monkey_item % curr_monkey.test_divisible != 0) {
                isDivisible = "not";
                throw_to = curr_monkey.throw_to_false;
            } else
                throw_to = curr_monkey.throw_to_true;


          //  cout << "Current worry level is " << isDivisible << " divisible by " << curr_monkey.test_divisible << ".\n";
            monkeyList[throw_to].items.push_back(monkey_item);

         //   cout << "Item with worry level " << monkey_item << " is thrown to monkey "<<throw_to<<".\n";
        }
        curr_monkey.items.clear();
    }
}

void day11Part1(const list<string> &inputStringList) {
    int max_rounds = 20;
    int curr_round=1;
    vector<Monkey> monkeyList;
    parseInput(inputStringList, monkeyList);
    for (auto monkey: monkeyList)
        printMonkey(monkey);

    while (curr_round < max_rounds+1) {
        monkeyRound(monkeyList);
        cout<<"Round: "<<curr_round<<'\n';
        for (auto monkey: monkeyList)
            printMonkey(monkey);
        curr_round++;

    }
}

void day11Part2(const list<string> &inputStringList) {

    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }

}


int mainDay11() {
    initDay(11, &day11Part1, &day11Part2);
    return 0;
}