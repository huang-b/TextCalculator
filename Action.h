#ifndef ACTION
#define ACTION

#include"Operator.h"

class Action {
public:
    virtual bool act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack) = 0;
};

class PushAction: public Action {
    bool act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack);
};

class PopAction: public Action {
    bool act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack);
};

class ElimAction: public Action {
    bool act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack);
};

class AccAction: public Action {
    bool act(vector<Operator*>& operatorStack, 
        Operator* nextOperator, vector<int>& operandStack);
};

#endif