#include"Symbol.h"

class Parser {
private:
    string text;
    unsigned int index;
public:
    Parser(string s): text(s), index(0) {}
    bool hasNext();
    Symbol next();
};