//
// Created by jacob on 12/4/2022.
//
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <iostream>
#include <cstring>
#include "../Utils/InitDay.h"
#include "../Utils/StackHelper.h"
#include "Day5.h"

using namespace std;



void day5Part1(const list<string> &inputStringList) {
    size_t num_stacks = inputStringList.front().length() / 4 + 1;
    vector<stack<char>> stacks(num_stacks);
    bool atMoves = false;
    for (string line: inputStringList) {
        if (!line.empty()) {
            if (line[1] == '1') {
                atMoves = true;
                for (stack<char> &stack: stacks) {
                    reverseStack(stack);
                }
            }
            if (!atMoves) {
                for (int i = 0; i < num_stacks; i++) {
                    if (!isblank(line[i * 4 + 1])) {
                        stacks[i].push(line[i * 4 + 1]);
                    }
                }
            } else if (line[0] == 'm') {

                int move = stoi(strtok(line.data(), "move"));
                int from = stoi(strtok(nullptr, "from")) - 1;
                int to = stoi(strtok(nullptr, "to")) - 1;
                while (move > 0 and !stacks[from].empty()) {

                    stacks[to].push(stacks[from].top());
                    stacks[from].pop();
                    move--;
                }


            }

        }
    }
    for (const stack<char> &stack: stacks) {
        cout<<stack.top();
    }
    cout<<'\n';

}

void day5Part2(const list<string> &inputStringList) {
    size_t num_stacks = inputStringList.front().length() / 4 + 1;
    vector<stack<char>> stacks(num_stacks);
    bool atMoves = false;
    for (string line: inputStringList) {
        if (!line.empty()) {
            if (line[1] == '1') {
                atMoves = true;
                for (stack<char> &stack: stacks) {
                    reverseStack(stack);
                }
            }
            if (!atMoves) {
                for (int i = 0; i < num_stacks; i++) {
                    if (!isblank(line[i * 4 + 1])) {
                        stacks[i].push(line[i * 4 + 1]);
                    }
                }
            } else if (line[0] == 'm') {

                int move = stoi(strtok(line.data(), "move"));
                int from = stoi(strtok(nullptr, "from")) - 1;
                int to = stoi(strtok(nullptr, "to")) - 1;
                stack<char> temp;
                int move2=move;
                while (move > 0 and !stacks[from].empty()) {
                    temp.push(stacks[from].top());
                    stacks[from].pop();
                    move--;
                }
                while(move2>0){
                    stacks[to].push(temp.top());
                    temp.pop();
                    move2--;
                }


            }

        }
    }
    for (const stack<char> &stack: stacks) {
        cout<<stack.top();
    }
    cout<<'\n';

}

int mainDay5() {
    initDay(5, &day5Part1, &day5Part2);
    return 0;
}