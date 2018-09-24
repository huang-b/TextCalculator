#include"Operator.h"

void AddOperator::operate(vector<int>& operandStack) {
    int b = operandStack.back();
    operandStack.pop_back();
    int a = operandStack.back();
    operandStack.pop_back();
    operandStack.push_back(a + b);
}

void SubOperator::operate(vector<int>& operandStack) {
    int b = operandStack.back();
    operandStack.pop_back();
    int a = operandStack.back();
    operandStack.pop_back();
    operandStack.push_back(a - b);
}

void MulOperator::operate(vector<int>& operandStack) {
    int b = operandStack.back();
    operandStack.pop_back();
    int a = operandStack.back();
    operandStack.pop_back();
    operandStack.push_back(a * b);
}

void QuietOperator::operate(vector<int>& operandStack) {
    // quiet means do nothing
}