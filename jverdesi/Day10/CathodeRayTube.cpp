//
// Created by jverdesi on 12/12/22.
//

#include <string>
#include <list>
#include <iostream>
#include <cstring>
#include <cmath>
#include "../Utils/InitDay.h"
#include <fcntl.h>
#include <cstdio>

using namespace std;

#include "CathodeRayTube.h"

void day10Part1(const list<string> &inputStringList) {
    int clock_cycle = 0;
    int register_x = 1;
    int signal_strength_sum = 0;
    for (string line: inputStringList) {
        if (!line.empty()) {
            string op = strtok(line.data(), " ");
            int new_clock = clock_cycle;
            int addx = 0;
            if (op == "addx") {
                addx = stoi(strtok(nullptr, " "));
                new_clock += 2;
            } else {
                new_clock++;
            }
            int curr_round_cycle = floor((clock_cycle + 20) / 40);
            int new_round_cycle = floor((new_clock + 20) / 40);

            if (curr_round_cycle < new_round_cycle and new_round_cycle < 7) {
                int rounded_cycle = (int) floor(new_clock / 20) * 20;
                signal_strength_sum += rounded_cycle * register_x;
            }

            clock_cycle = new_clock;
            register_x += addx;

        }
    }
    cout << "Signal_strength_sum: " << signal_strength_sum << '\n';
}

void printCycle(int x_register, int clock_cycle) {
    int row=floor(clock_cycle / 40);
    if (row > floor((clock_cycle - 1) / 40)) {
        cout << '\n';
    }
    if (abs(clock_cycle-(row*40) - x_register) < 2)
        cout << (const char*) u8"\u2593";
    else
        cout << (const char*) u8"\u2591";
}

void day10Part2(const list<string> &inputStringList) {

    int clock_cycle = 0;
    int register_x = 1;
    for (string line: inputStringList) {
        if (!line.empty()) {
            string op = strtok(line.data(), " ");
            int addx = 0;
            if (op == "addx") {
                addx = stoi(strtok(nullptr, " "));
                printCycle(register_x, clock_cycle++);
                printCycle(register_x, clock_cycle++);

            } else {
                printCycle(register_x, clock_cycle++);
            }
            register_x += addx;
        }
    }

}


int mainDay10() {
    //_setmode(_fileno(stdout), _O_U16TEXT); // <=== Windows madness

    initDay(10, &day10Part1, &day10Part2);
    return 0;
}