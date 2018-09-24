#include"Action.h"

bool PushAction::act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack) {
    operatorStack.push_back(nextOperator);
    return false;
}

bool PopAction::act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack) {
    Operator* lastOperator = operatorStack.back();
    operatorStack.pop_back();
    lastOperator->operate(operandStack);
    delete lastOperator;
    return true;
}

bool ElimAction::act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack) {
    operatorStack.pop_back();
    return false;
}

bool AccAction::act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack) {
    return false;
}