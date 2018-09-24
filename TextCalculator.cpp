#include<iostream>
#include<vector>
#include<sstream>

#include"Action.h"
#include"TextCalculator.h"

using namespace std;

PushAction PUSH_ACTION;
Action* PUSH = &PUSH_ACTION;
ElimAction ELIM_ACTION;
Action* ELIM = &ELIM_ACTION;
PopAction POP_ACTION;
Action* POP = &POP_ACTION;
AccAction ACC_ACTION;
Action* ACC = &ACC_ACTION;

Action* table[][8] = {
    //  E,    +,    -,    *,    (,    ),    =,    N
    {NULL, PUSH, PUSH, PUSH, PUSH, NULL,  ACC, NULL}, // E
    {NULL,  POP,  POP, PUSH, PUSH,  POP,  POP, NULL}, // +
    {NULL,  POP,  POP, PUSH, PUSH,  POP,  POP, NULL}, // -
    {NULL,  POP,  POP,  POP, PUSH,  POP,  POP, NULL}, // *
    {NULL, PUSH, PUSH, PUSH, PUSH, ELIM, NULL, NULL}, // (
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, // )
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}, // =
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}  // N
};

int TextCalculator::calculate(string& text) {
    vector<int> operandStack;
    vector<Operator*> operatorStack;
    QuietOperator empOperator(SymbolType::emp);
    operatorStack.push_back(&empOperator);
    Parser parser(text);
    while(parser.hasNext()) {
        Symbol symbol = parser.next();
        if(symbol.isNum()) {
            operandStack.push_back(symbol.toNum());
            continue;
        }
        Operator* nextOperator = symbol.toOperator();
        Action* action = NULL;
        do {
            action = table[operatorStack.back()->getSymbolType()]
                    [nextOperator->getSymbolType()];
            if(NULL == action) {
                throw string("Invalid Expression");
            }
        } while(action->act(operatorStack, nextOperator, operandStack));
    }
    return operandStack.back();
}

void main() {
    // input
    string text;
    getline(cin, text);
    // calculate
    TextCalculator calculator;
    try {
        cout << calculator.calculate(text) << endl;
    } catch(string msg) {
        cout << msg << endl;
        return;
    }
}