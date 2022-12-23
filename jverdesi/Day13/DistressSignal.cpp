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

    bool operator==(NestedInteger& other) const
    {
        int leftLen = (int) this->subList.size();
        int rightLen = (int) other.getList().size();
        if(leftLen!=rightLen or this->val != other.val)
            return false;
        for (int i = 0; i < leftLen; i++) {
          if(!(this->getList()[i]== other.getList()[i]))
              return false;
        }
        return true;

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

int compare_signals(NestedInteger &left, NestedInteger &right) {
//    cout << "Compare ";
//    printNest(left);
//    cout << " vs ";
//    printNest(right);
//    cout << '\n';

    if (left.isInteger() && right.isInteger()) {
        if (left.getInteger() < right.getInteger()) {
//            cout << "Left side is smaller, so inputs are in the right order\n";

            return 1;
        } else if (left.getInteger() > right.getInteger()) {
//            cout << "Right side is smaller, so inputs are not in the right order\n";
            return 0;
        }
    } else if (left.isInteger()) {
        NestedInteger newLeft;
        newLeft.add(left);
        return compare_signals(newLeft, right);
    } else if (right.isInteger()) {
        NestedInteger newRight;
        newRight.add(right);
        return compare_signals(left, newRight);

    } else {
        int leftLen = (int) left.getList().size();
        int rightLen = (int) right.getList().size();
        for (int i = 0; i < leftLen; i++) {
            if (i >= rightLen) {
//                cout << "Right side ran out of items, so inputs are not in the right order\n";
                return 0;
            }
            int retVal = compare_signals(left.getList()[i], right.getList()[i]);
            if (retVal != -1)
                return retVal;

        }
        if (leftLen < rightLen) {
//            cout << "Left side ran out of items, so inputs are in the right order\n";
            return 1;
        }


    }
    return -1;
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
//                printNest(signal1);
//                cout << '\n';

            } else {
                signal2 = initalize_signal(line, i);

                bool inOrder = compare_signals(signal1, signal2);
                indexSum += inOrder * ((rowIdx + 1) / 2);
//                printNest(signal2);
//                cout << "\n";
//                cout << "Row Index: " << (rowIdx + 1) / 2 << " In Order: " << inOrder << "\n";
//                cout << "==========\n";

            }
            rowIdx++;

        }

    }
    cout << "Score: " << indexSum << "\n";

}

void day13Part2(const list<string> &inputStringList) {
    int score = 0;
    vector<NestedInteger>signalList;
    for (const string &line: inputStringList) {
        if (!line.empty()) {
            int i=0;
            signalList.push_back(initalize_signal(line, i));
        }
    }
    sort(signalList.begin(),signalList.end(), compare_signals);
    int index=1;
    const string d1str="[[2]]";
    const string d2str="[[6]]";
    int i=0;
    int i2=0;

    NestedInteger divider1= initalize_signal(d1str,i);
    NestedInteger divider2= initalize_signal(d2str,i2);
    int d1Index=0;
    int d2Index=0;
    for(auto signal:signalList){
        if(divider1==signal)
            d1Index=index;
        if(divider2==signal)
            d2Index=index;
//        cout<<"Signal index: "<<index<<" Signal: ";
//        printNest(signal);
//        cout<<"\n";
        index++;
    }
    cout << "Score: " << d1Index*d2Index << "\n";
}

int mainDay13() {
    initDay(13, &day13Part1, &day13Part2);
    return 13;
}