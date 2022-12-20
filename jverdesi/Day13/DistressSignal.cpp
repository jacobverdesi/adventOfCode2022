//
// Created by jacob on 12/19/21322.
//

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include "../Utils/InitDay.h"
#include "DistressSignal.h"

using namespace std;

class NestedInteger {
private:
    int val = -1;
    vector<NestedInteger> subList;

public:
    NestedInteger() = default;

    explicit NestedInteger(int value) {
        val = value;
    }

    [[nodiscard]] bool isInteger() const {
        return val != -1;
    }

    [[nodiscard]] int getInteger() const {
        return val;
    }

    void setInteger(int value) {
        val = value;
    }

    void add(const NestedInteger &ni) {
        subList.push_back(ni);
    }

    [[nodiscard]] vector<NestedInteger> getList() const {
        return subList;
    }


};

void printNest(NestedInteger &curr) {
    if (curr.isInteger()) {
        cout << curr.getInteger();
    } else {
        cout << "[";
        int currLen = (int) curr.getList().size();
        for (auto sub: curr.getList()) {
            printNest(sub);
            if (--currLen != 0)
                cout << ",";

        }
        cout << "]";
    }
}

bool compare_signals(NestedInteger &left, NestedInteger &right) {
    cout << "Compare ";
    printNest(left);
    cout << " vs ";
    printNest(right);
    cout << '\n';

    if (left.isInteger() && right.isInteger()) {
        if (left.getInteger() < right.getInteger()) {
            cout << "Left side is smaller, so inputs are in the right order\n";

            return true;
        } else if (left.getInteger() > right.getInteger()) {
            cout << "Right side is smaller, so inputs are not in the right order\n";

        }
    } else if (left.isInteger()) {
        NestedInteger newLeft;
        newLeft.add(left);
        if (compare_signals(newLeft, right)) {
            return true;
        }
    } else if (right.isInteger()) {
        NestedInteger newRight;
        newRight.add(right);
        if (compare_signals(left, newRight)) {
            return true;
        }

    } else {

        int leftLen = (int) left.getList().size();
        int rightLen = (int) right.getList().size();
        for (int i = 0; i < leftLen; i++) {
            if (i >= rightLen) {
                cout << "Right side ran out of items, so inputs are not in the right order\n";
                return false;
            }
            if (compare_signals(left.getList()[i], right.getList()[i]))
                    return true;


        }
        cout << "Left side ran out of items, so inputs are in the right order\n";
        return true;

    }
    return false;
}

NestedInteger initalize_signal(const string &s, int &i) {
    NestedInteger newSignal;
    if (s[i] == '[' || s[i] == ',') {
        while (s[i] == ',' || s[i] == '[') {
            if (s[++i] != ']') newSignal.add(initalize_signal(s, i));
        }
        ++i;
    } else if (isdigit(s[i]) || s[i] == '-') {
        int sign = 1, num = 0;
        if (s[i] == '-') {
            sign = -1;
            ++i;
        }
        while (i < s.size() && isdigit(s[i]))
            num = num * 10 + s[i++] - '0';
        newSignal.setInteger(sign * num);
    }

    return newSignal;
}

void day13Part1(const list<string> &inputStringList) {

    int indexSum = 0;
    int rowIdx = 0;
    NestedInteger signal1, signal2;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            int i = 0;
            if (rowIdx % 2 == 0) {
                signal1 = initalize_signal(line, i);
                printNest(signal1);
                cout << '\n';

            } else {
                signal2 = initalize_signal(line, i);
                printNest(signal2);
                cout << '\n';

                indexSum += compare_signals(signal1, signal2) * rowIdx / 2;
            }
            rowIdx++;
        }
    }
    cout << "Score: " << indexSum << "\n";

}

void day13Part2(const list<string> &inputStringList) {
    int score = 0;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";
}

int mainDay13() {
    initDay(13, &day13Part1, &day13Part2);
    return 13;
}