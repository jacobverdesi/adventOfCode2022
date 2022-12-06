//
// Created by jacob on 12/5/2022.
//
#include "iostream"
#include "StackHelper.h"
#include "stack"

using namespace std;


void PrintStack(stack<char> s) {
    stack<char> temp;
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }

    while (!temp.empty()) {
        char t = temp.top();
        cout << t << "";
        temp.pop();
        s.push(t);
    }
    cout << '\n';
}

void reverseStack(stack<char> &inputStack) {
    char item;
    stack<char> tmpStack;

    while (!inputStack.empty()) {
        item = inputStack.top();
        inputStack.pop();
        tmpStack.push(item);
    }
    inputStack = tmpStack;
}